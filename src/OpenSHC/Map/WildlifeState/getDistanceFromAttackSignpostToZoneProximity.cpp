#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    // BFS from the cell of the active attack signpost within its separateAreaID, casDisRelated2 = step distance
    // (start = 1). Returns the distance of the first dequeued cell with a same-area populated neighbour whose
    // unknownNonZero01 != 0 (0x52DE6E), 0 when the queue runs empty or a dequeued distance is >= 100 (signed jge
    // 0x52DE23).
    // FUNCTION: STRONGHOLDCRUSADER 0x0052DD20
    int WildlifeState::getDistanceFromAttackSignpostToZoneProximity()
    {
        int cellX = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field121388_0x469d4]
                        .x
            / 10;
        int cellY = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field121388_0x469d4]
                        .y
            / 10;
        this->casDisRelated = 1;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                this->grid[x][y].casDisRelated2 = 0;
            }
        }
        this->DAT_Y10_Array_Section1034[0] = (short)cellY;
        this->DAT_X10_Array_Section1034[0] = (short)cellX;
        int const areaID = this->grid[cellX][cellY].separateAreaID;
        this->grid[cellX][cellY].casDisRelated2 = 1;
        while (this->candidateIndex != this->candidateIndex2) {
            cellX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            cellY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            this->casDisRelated = this->grid[cellX][cellY].casDisRelated2;
            if ((int)this->casDisRelated >= 100) {
                return 0;
            }
            int const nextValue = this->casDisRelated + 1;
            for (int dir = 0; dir < 8; dir++) {
                uint const x = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + cellX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + cellY;
                if (x <= 39 && y <= 39 && this->grid[x][y].firstMember > 0
                    && areaID == this->grid[x][y].separateAreaID) {
                    if (this->grid[x][y].unknownNonZero01 != 0) {
                        return this->casDisRelated;
                    }
                    if (this->grid[x][y].casDisRelated2 == 0) {
                        this->grid[x][y].casDisRelated2 = nextValue;
                        this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)x;
                        this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)y;
                        this->candidateIndex2++;
                        if ((int)this->candidateIndex2 >= 0x640) {
                            this->candidateIndex2 = 0;
                        }
                    }
                }
            }
            this->candidateIndex++;
            if ((int)this->candidateIndex >= 0x640) {
                this->candidateIndex = 0;
            }
        }
        return 0;
    }

}
}
