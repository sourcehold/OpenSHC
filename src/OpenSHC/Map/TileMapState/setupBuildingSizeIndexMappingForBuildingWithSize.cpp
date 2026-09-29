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
        int size = buildingSize;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            4056, '\0', DAT_BuildingSizeIndexMapping::instance + buildingSize);
        int last = buildingSize * buildingSize + -1;
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

        int diagonals = buildingSize * 2 + -1;

        /* passes 1 to 4: the same tiles walked diagonally, one pass per rotation */
        int column = 0;
        int base = 0;
        int run = 1;
        int index = last;
        for (int diagonal = 0; diagonal < diagonals; diagonal++) {
            for (int step = 0; step < run; step++) {
                if (step == 0) {
                    base = (base + 169) * buildingSize;
                }
                DAT_BuildingSizeIndexMapping::instance[0][base + column][2] = index;
                index = index + -1;
                if (step < run + -1) {
                    column = column + -1;
                    base = base + buildingSize;
                }
            }
            column = buildingSize + -1;
            if (diagonal < column) {
                run = run + 1;
                column = diagonal + 1;
                base = 0;
            } else {
                run = run + -1;
                base = (1 - (buildingSize + -1)) + diagonal;
            }
        }

        int row = buildingSize + -1;
        base = 0;
        run = 1;
        index = last;
        int mirror = buildingSize * 2 + -3;
        for (int diagonal = 0; diagonal < diagonals; diagonal++) {
            for (int step = 0; step < run; step++) {
                if (step == 0) {
                    base = (base + 0xa9) * buildingSize;
                }
                DAT_BuildingSizeIndexMapping::instance[0][base + row][3] = index;
                index = index + -1;
                if (step < run + -1) {
                    row = row + -1;
                    base = base - buildingSize;
                }
            }
            row = buildingSize + -1;
            if (diagonal < row) {
                run = run + 1;
                base = diagonal + 1;
            } else {
                run = run + -1;
                base = row;
                row = mirror;
            }
            mirror = mirror + -1;
        }

        base = buildingSize + -1;
        run = 1;
        index = last;
        mirror = buildingSize + -2;
        column = base;
        for (int diagonal = 0; diagonal < diagonals; diagonal++) {
            for (int step = 0; step < run; step++) {
                if (step == 0) {
                    base = (base + 0xa9) * buildingSize;
                }
                DAT_BuildingSizeIndexMapping::instance[0][base + column][4] = index;
                index = index + -1;
                if (step < run + -1) {
                    column = column + 1;
                    base = base - buildingSize;
                }
            }
            base = buildingSize + -1;
            if (diagonal < base) {
                run = run + 1;
                column = mirror;
            } else {
                run = run + -1;
                column = 0;
                base = mirror + base;
            }
            mirror = mirror + -1;
        }

        base = buildingSize + -1;
        column = 0;
        run = 1;
        index = last;
        int shrink = buildingSize + -2;
        int offset = 1 - base;
        for (int diagonal = 0; diagonal < size * 2 + -1; diagonal++) {
            for (int step = 0; step < run; step++) {
                if (step == 0) {
                    base = (base + 0xa9) * size;
                }
                DAT_BuildingSizeIndexMapping::instance[0][base + column][5] = index;
                index = index + -1;
                if (step < run + -1) {
                    column = column + 1;
                    base = base + size;
                }
            }
            if (diagonal < size + -1) {
                run = run + 1;
                column = 0;
                base = shrink;
            } else {
                run = run + -1;
                column = offset + diagonal;
                base = 0;
            }
            shrink = shrink + -1;
        }
    }

}
}
