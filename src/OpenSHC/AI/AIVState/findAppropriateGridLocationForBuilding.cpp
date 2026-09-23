#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search for a grid cell whose eight neighbours are all free
    // FUNCTION: STRONGHOLDCRUSADER 0x004EEE10
    void AIVState::findAppropriateGridLocationForBuilding(uint gridX, uint gridY)
    {
        this->visitCount = 1;
        this->algAIndex = 0;
        this->algBIndex = 1;
        this->heatMapXArray[0] = gridX;
        this->heatMapYArray[0] = gridY;
        this->buildingApproriateGridXPosition = -1;
        this->buildingAppropriateGridYPosition = -1;
        if (gridX > 79 || gridY > 79 || this->heatMaps[gridX][gridY].isNotNearEdgeUnk) {
            return;
        }
        ++this->mapExtraInfo.algorithmIterationNumber;
        this->heatMaps[gridX][gridY].algorithmIterationNumber = this->mapExtraInfo.algorithmIterationNumber;
        this->heatMaps[gridX][gridY].algorithmVisitCountUnk = this->visitCount;

        if (this->algAIndex == this->algBIndex) {
            return;
        }
        uint candidateX;
        uint candidateY;
        for (;;) {
            int const x = this->heatMapXArray[this->algAIndex];
            int const y = this->heatMapYArray[this->algAIndex];
            int freeCount = 0;
            if (!this->heatMaps[x][y].tilesNotPartOfLargestAreaCount) {
                freeCount = 1;
            }
            this->visitCount = (char)this->heatMaps[x][y].algorithmVisitCountUnk;
            for (int direction = 0; direction < 8; ++direction) {
                candidateX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + x;
                candidateY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + y;
                if (this->heatMaps[x][y].isNotNearEdgeUnk && (candidateX > 79 || candidateY > 79)) {
                    continue;
                }
                int const notInLargestArea
                    = (char)this->heatMaps[candidateX][candidateY].tilesNotPartOfLargestAreaCount;
                if (!this->heatMaps[candidateX][candidateY].terrainDiffHigherThan12
                    && !this->heatMaps[candidateX][candidateY].structureCount
                    && !this->heatMaps[candidateX][candidateY].isNotNearEdgeUnk
                    && !this->heatMaps[candidateX][candidateY].destructionBasedPlacementCooldown
                    && !this->heatMaps[candidateX][candidateY].treeCount
                    && (char)this->heatMaps[candidateX][candidateY].bouldersCount < 0 && !notInLargestArea) {
                    ++freeCount;
                }
                if (this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    = this->mapExtraInfo.algorithmIterationNumber;
                if (notInLargestArea >= 15) {
                    continue;
                }
                this->heatMaps[candidateX][candidateY].algorithmVisitCountUnk = this->visitCount + 1;
                this->heatMapXArray[this->algBIndex] = candidateX;
                this->heatMapYArray[this->algBIndex] = candidateY;
                ++this->algBIndex;
                if ((int)this->algBIndex >= 6400) {
                    this->algBIndex = 0;
                }
            }
            if (freeCount == 9) {
                break;
            }
            ++this->algAIndex;
            if ((int)this->algAIndex >= 6400) {
                this->algAIndex = 0;
            }
            if (this->algAIndex == this->algBIndex) {
                return;
            }
        }
        // the result is the last visited neighbour
        this->buildingAppropriateGridYPosition = candidateY;
        this->buildingApproriateGridXPosition = candidateX;
    }

}
}
