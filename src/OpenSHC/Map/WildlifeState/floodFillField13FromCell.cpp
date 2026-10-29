#include "OpenSHC/Map/WildlifeState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // BFS over the 40x40 grid writing field13_0x34 (+0x34). The start sets casDisRelated = 1 as the original does.
    // A dequeued value <= 1 ends the fill (signed jle 0x52C604); neighbours are tested with unsigned bounds (ja 0x27),
    // firstMember > 0 and a lower current value (signed jge 0x52C641). Queue indices wrap at 0x640 (signed jl).
    // The three queue fields are declared undefined4 (unsigned), so they are cast to int for the signed compares.
    // FUNCTION: STRONGHOLDCRUSADER 0x0052C570
    void WildlifeState::floodFillField13FromCell(int seedX, int seedY, int seedValue)
    {
        this->candidateIndex2 = 1;
        this->casDisRelated = 1;
        this->DAT_X10_Array_Section1034[0] = (short)seedX;
        this->DAT_Y10_Array_Section1034[0] = (short)seedY;
        this->candidateIndex = 0;
        this->grid[seedX][seedY].field13_0x34 = seedValue;
        while (this->candidateIndex != this->candidateIndex2) {
            seedX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            seedY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            this->casDisRelated = this->grid[seedX][seedY].field13_0x34;
            if ((int)this->casDisRelated <= 1) {
                return;
            }
            int const nextValue = this->casDisRelated - 1;
            for (int dir = 0; dir < 8; dir++) {
                unsigned int const x = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.xOffset + seedX;
                unsigned int const y = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[dir].int_.yOffset + seedY;
                if (x <= 39 && y <= 39 && this->grid[x][y].firstMember > 0 && this->grid[x][y].field13_0x34 < nextValue) {
                    this->grid[x][y].field13_0x34 = nextValue;
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
