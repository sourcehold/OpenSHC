#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // breadth first search for the closest free grid cell
    // FUNCTION: STRONGHOLDCRUSADER 0x004EEBD0
    void AIVState::findSuitableGridLocationFittingCriteria(uint gridX, uint gridY)
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

        while (this->algAIndex != this->algBIndex) {
            int const x = this->heatMapXArray[this->algAIndex];
            int const y = this->heatMapYArray[this->algAIndex];
            this->visitCount = (char)this->heatMaps[x][y].algorithmVisitCountUnk;
            for (int direction = 0; direction < 8; ++direction) {
                uint const candidateX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + x;
                uint const candidateY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + y;
                if (this->heatMaps[x][y].isNotNearEdgeUnk && (candidateX > 79 || candidateY > 79)) {
                    continue;
                }
                int const notInLargestArea
                    = (char)this->heatMaps[candidateX][candidateY].tilesNotPartOfLargestAreaCount;
                if (this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    == this->mapExtraInfo.algorithmIterationNumber) {
                    continue;
                }
                this->heatMaps[candidateX][candidateY].algorithmIterationNumber
                    = this->mapExtraInfo.algorithmIterationNumber;
                if (notInLargestArea >= 15) {
                    continue;
                }
                if (!this->heatMaps[candidateX][candidateY].terrainDiffHigherThan12
                    && !this->heatMaps[candidateX][candidateY].structureCount
                    && !this->heatMaps[candidateX][candidateY].isNotNearEdgeUnk
                    && !this->heatMaps[candidateX][candidateY].destructionBasedPlacementCooldown
                    && !this->heatMaps[candidateX][candidateY].treeCount
                    && (char)this->heatMaps[candidateX][candidateY].bouldersCount <= 0 && !notInLargestArea) {
                    this->buildingApproriateGridXPosition = candidateX;
                    this->buildingAppropriateGridYPosition = candidateY;
                    return;
                }
                this->heatMaps[candidateX][candidateY].algorithmVisitCountUnk = this->visitCount + 1;
                this->heatMapXArray[this->algBIndex] = candidateX;
                this->heatMapYArray[this->algBIndex] = candidateY;
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
    }

}
}
