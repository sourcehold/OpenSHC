#include "../AIVState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search from the campground for an oasis grid cell and places the farm there
    // FUNCTION: STRONGHOLDCRUSADER 0x004EDDF0
    int AIVState::findSuitableFarmLocationAndPlaceFarm(PlayerID playerID, MappersEnum farmType)
    {
        if (DAT_BuildingsState::instance.unknownCountdown01 < 20
            || DAT_GameState::instance.playerDataArray[playerID].countFarms
                >= DAT_GameState::instance.playerDataArray[playerID].availableOasisGridTiles) {
            return 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].algoOasisCooldownUnk > 0) {
            --DAT_GameState::instance.playerDataArray[playerID].algoOasisCooldownUnk;
            return 0;
        }

        this->visitCount = 1;
        this->algAIndex = 0;
        this->algBIndex = 1;
        // despite its declared type, farmType holds the BuildingType of the farm
        // the original leaves mapper untouched when farmType is none of the four below
        MappersEnum mapper;
        if (farmType == Map::Buildings::BT_WHEATFARM) {
            mapper = Commands::M_MAPPER_WHEATFARM;
        } else if (farmType == Map::Buildings::BT_HOPFARM) {
            mapper = Commands::M_MAPPER_HOPSFARM;
        } else if (farmType == Map::Buildings::BT_APPLEFARM) {
            mapper = Commands::M_MAPPER_APPLEFARM;
        } else if (farmType == Map::Buildings::BT_DAIRYFARM) {
            mapper = Commands::M_MAPPER_CATTLEFARM;
        }
        int const campX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry / 5;
        this->heatMapXArray[0] = campX;
        ++this->mapExtraInfo.algorithmIterationNumber;
        int const campY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry / 5;
        this->heatMapYArray[0] = campY;
        this->heatMaps[campX][campY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
        this->heatMaps[campX][campY].algorithmVisitCountUnk = this->visitCount;

        while (this->algAIndex != this->algBIndex) {
            int const x = this->heatMapXArray[this->algAIndex];
            int const y = this->heatMapYArray[this->algAIndex];
            this->visitCount = (char)this->heatMaps[x][y].algorithmVisitCountUnk;
            if (this->visitCount > 40) {
                break;
            }
            // only the four cardinal directions
            for (int direction = 0; direction < 8; direction += 2) {
                uint const gridY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + y;
                uint const gridX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + x;
                if (this->heatMaps[x][y].isNotNearEdgeUnk && (gridX > 79 || gridY > 79)) {
                    continue;
                }
                if (this->heatMaps[gridX][gridY].algorithmIterationNumber
                    == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                int const notInLargestArea = (char)this->heatMaps[gridX][gridY].tilesNotPartOfLargestAreaCount;
                this->heatMaps[gridX][gridY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
                if (notInLargestArea > 16) {
                    continue;
                }
                this->heatMaps[gridX][gridY].algorithmVisitCountUnk = this->visitCount + 1;
                this->heatMapXArray[this->algBIndex] = gridX;
                this->heatMapYArray[this->algBIndex] = gridY;
                ++this->algBIndex;
                if ((int)this->algBIndex >= 6400) {
                    this->algBIndex = 0;
                }
                if (this->heatMaps[gridX][gridY].tilesNotPartOfLargestAreaCount
                    || this->heatMaps[gridX][gridY].structureCount || this->heatMaps[gridX][gridY].treeCount
                    || this->heatMaps[gridX][gridY].destructionBasedPlacementCooldown
                    || (char)this->heatMaps[gridX][gridY].oasisScrubCount <= 25
                    || (char)this->heatMaps[gridX][gridY].oasisThickScrubCount <= 14) {
                    continue;
                }
                int const xOffset
                    = DAT_AIVDefinedData::instance.TilesSelfAndRightThree[this->mapExtraInfo.algBuildingPlacementNudge]
                          .x;
                int const yOffset
                    = DAT_AIVDefinedData::instance.TilesSelfAndRightThree[this->mapExtraInfo.algBuildingPlacementNudge]
                          .y;
                ++this->counter;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(playerID,
                    xOffset + gridX * 5, yOffset + gridY * 5, mapper,
                    MACRO_CALL_MEMBER(
                        Map::TileMapState_Func::getBuildingSizeForCommandBuildingType, DAT_TileMapState::ptr)(mapper),
                    15);
                if (!DAT_TileMapState::instance.buildingPlacementFail) {
                    this->heatMaps[gridX][gridY].structureCount = 1;
                    return 1;
                }
            }
            ++this->algAIndex;
            if ((int)this->algAIndex >= 6400) {
                this->algAIndex = 0;
            }
        }
        DAT_GameState::instance.playerDataArray[playerID].algoOasisCooldownUnk = 5;
        return 0;
    }

}
}
