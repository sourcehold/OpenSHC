#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search from the campground for the grid cell with the best tree score
    // FUNCTION: STRONGHOLDCRUSADER 0x004EE140
    void AIVState::findAppropriateWoodCutterGridLocation(int playerID)
    {
        this->algAIndex = 0;
        int foundCount = 0;
        this->visitCount = 1;
        this->algBIndex = 1;
        int const campX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry / 5;
        this->heatMapXArray[0] = campX;
        int const campY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry / 5;
        this->heatMapYArray[0] = campY;
        this->buildingApproriateGridXPosition = -1;
        this->buildingAppropriateGridYPosition = -1;
        int bestScore = -100;
        uint bestX = -1;
        uint bestY = -1;
        if (DAT_GameState::instance.playerDataArray[playerID].algoTreeCooldownUnk > 0) {
            --DAT_GameState::instance.playerDataArray[playerID].algoTreeCooldownUnk;
            return;
        }
        ++this->mapExtraInfo.algorithmIterationNumber;
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
                this->heatMaps[gridX][gridY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
                char const notInLargestArea = (char)this->heatMaps[gridX][gridY].tilesNotPartOfLargestAreaCount;
                if (notInLargestArea >= 16 || this->heatMaps[gridX][gridY].destructionBasedPlacementCooldown) {
                    continue;
                }
                if (notInLargestArea >= 6) {
                    continue;
                }
                char const treeCount = (char)this->heatMaps[gridX][gridY].treeCount;
                if (treeCount <= 0) {
                    continue;
                }
                ++foundCount;
                int score = treeCount * 5 - this->visitCount * 3;
                // prefer cells that were not used for a woodcutter recently
                if (this->heatMaps[gridX][gridY].woodRelatedCountdownTo0) {
                    if (score > 0) {
                        score /= 2;
                    } else {
                        score *= 2;
                    }
                }
                if (score > bestScore) {
                    bestX = gridX;
                    bestY = gridY;
                    bestScore = score;
                }
                if (foundCount > 10 || (foundCount > 5 && this->visitCount > 20)
                    || (foundCount > 0 && this->visitCount > 30)) {
                    break;
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
        if (foundCount > 0) {
            this->buildingApproriateGridXPosition = bestX;
            this->buildingAppropriateGridYPosition = bestY;
            return;
        }
        DAT_GameState::instance.playerDataArray[playerID].algoTreeCooldownUnk = 5;
    }

}
}
