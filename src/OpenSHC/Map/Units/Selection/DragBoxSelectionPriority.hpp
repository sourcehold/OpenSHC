/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/Selection/DragBoxSelectionPriority.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Selection {
            typedef enum DragBoxSelectionPriority {

                DBSP_OWN_UNITS = 0, // 0x00000000
                DBSP_CATAPULTS = 1, // 0x00000001
                DBSP_TREBUCHETS = 2, // 0x00000002
                DBSP_SIEGE_TOWERS = 3, // 0x00000003
                DBSP_BATTERING_RAMS = 4, // 0x00000004
                DBSP_SHIELDS = 5, // 0x00000005
                DBSP_MANGONELS = 6, // 0x00000006
                DBSP_BALLISTAS = 7, // 0x00000007
                DBSP_FIRE_BALLISTAS = 8, // 0x00000008
                DBSP_OTHER_PLAYERS_UNITS = 9 // 0x00000009

            } DragBoxSelectionPriority;

            static_assert_cpp98_obj(sizeof(DragBoxSelectionPriority) == 4, DragBoxSelectionPriority);
        } // namespace Selection
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
