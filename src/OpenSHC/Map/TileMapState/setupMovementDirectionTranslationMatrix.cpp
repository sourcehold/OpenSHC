#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6B20
    void TileMapState::setupMovementDirectionTranslationMatrix()
    {
        /*
          Ghidra rendered the two running values of the first loop as directionTranslationMatrix[199][4]
          and [200][5]; in the original they are registers, and rows 199 and 200 are only written by
          the block after the loop. Rows 0..198 count up in "step" and down in "counter", rows 201.. count
          back down again.
        */
        int step = 2;
        int counter = 0;
        int row = 0;
        do {
            this->directionTranslationMatrix[row][0] = counter - 1;
            this->directionTranslationMatrix[row][3] = step + 2;
            this->directionTranslationMatrix[row][4] = step + 1;
            this->directionTranslationMatrix[row][1] = counter;
            this->directionTranslationMatrix[row][5] = step;
            this->directionTranslationMatrix[row][2] = 1;
            this->directionTranslationMatrix[row][6] = -1;
            this->directionTranslationMatrix[row][7] = counter - 2;
            this->yArray1[row] = step;
            counter = counter - 2;
            step = step + 2;
            row++;
        } while (counter > -398);

        this->directionTranslationMatrix[199][1] = 2 - step;
        this->directionTranslationMatrix[199][4] = step;
        this->directionTranslationMatrix[199][6] = -1;
        this->directionTranslationMatrix[199][2] = 1;
        this->directionTranslationMatrix[199][3] = step + 1;
        this->directionTranslationMatrix[199][0] = 1 - step;
        this->directionTranslationMatrix[199][7] = -step;
        this->directionTranslationMatrix[199][5] = step - 1;
        this->yArray1[199] = step;
        this->directionTranslationMatrix[200][0] = -step;
        this->directionTranslationMatrix[200][1] = 1 - step;
        this->directionTranslationMatrix[200][2] = 1;
        this->directionTranslationMatrix[200][3] = step;
        this->directionTranslationMatrix[200][4] = step - 1;
        this->directionTranslationMatrix[200][5] = step - 2;
        this->directionTranslationMatrix[200][6] = -1;
        this->directionTranslationMatrix[200][7] = -1 - step;
        this->yArray1[200] = step;

        if (step - 2 > 0) {
            int lowerStep = step - 2;
            int lowerCounter = -2 - lowerStep;
            int lowerRow = 201;
            do {
                this->directionTranslationMatrix[lowerRow][0] = lowerCounter + 1;
                this->directionTranslationMatrix[lowerRow][1] = lowerCounter + 2;
                this->directionTranslationMatrix[lowerRow][4] = lowerStep - 1;
                this->directionTranslationMatrix[lowerRow][3] = lowerStep;
                this->directionTranslationMatrix[lowerRow][7] = lowerCounter;
                this->directionTranslationMatrix[lowerRow][2] = 1;
                this->directionTranslationMatrix[lowerRow][5] = lowerStep - 2;
                this->directionTranslationMatrix[lowerRow][6] = -1;
                this->yArray1[lowerRow] = lowerStep;
                lowerStep = lowerStep - 2;
                lowerCounter = lowerCounter + 2;
                lowerRow++;
            } while (lowerStep > 0);
        }
    }

}
}
