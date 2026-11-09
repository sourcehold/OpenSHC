#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/Navigation/Enums/PathFindingConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A21B0
        void PathFindingState::placeCommemoratingStatueAtGoodLocation(int playerID)
        {
            int _startX = DAT_GameState::instance.playerDataArray[playerID].someKeepRelatedX2;
            int _startY = DAT_GameState::instance.playerDataArray[playerID].someKeepRelatedY2;
            if (_startX < 0 || _startX > MC_MAP_XY_LIMIT_MIN_1 || _startY < 0 || _startY > MC_MAP_XY_LIMIT_MIN_1
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_startY * MC_MAP_XY_LIMIT + _startX]
                    == 0) {
                return;
            }
            this->calculations += 1;
            this->searchGeneration += 1;
            if (PFC_SEARCH_GENERATION_LIMIT < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(DAT_TileMapState::instance.WalkLayer), 0, &DAT_TileMapState::instance.WalkLayer[0]);
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.yQueue[0] = _startY;
            this->searchQueue.xQueue[0] = _startX;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[_startY].addXgetTile + _startX;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = this->searchGeneration;
            MappersEnum commandBuildingType = (OpenSHC::Commands::MappersEnum)(SEC_RNG::instance.currentNumber2 % 5
                + OpenSHC::Commands::M_MAPPER_STATUE1);
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                int _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile < 0) {
                    return;
                }
                if (_tile >= MC_MAP_TILES_COUNT) {
                    return;
                }
                _startX = this->searchQueue.xQueue[this->searchQueue.readIndex];
                _startY = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (MC_MAP_TILES_COUNT < this->searchQueue.currentDistance) {
                    return;
                }
                if (20 < this->searchQueue.currentDistance) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(
                    playerID, _startX, _startY, commandBuildingType, -2);
                if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
                    DAT_TileMapState::instance.skipPlacementCheck = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                        playerID, _startX, _startY, commandBuildingType, 2, 15);
                    _tile = DAT_TileMapState::instance.placedBuildingID;
                    DAT_BuildingsState::instance.buildings[_tile].owner = 0;
                    DAT_BuildingsState::instance.buildings[_tile].statueCommemoratingPlayerID = playerID;
                    return;
                }
                for (int _direction = 0; _direction < PFC_DIRECTIONS; ++_direction) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_startY][_direction] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidate]
                               & (LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE))
                            == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidate] = this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidate] = this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.xOffset
                            + _startX;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + _startY;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                        this->searchQueue.writeIndex += 1;
                        if (MC_MAP_TILES_COUNT <= this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }

                this->searchQueue.readIndex += 1;
                if (MC_MAP_TILES_COUNT <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
        }

    }
}
}
