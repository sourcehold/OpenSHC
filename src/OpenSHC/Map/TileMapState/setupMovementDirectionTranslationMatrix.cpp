#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6B20
    void TileMapState::setupMovementDirectionTranslationMatrix()
    {
        // the map is a diamond: rows grow by two tiles up to the two middle rows 199 and 200, then shrink
        int width = 2;
        for (int row = 0; width < 400; row++) {
            int (&offsets)[8] = this->directionTranslationMatrix[row];
            offsets[0] = 1 - width;
            offsets[1] = 2 - width;
            offsets[2] = 1;
            offsets[3] = width + 2;
            offsets[4] = width + 1;
            offsets[5] = width;
            offsets[6] = -1;
            offsets[7] = -width;
            this->yArray1[row] = width;
            width += 2;
        }

        int (&upperMiddle)[8] = this->directionTranslationMatrix[199];
        upperMiddle[0] = 1 - width;
        upperMiddle[1] = 2 - width;
        upperMiddle[2] = 1;
        upperMiddle[3] = width + 1;
        upperMiddle[4] = width;
        upperMiddle[5] = width - 1;
        upperMiddle[6] = -1;
        upperMiddle[7] = -width;
        this->yArray1[199] = width;
        int (&lowerMiddle)[8] = this->directionTranslationMatrix[200];
        lowerMiddle[0] = -width;
        lowerMiddle[1] = 1 - width;
        lowerMiddle[2] = 1;
        lowerMiddle[3] = width;
        lowerMiddle[4] = width - 1;
        lowerMiddle[5] = width - 2;
        lowerMiddle[6] = -1;
        lowerMiddle[7] = -1 - width;
        this->yArray1[200] = width;

        int row = 201;
        for (int lowerWidth = width - 2; lowerWidth > 0; lowerWidth -= 2) {
            int (&offsets)[8] = this->directionTranslationMatrix[row];
            offsets[0] = -1 - lowerWidth;
            offsets[1] = -lowerWidth;
            offsets[2] = 1;
            offsets[3] = lowerWidth;
            offsets[4] = lowerWidth - 1;
            offsets[5] = lowerWidth - 2;
            offsets[6] = -1;
            offsets[7] = -2 - lowerWidth;
            this->yArray1[row] = lowerWidth;
            row++;
        }
    }

}
}
