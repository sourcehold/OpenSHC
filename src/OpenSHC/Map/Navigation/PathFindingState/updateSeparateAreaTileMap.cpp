#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004995E0
        BOOLEnum PathFindingState::updateSeparateAreaTileMap(int forceUpdate)
        {
            if (forceUpdate != 0) {
                this->toggleUpdateSeparateAreaTileMap = 1;
                DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps = 0;
            }
            DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps
                = DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps - 1;
            if (0 < DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps) {
                return FALSE;
            }
            DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps = 200;
            if (this->toggleUpdateSeparateAreaTileMap == 0) {
                return FALSE;
            }
            this->field_0x74 += 1;
            /*
              The flood fill of one area (the dequeue loop with its eight-neighbour expansion) is
              handwritten assembly in the original; it reaches the area layer, the zone sizes and the
              queue through these locals; see LinkageNeighbourAsm.hpp. The queue end lives in the forceUpdate
              parameter slot, as it does in the original.
             */
            ushort* _areaLayer;
            int* _zoneSizes;
            short* _yQueue;
            int* _tilesQueue;
            uchar* _linkage;
            int* _dirMatrix;
            int _readIndex;
            int _tile;
            int _cY;
            this->toggleUpdateSeparateAreaTileMap = 0;
            this->totalZones = 0;
            this->sum = 0;
            _readIndex = 0;
            _areaLayer = DAT_TileMapState::instance.PathConnectionLayer;
            _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            _yQueue = this->searchQueue.yQueue;
            _tilesQueue = this->searchQueue.tilesQueue;
            _zoneSizes = this->zoneSizesArray;
            forceUpdate = 1;
            int _areaID = 1;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.PathConnectionLayer), 0,
                (void*)(DAT_TileMapState::instance.PathConnectionLayer));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                4000, '\0', (void*)(this->zoneSizesArray));
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
            int _row = 0;
            int* _rowEnd;
            int _first = 0;
            _rowEnd = &DAT_ViewportRenderState::instance.translationMatrix[1].firstTileOfRow;
            for (; _first < MC_MAP_TILES_COUNT; _first = _first + 1) {
                if (_first >= *_rowEnd) {
                    _row += 1;
                    _rowEnd += 3;
                }
                /*
                  the original tests only the low byte of this 2-byte element
                  (cmp byte ptr [eax*2 + ..], 0), so an area ID that is a multiple of 256
                  reads as unassigned here. Kept as the original has it.
                 */
                if ((char)DAT_TileMapState::instance.PathConnectionLayer[_first] != '\0'
                    || (DAT_TileMapState::instance.LogicLayer[_first]
                           & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE
                               | LogicHelpers::L_ROCKY | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE
                               | LogicHelpers::L_RIVER | LogicHelpers::L_CRENEL_VARIATIONUnk
                               | LogicHelpers::L_FARM_FIELD_HOP | LogicHelpers::L_FARM_FIELD_DAIRY
                               | LogicHelpers::L_MOAT))
                        != 0) {
                    continue;
                }
                this->searchQueue.yQueue[0] = _row;
                this->searchQueue.tilesQueue[0] = _first;
                forceUpdate = 1;
                _readIndex = 0;
                DAT_TileMapState::instance.PathConnectionLayer[_first] = _areaID;

                // clang-format off
                __asm {
                    mov edi, _areaLayer
                area_loop:
                    mov ecx, _readIndex
                    cmp ecx, forceUpdate
                    je area_done
                    mov esi, _zoneSizes
                    mov eax, 0
                    mov edx, 1
                    mov ax, word ptr _areaID
                    add dword ptr [esi + eax*4], edx
                    mov esi, _tilesQueue
                    mov edx, dword ptr [esi + ecx*4]
                    mov _tile, edx
                    mov esi, _yQueue
                    mov eax, 0
                    mov ax, word ptr [esi + ecx*2]
                    mov _cY, eax
                    mov ebx, _linkage
                    mov bl, byte ptr [ebx + edx]
                }
                MACRO_LINKAGE_PUSH_AREA(1, w, forceUpdate, -2, 64, MACRO_ASM_DEC, MACRO_ASM_SAME)
                MACRO_LINKAGE_PUSH_AREA(1, e, forceUpdate, +2, 4, MACRO_ASM_INC, MACRO_ASM_SAME)
                __asm mov edx, _tile
                __asm mov eax, _cY
                __asm shl eax, 3
                __asm mov esi, _dirMatrix
                __asm add edx, dword ptr [esi + eax*4]
                MACRO_LINKAGE_PUSH_AREA(1, nw, forceUpdate, -2, 128, MACRO_ASM_DEC, MACRO_ASM_DEC)
                MACRO_LINKAGE_PUSH_AREA(1, n, forceUpdate, 0, 1, MACRO_ASM_SAME, MACRO_ASM_DEC)
                MACRO_LINKAGE_PUSH_AREA(1, ne, forceUpdate, +2, 2, MACRO_ASM_INC, MACRO_ASM_DEC)
                __asm mov edx, _tile
                __asm mov eax, _cY
                __asm shl eax, 3
                __asm add eax, 4
                __asm mov esi, _dirMatrix
                __asm add edx, dword ptr [esi + eax*4]
                MACRO_LINKAGE_PUSH_AREA(1, sw, forceUpdate, -2, 32, MACRO_ASM_DEC, MACRO_ASM_INC)
                MACRO_LINKAGE_PUSH_AREA(1, s, forceUpdate, 0, 16, MACRO_ASM_SAME, MACRO_ASM_INC)
                MACRO_LINKAGE_PUSH_AREA(1, se, forceUpdate, +2, 8, MACRO_ASM_INC, MACRO_ASM_INC)
                __asm {
                    add _readIndex, 1
                    jmp area_loop
                area_done:
                } // clang-format on

                _areaID += 1;
                // both (short) here and on the store below are load-bearing: dropping them
                // costs an instruction, so the original kept this value 16 bits wide
                if (1000 <= (short)_areaID) {
                    break;
                }
            }
            this->totalZones = (short)_areaID;
            for (int _zone = 1; _zone < 1000; _zone = _zone + 1) {
                this->sum = this->sum + this->zoneSizesArray[_zone];
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
            return TRUE;
        }

    }
}
}
