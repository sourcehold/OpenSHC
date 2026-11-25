/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LogicHelpers/WallOwner.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace LogicHelpers {
        typedef enum WallOwner {

            WO_OWNER_MASK = 7, // 0x00000007
            WO_DAMAGED_WALL_GFXUnk = 8 // 0x00000008

        } WallOwner;

        static_assert_cpp98_obj(sizeof(WallOwner) == 4, WallOwner);
    } // namespace LogicHelpers
} // namespace Map
} // namespace OpenSHC
