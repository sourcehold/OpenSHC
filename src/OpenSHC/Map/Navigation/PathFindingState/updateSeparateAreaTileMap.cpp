#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
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

        /*
          WARNING: Restarted to delay deadcode elimination for space: ram
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
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
            this->field41_0x74 = this->field41_0x74 + 1;
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
            int _areaID;
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
            _areaID = 1;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.PathConnectionLayer)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                4000, '\0', (void*)((int)(this->zoneSizesArray)));
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
            int _row = 0;
            int* _rowEnd;
            int _first = 0;
            _rowEnd = &DAT_ViewportRenderState::instance.translationMatrix[1].firstTileOfRow;
            for (; _first < 80400; _first = _first + 1) {
                if (_first >= *_rowEnd) {
                    _row = _row + 1;
                    _rowEnd = _rowEnd + 3;
                }
                if ((char)DAT_TileMapState::instance.PathConnectionLayer[_first] != '\0'
                    || (DAT_TileMapState::instance.LogicLayer[_first] & 0x4a5014b1) != 0) {
                    continue;
                }
                this->searchQueue.yQueue[0] = (short)_row;
                this->searchQueue.tilesQueue[0] = _first;
                forceUpdate = 1;
                _readIndex = 0;
                DAT_TileMapState::instance.PathConnectionLayer[_first] = (ushort)_areaID;

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
                MACRO_LINKAGE_PUSH_AREA(1, w, forceUpdate, -2, 0x40, MACRO_ASM_DEC, MACRO_ASM_SAME)
                MACRO_LINKAGE_PUSH_AREA(1, e, forceUpdate, +2, 0x04, MACRO_ASM_INC, MACRO_ASM_SAME)
                __asm mov edx, _tile
                __asm mov eax, _cY
                __asm shl eax, 3
                __asm mov esi, _dirMatrix
                __asm add edx, dword ptr [esi + eax*4]
                MACRO_LINKAGE_PUSH_AREA(1, nw, forceUpdate, -2, 0x80, MACRO_ASM_DEC, MACRO_ASM_DEC)
                MACRO_LINKAGE_PUSH_AREA(1, n, forceUpdate, 0, 0x01, MACRO_ASM_SAME, MACRO_ASM_DEC)
                MACRO_LINKAGE_PUSH_AREA(1, ne, forceUpdate, +2, 0x02, MACRO_ASM_INC, MACRO_ASM_DEC)
                __asm mov edx, _tile
                __asm mov eax, _cY
                __asm shl eax, 3
                __asm add eax, 4
                __asm mov esi, _dirMatrix
                __asm add edx, dword ptr [esi + eax*4]
                MACRO_LINKAGE_PUSH_AREA(1, sw, forceUpdate, -2, 0x20, MACRO_ASM_DEC, MACRO_ASM_INC)
                MACRO_LINKAGE_PUSH_AREA(1, s, forceUpdate, 0, 0x10, MACRO_ASM_SAME, MACRO_ASM_INC)
                MACRO_LINKAGE_PUSH_AREA(1, se, forceUpdate, +2, 0x08, MACRO_ASM_INC, MACRO_ASM_INC)
                __asm {
                    add _readIndex, 1
                    jmp area_loop
                area_done:
                }
                // clang-format on

                _areaID = _areaID + 1;
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
