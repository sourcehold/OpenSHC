#include "../ViewportRenderState.func.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2050
    void ViewportRenderState::setTileSystemMemoryLookupArrays()
    {
        int tileNumber = 0;
        int tileGrid[160000];
        for (int i = 0; i < 160000; i++) {
            tileGrid[i] = 0;
        }

        // the map is a diamond: rows grow by two tiles down to the middle, then shrink again
        int rowFirstColumn = 199;
        int rowWidth = 2;
        int rowSpan = 398;
        int row;
        for (row = 0; row < 200; row++) {
            this->translationMatrix[row].distanceToCenter = rowSpan / 2;
            this->translationMatrix[row].firstTileOfRow = tileNumber;
            this->translationMatrix[row].addXgetTile = tileNumber - rowSpan / 2;
            for (int column = 0; column < rowWidth; column++) {
                tileGrid[rowFirstColumn + row * 400 + column] = tileNumber;
                tileNumber++;
            }
            rowSpan -= 2;
            rowFirstColumn--;
            rowWidth += 2;
        }
        rowSpan = 400 - rowWidth;
        for (; row < 400; row++) {
            rowFirstColumn++;
            rowSpan += 2;
            rowWidth -= 2;
            this->translationMatrix[row].distanceToCenter = rowSpan / 2;
            this->translationMatrix[row].firstTileOfRow = tileNumber;
            this->translationMatrix[row].addXgetTile = tileNumber - rowSpan / 2;
            for (int column = 0; column < rowWidth; column++) {
                tileGrid[row * 400 + rowFirstColumn + column] = tileNumber;
                tileNumber++;
            }
        }
        this->translationMatrix[row].distanceToCenter = (400 - rowWidth) / 2;
        this->translationMatrix[row].firstTileOfRow = tileNumber;
        this->translationMatrix[row].addXgetTile = tileNumber - (400 - rowWidth) / 2;

        for (int i = 0; i < 8; i++) {
            this->screenPointToTileNumber[i] = 0;
        }
        int screenIndex = 8;

        // orientation 0
        int startX = 0;
        int startY = 199 * 400;
        for (int r = 200; r > 0; r--) {
            int x = startX;
            int y = startY;
            for (int n = 200; n > 0; n--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + x];
                x++;
                y -= 400;
            }
            startY += 400;
            x = startX;
            y = startY;
            for (int n = 200; n >= 0; n--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + x];
                x++;
                y -= 400;
            }
            startX++;
        }
        for (int y = 399 * 400, n = 200; n > 0; n--) {
            this->screenPointToTileNumber[screenIndex++] = tileGrid[y + startX];
            startX++;
            y -= 400;
        }

        // orientation 6
        startX = 199;
        startY = 399;
        for (int r = 0; r < 200; r++) {
            int x = startX;
            int y = startY * 400;
            for (int n = 0; n < 200; n++) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + x];
                x--;
                y -= 400;
            }
            int const nextStartX = startX + 1;
            x = nextStartX;
            y = (nextStartX - startX + startY) * 400;
            int n = nextStartX - startX + 199;
            do {
                y -= 400;
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + x];
                x--;
                n--;
            } while (n >= 0);
            startX = nextStartX;
            startY--;
        }
        {
            int y = startY * 400;
            for (int n = 0; n < 200; n++) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + startX];
                startX--;
                y -= 400;
            }
        }

        // orientation 4
        int column = 199;
        for (int rowBase = 80000; rowBase > 0;) {
            int y = rowBase;
            for (int dx = 200; dx > 0; dx--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[column + y + dx];
                y += 400;
            }
            rowBase -= 400;
            y = rowBase;
            for (int dx = 200; dx >= 0; dx--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[column + y + dx];
                y += 400;
            }
            column--;
        }
        for (int y = 0, dx = 200; dx > 0; dx--) {
            this->screenPointToTileNumber[screenIndex++] = tileGrid[y + dx - 1];
            y += 400;
        }

        // orientation 2
        int rowY = 0;
        int startColumn = 200;
        do {
            int x = startColumn;
            int y = rowY * 400;
            for (int n = 200; n > 0; n--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + x];
                x++;
                y += 400;
            }
            int const nextStartColumn = startColumn - 1;
            x = nextStartColumn;
            y = (nextStartColumn - startColumn + 1 + rowY) * 400;
            for (int n = 200; n >= 0; n--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + x];
                x++;
                y += 400;
            }
            rowY++;
            startColumn = nextStartColumn;
        } while (startColumn > 0);
        {
            int y = rowY * 400;
            for (int n = 200; n > 0; n--) {
                this->screenPointToTileNumber[screenIndex++] = tileGrid[y + startColumn];
                startColumn++;
                y += 400;
            }
        }

        for (int y = 0; y < 400; y++) {
            for (int x = 0; x < 400; x++) {
                this->DAT_BinaryTileMap400x400[y * 400 + x] = tileGrid[y * 400 + x] > 0;
            }
        }
    }

}
}
