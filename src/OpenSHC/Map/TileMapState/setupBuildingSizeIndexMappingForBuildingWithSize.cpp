#include "../TileMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingSizeIndexMapping.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9590
    void TileMapState::setupBuildingSizeIndexMappingForBuildingWithSize(int buildingSize)
    {
        int const tileCount = buildingSize * buildingSize;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            4056, 0, DAT_BuildingSizeIndexMapping::instance + buildingSize);
        if (buildingSize <= 1) {
            return;
        }
        int const maxCoord = buildingSize - 1;

        // pass 0: the unrotated footprint, in reading order
        for (int y = 0; y < buildingSize; y++) {
            for (int x = 0; x < buildingSize; x++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][0] = x;
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][1] = y;
            }
        }

        // passes 1 to 4: the same tiles walked diagonally, one pass per rotation
        int const last = tileCount - 1;
        int x = 0;
        int y = 0;
        int run = 1;
        int index = last;
        int diagonal;
        for (diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][2] = index;
                index--;
                if (step < run - 1) {
                    x--;
                    y++;
                }
            }
            if (diagonal < maxCoord) {
                run++;
                y = 0;
                x = diagonal + 1;
            } else {
                run--;
                x = maxCoord;
                y = 1 - maxCoord + diagonal;
            }
        }

        x = maxCoord;
        y = 0;
        run = 1;
        index = last;
        for (diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][3] = index;
                index--;
                if (step < run - 1) {
                    x--;
                    y--;
                }
            }
            if (diagonal < maxCoord) {
                run++;
                x = maxCoord;
                y = diagonal + 1;
            } else {
                run--;
                x = maxCoord + buildingSize - 2 - diagonal;
                y = maxCoord;
            }
        }

        x = maxCoord;
        y = maxCoord;
        run = 1;
        index = last;
        for (diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][4] = index;
                index--;
                if (step < run - 1) {
                    x++;
                    y--;
                }
            }
            if (diagonal < maxCoord) {
                run++;
                x = buildingSize - 2 - diagonal;
                y = maxCoord;
            } else {
                run--;
                x = 0;
                y = maxCoord + (buildingSize - 2 - diagonal);
            }
        }

        x = 0;
        y = maxCoord;
        run = 1;
        index = last;
        for (diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][5] = index;
                index--;
                if (step < run - 1) {
                    x++;
                    y++;
                }
            }
            if (diagonal < maxCoord) {
                run++;
                x = 0;
                y = buildingSize - 2 - diagonal;
            } else {
                run--;
                x = 1 - maxCoord + diagonal;
                y = 0;
            }
        }
    }

}
}
