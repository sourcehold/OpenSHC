#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    // BFS from the cell of the active attack signpost (tileUnk / 10, signed idiv by 10) writing the step distance into
    // casDisRelated2 (start = 1). A dequeued distance >= 100 ends the fill (signed jge 0x52DAD7). Neighbours need
    // unsigned bounds (ja 0x27), firstMember > 0, the start cell's separateAreaID, unknownNonZero01 == 0 and
    // casDisRelated2 == 0; each entered cell also gets field_0x74 incremented. The original leaves the last
    // compared value in eax, the only caller (updateNofFpoints, 0x52E18B) does not read it.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D9D0
    void WildlifeState::floodFillCasDisFromSignpost()
    {
        int cellX = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field_0x469d4]
                        .x
            / 10;
        int cellY = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field_0x469d4]
                        .y
            / 10;
        this->casDisRelated = 1;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        for (int y = 0; y < countof(this->grid[0]); y++) {
            for (int x = 0; x < countof(this->grid); x++) {
                this->grid[x][y].casDisRelated2 = 0;
                this->grid[x][y].field_0x74 = 0;
            }
        }
        this->DAT_Y10_Array_Section1034[0] = cellY;
        this->DAT_X10_Array_Section1034[0] = cellX;
        int const areaID = this->grid[cellX][cellY].separateAreaID;
        this->grid[cellX][cellY].casDisRelated2 = 1;
        while (this->candidateIndex != this->candidateIndex2) {
            cellX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            cellY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            this->casDisRelated = this->grid[cellX][cellY].casDisRelated2;
            if (this->casDisRelated >= 100) {
                return;
            }
            int const nextValue = this->casDisRelated + 1;
            for (int dir = 0; dir < 8; dir++) {
                uint const x
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + cellX;
                uint const y
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + cellY;
                if (x <= 39 && y <= 39 && this->grid[x][y].firstMember > 0 && areaID == this->grid[x][y].separateAreaID
                    && this->grid[x][y].unknownNonZero01 == 0 && this->grid[x][y].casDisRelated2 == 0) {
                    this->grid[x][y].casDisRelated2 = nextValue;
                    this->grid[x][y].field_0x74++;
                    this->DAT_X10_Array_Section1034[this->candidateIndex2] = x;
                    this->DAT_Y10_Array_Section1034[this->candidateIndex2] = y;
                    this->candidateIndex2++;
                    if (this->candidateIndex2 >= 1600) {
                        this->candidateIndex2 = 0;
                    }
                }
            }
            this->candidateIndex++;
            if (this->candidateIndex >= 1600) {
                this->candidateIndex = 0;
            }
        }
    }

}
}
