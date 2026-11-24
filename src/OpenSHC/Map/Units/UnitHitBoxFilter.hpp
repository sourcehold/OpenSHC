/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/UnitHitBoxFilter.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        typedef enum UnitHitBoxFilter {

            UHBF_ANY = 0, // 0x00000000
            UHBF_ENEMY_TEAM = 1, // 0x00000001
            UHBF_OWN_SIEGE_ENGINE = 2, // 0x00000002
            UHBF_OWN = 3, // 0x00000003
            UHBF_ANY_PLAYER_SELECTABLE = 4, // 0x00000004
            UHBF_OWN_SELECTABLE = 5, // 0x00000005
            UHBF_OWN_LADDERMAN = 6 // 0x00000006

        } UnitHitBoxFilter;

        static_assert_cpp98_obj(sizeof(UnitHitBoxFilter) == 4, UnitHitBoxFilter);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
