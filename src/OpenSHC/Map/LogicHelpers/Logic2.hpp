/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LogicHelpers/Logic2.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace LogicHelpers {
        typedef enum Logic2 {

            L2_NONE = 0, // 0x00000000
            L2_SCRUB = 1, // 0x00000001
            L2_EARTH_AND_STONES = 2, // 0x00000002
            L2_MOAT_UNDUG = 3, // 0x00000003
            L2_PLATEAU_MEDIUM = 4, // 0x00000004
            L2_PLATEAU_HIGH = 8, // 0x00000008
            L2_OASIS_GRASS = 16, // 0x00000010
            L2_BEACH = 32, // 0x00000020
            L2_STONES_OR_DRIVEN_SANDUnk = 64, // 0x00000040
            L2_THICK_SCRUB = 128 // 0x00000080

        } Logic2;

        static_assert_cpp98_obj(sizeof(Logic2) == 4, Logic2);
    } // namespace LogicHelpers
} // namespace Map
} // namespace OpenSHC
