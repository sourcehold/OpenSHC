/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState_Miller.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState_Miller {

                USM_PICKING_UP_WHEAT = 3, // 0x00000003
                USM_RETURNING_WITH_WHEAT = 4, // 0x00000004
                USM_AWAITING_SPACE = 7, // 0x00000007
                USM_DEPOSITING_FLOUR = 8 // 0x00000008

            } UnitState_Miller;

            static_assert_cpp98_obj(sizeof(UnitState_Miller) == 4, UnitState_Miller);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
