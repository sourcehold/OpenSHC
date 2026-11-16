/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LogicHelpers/MiscDisplay.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace LogicHelpers {
        typedef enum MiscDisplay {

            MD_SEA_CLIFF = 64, // 0x00000040
            MD_SEA_UNNAMED_0x80 = 128, // 0x00000080
            MD_SEA_SHORE = 256, // 0x00000100
            MD_SEA_SHORE_EDGE = 512, // 0x00000200
            MD_SEA_EDGES = 960 // 0x000003C0

        } MiscDisplay;

        static_assert_cpp98_obj(sizeof(MiscDisplay) == 4, MiscDisplay);
    } // namespace LogicHelpers
} // namespace Map
} // namespace OpenSHC
