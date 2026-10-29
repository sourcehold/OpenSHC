#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // BFS over the 40x40 grid writing unknownNonZero01 (+0x68). A dequeued value <= 1 ends the fill (signed jle
    // 0x52D7B4); neighbours need unsigned bounds (ja 0x27), firstMember > 0, unclaimedArea <= 10 (signed jg
    // 0x52D7F2) and a lower current value (signed jge 0x52D7F7). The queue indices are undefined4, so they are cast to
    // int for the signed wrap compares (jl 0x640).
    // FUNCTION: STRONGHOLDCRUSADER 0x0052D720
    void WildlifeState::floodFillZoneProximityFromCell(int cellX, int cellY, int strength)
    {
        this->candidateIndex2 = 1;
        this->casDisRelated = 1;
        this->DAT_X10_Array_Section1034[0] = (short)cellX;
        this->DAT_Y10_Array_Section1034[0] = (short)cellY;
        this->candidateIndex = 0;
        this->grid[cellX][cellY].unknownNonZero01 = strength;
        while (this->candidateIndex != this->candidateIndex2) {
            cellX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            cellY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            this->casDisRelated = this->grid[cellX][cellY].unknownNonZero01;
            if ((int)this->casDisRelated <= 1) {
                return;
            }
            int const nextValue = this->casDisRelated - 1;
            for (int dir = 0; dir < 8; dir++) {
                uint const x = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + cellX;
                uint const y = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + cellY;
                if (x <= 39 && y <= 39 && this->grid[x][y].firstMember > 0 && this->grid[x][y].unclaimedArea <= 10
                    && this->grid[x][y].unknownNonZero01 < nextValue) {
                    this->grid[x][y].unknownNonZero01 = nextValue;
                    this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)x;
                    this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)y;
                    this->candidateIndex2++;
                    if ((int)this->candidateIndex2 >= 0x640) {
                        this->candidateIndex2 = 0;
                    }
                }
            }
            this->candidateIndex++;
            if ((int)this->candidateIndex >= 0x640) {
                this->candidateIndex = 0;
            }
        }
    }

}
}
