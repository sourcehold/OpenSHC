#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search from the campground for a grid cell with enough of the given resource
    // FUNCTION: STRONGHOLDCRUSADER 0x004EE430
    void AIVState::findAppropriateGridLocationForResourceTypeBuilding(
        int playerID, AIGridComputationResourceType resourceType)
    {
        this->visitCount = 1;
        this->algAIndex = 0;
        this->algBIndex = 1;
        this->buildingApproriateGridXPosition = -1;
        this->buildingAppropriateGridYPosition = -1;
        if (resourceType == AIGCRT_OIL) {
            if (DAT_GameState::instance.playerDataArray[playerID].countPitchRigs
                >= DAT_GameState::instance.playerDataArray[playerID].availableOilGridTiles) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].algoOilCooldown > 0) {
                --DAT_GameState::instance.playerDataArray[playerID].algoOilCooldown;
                return;
            }
        } else if (resourceType == AIGCRT_IRON) {
            if (DAT_GameState::instance.playerDataArray[playerID].countIronMines
                >= DAT_GameState::instance.playerDataArray[playerID].availableIronGridTiles) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].algoIronCooldown > 0) {
                --DAT_GameState::instance.playerDataArray[playerID].algoIronCooldown;
                return;
            }
        } else if (resourceType == AIGCRT_BOULDER) {
            if (DAT_GameState::instance.playerDataArray[playerID].countStoneQuarries
                >= DAT_GameState::instance.playerDataArray[playerID].availableBoulderGridTiles) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].algoBoulderCooldown > 0) {
                --DAT_GameState::instance.playerDataArray[playerID].algoBoulderCooldown;
                return;
            }
        }

        int const campX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry / 5;
        ++this->mapExtraInfo.algorithmIterationNumber;
        int const campY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry / 5;
        this->heatMapXArray[0] = campX;
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
                uint const gridX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + x;
                uint const gridY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + y;
                if (this->heatMaps[x][y].isNotNearEdgeUnk && (gridX > 79 || gridY > 79)) {
                    continue;
                }
                if (this->heatMaps[gridX][gridY].algorithmIterationNumber
                    == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                this->heatMaps[gridX][gridY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
                int const blockedCount = (char)this->heatMaps[gridX][gridY].tilesNotPartOfLargestAreaCount
                    - (char)this->heatMaps[gridX][gridY].impassableCount;
                if (blockedCount >= 16) {
                    continue;
                }
                int const owner = (char)this->heatMaps[gridX][gridY].tileOwnership;
                if ((blockedCount == 0 || resourceType == AIGCRT_IRON) && blockedCount <= 4
                    && !this->heatMaps[gridX][gridY].structureCount
                    && !this->heatMaps[gridX][gridY].destructionBasedPlacementCooldown
                    && (owner == 0
                        || DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                            == DAT_GameState::instance.mapAndTime.playerTeams[owner])) {
                    if (resourceType == AIGCRT_OIL) {
                        if ((char)this->heatMaps[gridX][gridY].oilCount > 2
                            && (char)this->heatMaps[gridX][gridY].marshCount >= 10
                            && this->heatMaps[gridX][gridY].highestTerrainHeight
                                    - this->heatMaps[gridX][gridY].lowestTerrainHeight
                                < 12) {
                            this->buildingApproriateGridXPosition = gridX;
                            this->buildingAppropriateGridYPosition = gridY;
                            return;
                        }
                    } else if (resourceType == AIGCRT_IRON) {
                        if ((char)this->heatMaps[gridX][gridY].ironCount > 6
                            && this->heatMaps[gridX][gridY].highestTerrainHeight
                                    - this->heatMaps[gridX][gridY].lowestTerrainHeight
                                < 12) {
                            this->buildingApproriateGridXPosition = gridX;
                            this->buildingAppropriateGridYPosition = gridY;
                            return;
                        }
                    } else if (resourceType == AIGCRT_BOULDER) {
                        if ((char)this->heatMaps[gridX][gridY].bouldersCount >= 8
                            && this->heatMaps[gridX][gridY].highestTerrainHeight
                                    - this->heatMaps[gridX][gridY].lowestTerrainHeight
                                < 40) {
                            this->buildingApproriateGridXPosition = gridX;
                            this->buildingAppropriateGridYPosition = gridY;
                            return;
                        }
                    }
                }
                this->heatMaps[gridX][gridY].algorithmVisitCountUnk = this->visitCount + 1;
                this->heatMapXArray[this->algBIndex] = gridX;
                this->heatMapYArray[this->algBIndex] = gridY;
                ++this->algBIndex;
                if ((int)this->algBIndex >= 6400) {
                    this->algBIndex = 0;
                }
            }
            ++this->algAIndex;
            if ((int)this->algAIndex >= 6400) {
                this->algAIndex = 0;
            }
        }

        // nothing found, wait before searching again
        if (resourceType == AIGCRT_OIL) {
            DAT_GameState::instance.playerDataArray[playerID].algoOilCooldown = 5;
            return;
        }
        if (resourceType == AIGCRT_IRON) {
            DAT_GameState::instance.playerDataArray[playerID].algoIronCooldown = 5;
            return;
        }
        if (resourceType == AIGCRT_BOULDER) {
            DAT_GameState::instance.playerDataArray[playerID].algoBoulderCooldown = 5;
        }
    }

}
}
