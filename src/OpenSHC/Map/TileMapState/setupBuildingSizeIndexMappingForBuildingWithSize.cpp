#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingSizeIndexMapping.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9590
    void TileMapState::setupBuildingSizeIndexMappingForBuildingWithSize(int buildingSize)
    {
        int tileCount = buildingSize * buildingSize;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            4056, '\0', DAT_BuildingSizeIndexMapping::instance + buildingSize);
        if (buildingSize <= 1) {
            return;
        }

        /* pass 0: the unrotated footprint, in reading order */
        for (int y = 0; y < buildingSize; y++) {
            for (int x = 0; x < buildingSize; x++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][0] = x;
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][1] = y;
            }
        }

        /* passes 1 to 4: the same tiles walked diagonally, one pass per rotation */
        int last = tileCount - 1;
        int x = 0;
        int y = 0;
        int run = 1;
        int index = last;
        for (int diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][2] = index;
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
                x = buildingSize - 1;
                y = (1 - (buildingSize - 1)) + diagonal;
            }
        }

        x = buildingSize - 1;
        y = 0;
        run = 1;
        index = last;
        for (int diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][3] = index;
                index--;
                if (step < run - 1) {
                    x--;
                    y--;
                }
            }
            if (diagonal < buildingSize - 1) {
                run++;
                x = buildingSize - 1;
                y = diagonal + 1;
            } else {
                run--;
                x = (buildingSize - 1) + (buildingSize - 2) - diagonal;
                y = buildingSize - 1;
            }
        }

        x = buildingSize - 1;
        y = buildingSize - 1;
        run = 1;
        index = last;
        for (int diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][4] = index;
                index--;
                if (step < run - 1) {
                    x++;
                    y--;
                }
            }
            if (diagonal < buildingSize - 1) {
                run++;
                x = buildingSize - 2 - diagonal;
                y = buildingSize - 1;
            } else {
                run--;
                x = 0;
                y = (buildingSize - 2 - diagonal) + (buildingSize - 1);
            }
        }

        x = 0;
        y = buildingSize - 1;
        run = 1;
        index = last;
        for (int diagonal = 0; diagonal < buildingSize * 2 - 1; diagonal++) {
            for (int step = 0; step < run; step++) {
                DAT_BuildingSizeIndexMapping::instance[buildingSize][y * buildingSize + x][5] = index;
                index--;
                if (step < run - 1) {
                    x++;
                    y++;
                }
            }
            if (diagonal < buildingSize - 1) {
                run++;
                x = 0;
                y = buildingSize - 2 - diagonal;
            } else {
                run--;
                x = (1 - (buildingSize - 1)) + diagonal;
                y = 0;
            }
        }
    }

}
}
