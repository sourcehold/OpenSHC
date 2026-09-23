#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // counts the grid cells around the campground that are usable for the resource buildings
    // FUNCTION: STRONGHOLDCRUSADER 0x004EE830
    void AIVState::recomputeAIAvailableGridTiles(int playerID)
    {
        DAT_GameState::instance.playerDataArray[playerID].algoTreeCooldownUnk = -1;
        DAT_GameState::instance.playerDataArray[playerID].algoOasisCooldownUnk = -1;
        DAT_GameState::instance.playerDataArray[playerID].algoBoulderCooldown = -1;
        DAT_GameState::instance.playerDataArray[playerID].algoIronCooldown = -1;
        DAT_GameState::instance.playerDataArray[playerID].algoOilCooldown = -1;
        DAT_GameState::instance.playerDataArray[playerID].availableTreeGridTiles = 0;
        DAT_GameState::instance.playerDataArray[playerID].availableOasisGridTiles = 0;
        DAT_GameState::instance.playerDataArray[playerID].availableBoulderGridTiles = 0;
        DAT_GameState::instance.playerDataArray[playerID].availableIronGridTiles = 0;
        DAT_GameState::instance.playerDataArray[playerID].availableOilGridTiles = 0;
        this->visitCount = 1;
        this->algBIndex = 1;
        this->algAIndex = 0;
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
                uint const gridX = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + x;
                uint const gridY = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + y;
                if (this->heatMaps[x][y].isNotNearEdgeUnk && (gridX > 79 || gridY > 79)) {
                    continue;
                }
                if (this->heatMaps[gridX][gridY].algorithmIterationNumber == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                int const impassable = (char)this->heatMaps[gridX][gridY].impassableCount;
                this->heatMaps[gridX][gridY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
                int const notInLargestArea = (char)this->heatMaps[gridX][gridY].tilesNotPartOfLargestAreaCount;
                int const blockedCount = notInLargestArea - impassable;
                if (blockedCount >= 16) {
                    continue;
                }
                if ((char)this->heatMaps[gridX][gridY].oilCount >= 2 && (char)this->heatMaps[gridX][gridY].marshCount >= 10 && notInLargestArea == impassable) {
                    if (this->heatMaps[gridX][gridY].highestTerrainHeight - this->heatMaps[gridX][gridY].lowestTerrainHeight < 12) {
                        ++DAT_GameState::instance.playerDataArray[playerID].availableOilGridTiles;
                    }
                } else if ((char)this->heatMaps[gridX][gridY].ironCount >= 6 && blockedCount <= 4) {
                    if (this->heatMaps[gridX][gridY].highestTerrainHeight - this->heatMaps[gridX][gridY].lowestTerrainHeight < 12) {
                        ++DAT_GameState::instance.playerDataArray[playerID].availableIronGridTiles;
                    }
                } else if ((char)this->heatMaps[gridX][gridY].bouldersCount >= 8 && notInLargestArea == impassable) {
                    if (this->heatMaps[gridX][gridY].highestTerrainHeight - this->heatMaps[gridX][gridY].lowestTerrainHeight < 40) {
                        ++DAT_GameState::instance.playerDataArray[playerID].availableBoulderGridTiles;
                    }
                } else if ((char)this->heatMaps[gridX][gridY].treeCount >= 0 && blockedCount <= 5) {
                    if (this->heatMaps[gridX][gridY].highestTerrainHeight - this->heatMaps[gridX][gridY].lowestTerrainHeight < 12) {
                        ++DAT_GameState::instance.playerDataArray[playerID].availableTreeGridTiles;
                    }
                } else if ((char)this->heatMaps[gridX][gridY].oasisScrubCount > 25 && (char)this->heatMaps[gridX][gridY].oasisThickScrubCount > 14
                    && notInLargestArea == impassable && this->heatMaps[gridX][gridY].highestTerrainHeight - this->heatMaps[gridX][gridY].lowestTerrainHeight < 12) {
                    ++DAT_GameState::instance.playerDataArray[playerID].availableOasisGridTiles;
                }
                this->heatMaps[gridX][gridY].algorithmVisitCountUnk = this->visitCount + 1;
                this->heatMapXArray[this->algBIndex] = gridX;
                this->heatMapYArray[this->algBIndex] = gridY;
                ++this->algBIndex;
                if (this->algBIndex > 6400) {
                    this->algBIndex = 0;
                }
            }
            ++this->algAIndex;
            if (this->algAIndex > 6400) {
                this->algAIndex = 0;
            }
        }

        // allow searching right away if there is anything to find
        if (DAT_GameState::instance.playerDataArray[playerID].availableTreeGridTiles > 0) {
            DAT_GameState::instance.playerDataArray[playerID].algoTreeCooldownUnk = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].availableOasisGridTiles > 0) {
            DAT_GameState::instance.playerDataArray[playerID].algoOasisCooldownUnk = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].availableBoulderGridTiles > 0) {
            DAT_GameState::instance.playerDataArray[playerID].algoBoulderCooldown = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].availableIronGridTiles > 0) {
            DAT_GameState::instance.playerDataArray[playerID].algoIronCooldown = 0;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].availableOilGridTiles > 0) {
            DAT_GameState::instance.playerDataArray[playerID].algoOilCooldown = 0;
        }
    }

}
}
