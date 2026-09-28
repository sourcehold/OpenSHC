#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2050
    void ViewportRenderState::setTileSystemMemoryLookupArrays()
    {
        int diagonal;
        int savedDestOffset2;
        int scratch6;
        int scratch7;
        int runRemaining;
        int destIndex;
        int firstHalfIndex;
        int secondHalfIndex;
        int rowBase;
        int blockRemaining;
        int diagonalBase;
        int tileGrid[160000];
        int column;

        int tileNumber = 0;
        for (int i = 0; i < 160000; i++) {
            tileGrid[i] = 0;
        }

        int rowFirstColumn = 199;
        int rowWidth = 2;
        int rowStart = 0;
        int rowSpan = 398;
        for (int row = 0; rowStart < 80000; row++) {
            this->translationMatrix[row].distanceToCenter = rowSpan / 2;
            this->translationMatrix[row].firstTileOfRow = tileNumber;
            this->translationMatrix[row].addXgetTile = tileNumber - rowSpan / 2;
            if (0 < rowWidth) {
                for (int column = 0; column < rowWidth; column++) {
                    tileGrid[rowFirstColumn + rowStart + column] = tileNumber;
                    tileNumber = tileNumber + 1;
                }
            }
            rowSpan = rowSpan + -2;
            rowFirstColumn = rowFirstColumn + -1;
            rowStart = rowStart + 400;
            rowWidth = rowWidth + 2;
        }

        rowStart = 80000;
        rowSpan = 400 - rowWidth;
        for (int row = 200; rowStart < 160000; row++) {
            rowFirstColumn = rowFirstColumn + 1;
            rowSpan = rowSpan + 2;
            rowWidth = rowWidth + -2;
            this->translationMatrix[row].distanceToCenter = rowSpan / 2;
            this->translationMatrix[row].firstTileOfRow = tileNumber;
            this->translationMatrix[row].addXgetTile = tileNumber - rowSpan / 2;
            if (0 < rowWidth) {
                for (int column = 0; column < rowWidth; column++) {
                    tileGrid[rowStart + rowFirstColumn + column] = tileNumber;
                    tileNumber = tileNumber + 1;
                }
            }
            rowStart = rowStart + 400;
        }
        this->translationTracker1 = tileNumber;
        this->translationResult1 = (400 - rowWidth) / 2;
        this->translationResult2 = tileNumber - this->translationResult1;
        this->field9_0x4e5e0 = 0;
        this->field10_0x4e5e4 = 0;
        this->field11_0x4e5e8 = 0;
        this->field12_0x4e5ec = 0;
        this->field13_0x4e5f0 = 0;
        this->field14_0x4e5f4 = 0;
        this->field15_0x4e5f8 = 0;
        this->field16_0x4e5fc = 0;
        runRemaining = 200;
        rowBase = 0;
        diagonalBase = 79600;
        destIndex = 0;
        column = 8;
        do {
            scratch7 = column;
            scratch6 = 200;
            secondHalfIndex = destIndex + 200;
            firstHalfIndex = destIndex;
            column = rowBase;
            diagonal = diagonalBase;
            do {
                this->screenPointToTileNumber[firstHalfIndex] = tileGrid[diagonal + column];
                scratch6 = scratch6 + -1;
                firstHalfIndex = firstHalfIndex + 1;
                diagonal = diagonal + -400;
                column = column + 1;
            } while (0 < scratch6);
            diagonalBase = diagonalBase + 400;
            destIndex = destIndex + 401;
            scratch6 = 200;
            column = rowBase;
            diagonal = diagonalBase;
            do {
                this->screenPointToTileNumber[secondHalfIndex] = tileGrid[diagonal + column];
                scratch6 = scratch6 + -1;
                secondHalfIndex = secondHalfIndex + 1;
                column = column + 1;
                diagonal = diagonal + -400;
            } while (-1 < scratch6);
            runRemaining = runRemaining + -1;
            rowBase = rowBase + 1;
            column = scratch7 + 401;
        } while (0 < runRemaining);
        column = 200;
        destIndex = scratch7 + 393;
        diagonal = 159600;
        do {
            this->screenPointToTileNumber[destIndex] = tileGrid[diagonal + rowBase];
            column = column + -1;
            destIndex = destIndex + 1;
            rowBase = rowBase + 1;
            diagonal = diagonal + -400;
        } while (0 < column);
        rowBase = 399;
        diagonalBase = 0x26f70;
        destIndex = scratch7 + 0x251;
        blockRemaining = 200;
        column = scratch7 + 0x259;
        diagonal = 199;
        do {
            scratch6 = column;
            runRemaining = 200;
            secondHalfIndex = destIndex + 200;
            firstHalfIndex = destIndex;
            column = diagonal;
            scratch7 = diagonalBase;
            do {
                this->screenPointToTileNumber[firstHalfIndex] = tileGrid[scratch7 + column];
                firstHalfIndex = firstHalfIndex + 1;
                column = column + -1;
                scratch7 = scratch7 + -400;
                runRemaining = runRemaining + -1;
            } while (runRemaining != 0);
            scratch7 = diagonal + 1;
            runRemaining = (scratch7 - diagonal) + 199;
            diagonal = ((scratch7 - diagonal) + rowBase) * 400;
            destIndex = destIndex + 0x191;
            column = scratch7;
            do {
                diagonal = diagonal + -400;
                this->screenPointToTileNumber[secondHalfIndex] = tileGrid[diagonal + column];
                secondHalfIndex = secondHalfIndex + 1;
                column = column + -1;
                runRemaining = runRemaining + -1;
            } while (-1 < runRemaining);
            rowBase = rowBase + -1;
            diagonalBase = diagonalBase + -400;
            blockRemaining = blockRemaining + -1;
            column = scratch6 + 0x191;
            diagonal = scratch7;
        } while (blockRemaining != 0);
        column = rowBase * 400;
        diagonal = 200;
        destIndex = scratch6 + 0x189;
        do {
            this->screenPointToTileNumber[destIndex] = tileGrid[column + scratch7];
            destIndex = destIndex + 1;
            scratch7 = scratch7 + -1;
            column = column + -400;
            diagonal = diagonal + -1;
        } while (diagonal != 0);
        scratch7 = 199;
        column = 80000;
        destIndex = scratch6 + 0x251;
        diagonal = scratch6 + 0x259;
        do {
            savedDestOffset2 = diagonal;
            scratch6 = 200;
            secondHalfIndex = destIndex + 200;
            firstHalfIndex = destIndex;
            diagonal = column;
            do {
                this->screenPointToTileNumber[firstHalfIndex] = tileGrid[scratch7 + diagonal + scratch6];
                scratch6 = scratch6 + -1;
                firstHalfIndex = firstHalfIndex + 1;
                diagonal = diagonal + 400;
            } while (0 < scratch6);
            column = column + -400;
            scratch6 = 200;
            destIndex = destIndex + 0x191;
            diagonal = column;
            do {
                this->screenPointToTileNumber[secondHalfIndex] = tileGrid[scratch7 + diagonal + scratch6];
                secondHalfIndex = secondHalfIndex + 1;
                diagonal = diagonal + 400;
                scratch6 = scratch6 + -1;
            } while (-1 < scratch6);
            scratch7 = scratch7 + -1;
            diagonal = savedDestOffset2 + 0x191;
        } while (0 < column);
        column = 200;
        diagonal = 0;
        destIndex = savedDestOffset2 + 0x189;
        do {
            this->screenPointToTileNumber[destIndex] = tileGrid[diagonal + -1 + column];
            column = column + -1;
            destIndex = destIndex + 1;
            diagonal = diagonal + 400;
        } while (0 < column);
        rowBase = 0;
        diagonalBase = 0;
        destIndex = savedDestOffset2 + 0x251;
        column = 200;
        diagonal = savedDestOffset2 + 0x259;
        do {
            scratch6 = diagonal;
            savedDestOffset2 = 200;
            secondHalfIndex = destIndex + 200;
            firstHalfIndex = destIndex;
            diagonal = column;
            scratch7 = diagonalBase;
            do {
                this->screenPointToTileNumber[firstHalfIndex] = tileGrid[scratch7 + diagonal];
                savedDestOffset2 = savedDestOffset2 + -1;
                firstHalfIndex = firstHalfIndex + 1;
                diagonal = diagonal + 1;
                scratch7 = scratch7 + 400;
            } while (0 < savedDestOffset2);
            scratch7 = column + -1;
            diagonal = ((scratch7 - column) + 1 + rowBase) * 400;
            runRemaining = 200;
            destIndex = destIndex + 0x191;
            column = scratch7;
            do {
                this->screenPointToTileNumber[secondHalfIndex] = tileGrid[diagonal + column];
                secondHalfIndex = secondHalfIndex + 1;
                column = column + 1;
                diagonal = diagonal + 400;
                runRemaining = runRemaining + -1;
            } while (-1 < runRemaining);
            rowBase = rowBase + 1;
            diagonalBase = diagonalBase + 400;
            column = scratch7;
            diagonal = scratch6 + 0x191;
        } while (0 < scratch7);
        column = rowBase * 400;
        diagonal = 200;
        destIndex = scratch6 + 0x189;
        do {
            this->screenPointToTileNumber[destIndex] = tileGrid[column + scratch7];
            diagonal = diagonal + -1;
            destIndex = destIndex + 1;
            scratch7 = scratch7 + 1;
            column = column + 400;
        } while (0 < diagonal);
        for (int y = 0; y < 400; y++) {
            for (int x = 0; x < 400; x++) {
                this->DAT_BinaryTileMap400x400[y * 400 + x] = (0 < tileGrid[y * 400 + x]);
            }
        }
    }

}
}
