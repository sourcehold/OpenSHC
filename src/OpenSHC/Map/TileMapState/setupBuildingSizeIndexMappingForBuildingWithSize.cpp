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
        int const maxCoord = buildingSize - 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            4056, 0, DAT_BuildingSizeIndexMapping::instance + buildingSize);
        if (buildingSize <= 1) {
            return;
        }

        // pass 0: the unrotated footprint, in reading order
        for (int y = 0; y < buildingSize; y++) {
            for (int x = 0; x < buildingSize; x++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x].x = x;
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x].y = y;
            }
        }

        // passes 1 to 4: the same tiles walked diagonally, one pass per rotation
        int const last = tileCount - 1;
        int x = 0;
        int y = 0;
        int run;
        int index = last;
        int diagonal;
        for (diagonal = 0, run = 1; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x].orientedPartIndex[0] = index;
                index--;
                if (step < run - 1) {
                    x--;
                    y++;
                }
            }
            if (diagonal < buildingSize - 1) {
                run++;
                x = diagonal + 1;
                y = 0;
            } else {
                run--;
                x = maxCoord;
                y = 1 - maxCoord + diagonal;
            }
        }

        x = maxCoord;
        y = 0;
        index = last;
        for (diagonal = 0, run = 1; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x].orientedPartIndex[1] = index;
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
                x = maxCoord + (buildingSize - 2) - diagonal;
                y = maxCoord;
            }
        }

        x = maxCoord;
        y = maxCoord;
        int secondIndex = last;
        for (diagonal = 0, run = 1; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x].orientedPartIndex[2]
                    = secondIndex;
                secondIndex--;
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
                y = (buildingSize - 2 - diagonal) + maxCoord;
            }
        }

        x = 0;
        y = maxCoord;
        secondIndex = last;
        for (diagonal = 0, run = 1; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x].orientedPartIndex[3]
                    = secondIndex;
                secondIndex--;
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
