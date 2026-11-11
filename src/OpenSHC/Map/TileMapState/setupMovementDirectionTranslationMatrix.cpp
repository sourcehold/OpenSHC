#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6B20
    void TileMapState::setupMovementDirectionTranslationMatrix()
    {
        // the map is a diamond: rows grow by two tiles up to the two middle rows 199 and 200, then shrink
        int width = 2;
        for (int row = 0; width < 400; row++) {
            this->directionTranslationMatrix[row][0] = 1 - width;
            this->directionTranslationMatrix[row][1] = 2 - width;
            this->directionTranslationMatrix[row][2] = 1;
            this->directionTranslationMatrix[row][3] = width + 2;
            this->directionTranslationMatrix[row][4] = width + 1;
            this->directionTranslationMatrix[row][5] = width;
            this->directionTranslationMatrix[row][6] = -1;
            this->directionTranslationMatrix[row][7] = -width;
            this->yArray1[row] = width;
            width += 2;
        }

        this->directionTranslationMatrix[199][0] = 1 - width;
        this->directionTranslationMatrix[199][1] = 2 - width;
        this->directionTranslationMatrix[199][2] = 1;
        this->directionTranslationMatrix[199][3] = width + 1;
        this->directionTranslationMatrix[199][4] = width;
        this->directionTranslationMatrix[199][5] = width - 1;
        this->directionTranslationMatrix[199][6] = -1;
        this->directionTranslationMatrix[199][7] = -width;
        this->yArray1[199] = width;
        this->directionTranslationMatrix[200][0] = -width;
        this->directionTranslationMatrix[200][1] = 1 - width;
        this->directionTranslationMatrix[200][2] = 1;
        this->directionTranslationMatrix[200][3] = width;
        this->directionTranslationMatrix[200][4] = width - 1;
        this->directionTranslationMatrix[200][5] = width - 2;
        this->directionTranslationMatrix[200][6] = -1;
        this->directionTranslationMatrix[200][7] = -1 - width;
        this->yArray1[200] = width;

        int row = 201;
        for (int lowerWidth = width - 2; lowerWidth > 0; lowerWidth -= 2) {
            this->directionTranslationMatrix[row][0] = -1 - lowerWidth;
            this->directionTranslationMatrix[row][1] = -lowerWidth;
            this->directionTranslationMatrix[row][2] = 1;
            this->directionTranslationMatrix[row][3] = lowerWidth;
            this->directionTranslationMatrix[row][4] = lowerWidth - 1;
            this->directionTranslationMatrix[row][5] = lowerWidth - 2;
            this->directionTranslationMatrix[row][6] = -1;
            this->directionTranslationMatrix[row][7] = -2 - lowerWidth;
            this->yArray1[row] = lowerWidth;
            row++;
        }
    }

}
}
