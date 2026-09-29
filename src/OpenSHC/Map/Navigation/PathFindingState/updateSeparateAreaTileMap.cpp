#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp"


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
            if (0 < DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps
                || (DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps = 200,
                    this->toggleUpdateSeparateAreaTileMap == 0)) {
                return FALSE;
            }
            this->field41_0x74 = this->field41_0x74 + 1;
            this->toggleUpdateSeparateAreaTileMap = 0;
            this->totalZones = 0;
            this->sum = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.PathConnectionLayer)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                4000, '\0', (void*)((int)(this->zoneSizesArray)));
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
            /*
              The eight-neighbour expansion below is handwritten assembly in the original and reaches
              the area layer and the queue through these locals; see LinkageNeighbourAsm.hpp. The
              queue end lives in the forceUpdate parameter slot, as it does in the original.
             */
            ushort* _areaLayer = DAT_TileMapState::instance.PathConnectionLayer;
            int* _tilesQueue = this->searchQueue.tilesQueue;
            short* _yQueue = this->searchQueue.yQueue;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            short _areaID = 1;
            short _row = 0;
            int* _rowEnd = &DAT_ViewportRenderState::instance.translationMatrix[1].firstTileOfRow;
            for (int _first = 0; _first < 80400; _first = _first + 1) {
                if (*_rowEnd <= _first) {
                    _row = _row + 1;
                    _rowEnd = _rowEnd + 3;
                }
                if ((char)(short)DAT_TileMapState::instance.PathConnectionLayer[_first] != '\0'
                    || (DAT_TileMapState::instance.LogicLayer[_first] & 0x4a5014b1) != 0) {
                    continue;
                }
                this->searchQueue.tilesQueue[0] = _first;
                this->searchQueue.yQueue[0] = _row;
                DAT_TileMapState::instance.PathConnectionLayer[_first] = _areaID;
                forceUpdate = 1;
                for (int _readIndex = 0; _readIndex != forceUpdate; _readIndex = _readIndex + 1) {
                    this->zoneSizesArray[(ushort)_areaID] = this->zoneSizesArray[(ushort)_areaID] + 1;
                    int _tile = this->searchQueue.tilesQueue[_readIndex];
                    int _cY = (ushort)this->searchQueue.yQueue[_readIndex];
                    int _cLink = DAT_TileMapState::instance.PathLinkageLayer[_tile];

                    MACRO_LINKAGE_EXPAND_AREA_NEIGHBOURS(1, forceUpdate)
                }
                _areaID = _areaID + 1;
                if (999 < _areaID) {
                    break;
                }
            }
            this->totalZones = (int)_areaID;
            int* _zoneSize = this->zoneSizesArray + 2;
            for (int _group = 333; _group != 0; _group = _group - 1) {
                this->sum = _zoneSize[1] + this->sum + _zoneSize[-1] + *_zoneSize;
                _zoneSize = _zoneSize + 3;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
            return TRUE;
        }

    }
}
}
