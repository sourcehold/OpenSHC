/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LogicHelpers/Logic1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace LogicHelpers {
        typedef enum Logic1 {

            L_NONE = 0, // 0x00000000
            L_SEA = 1, // 0x00000001
            L_STOCKPILEUnk = 2, // 0x00000002
            L_PLAIN1_AND_FARM = 4, // 0x00000004
            L_PLAIN2_AND_PITCH = 8, // 0x00000008
            L_BORDER = 16, // 0x00000010
            L_BORDER_EDGE = 32, // 0x00000020
            L_ROCKY = 128, // 0x00000080
            L_WALL_OR_GATEHOUSE = 256, // 0x00000100
            L_CRENEL = 512, // 0x00000200
            L_BUILDING = 1024, // 0x00000400
            L_STAIRS = 2048, // 0x00000800
            L_TREE = 4096, // 0x00001000
            L_TREE_VARIATION = 8192, // 0x00002000
            L_MOAT_DUG_OR_PLANNED = 16384, // 0x00004000
            L_DEFAULT_EARTH_OR_TEXTURE = 32768, // 0x00008000
            L_UNKNOWN_WALL_RELATED = 65536, // 0x00010000
            L_BOULDERS = 131072, // 0x00020000
            L_PEBBLES = 262144, // 0x00040000
            L_IRON = 524288, // 0x00080000
            L_RIVER = 1048576, // 0x00100000
            L_FORD = 2097152, // 0x00200000
            L_CRENEL_VARIATIONUnk = 4194304, // 0x00400000
            L_FARM_FIELD_WHEAT = 16777216, // 0x01000000
            L_FARM_FIELD_HOP = 33554432, // 0x02000000
            L_FARM_FIELD_APPLE = 67108864, // 0x04000000
            L_FARM_FIELD_DAIRY = 134217728, // 0x08000000
            L_KEEP_NON_MANOR_HOUSE = 268435456, // 0x10000000
            L_MARSH = 536870912, // 0x20000000
            L_MOAT = 1073741824, // 0x40000000
            L_OIL = 2147483648, // 0x80000000
            Logic1Int__L_LADDER = 8388608 // 0x00800000

        } Logic1;

        static_assert_cpp98_obj(sizeof(Logic1) == 4, Logic1);
    } // namespace LogicHelpers
} // namespace Map
} // namespace OpenSHC
