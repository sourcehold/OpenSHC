/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum UnitState {

                US_DETERMINE_NEXT_STATEUnk = 0, // 0x00000000
                US_IDLEUnk = 1, // 0x00000001
                US_RELOAD_WEAPONUnk = 4, // 0x00000004
                US_AIM_WEAPONUnk = 5, // 0x00000005
                US_FIRE_WEAPONUnk = 6, // 0x00000006
                US_LOOK_AROUNDUnk = 7, // 0x00000007
                US_STAND_UPUnk = 8, // 0x00000008
                US_SIT_DOWNUnk = 11, // 0x0000000B
                US_MOVE_TO_DESTINATION = 101, // 0x00000065
                US_MELEE_ATTACK = 106, // 0x0000006A
                US_MELEE_ATTACK_WALL = 107, // 0x0000006B
                US_JESTER_ROAM_TO = 109, // 0x0000006D
                US_DISAPPEAR = 110, // 0x0000006E
                US_DEATH_01 = 111, // 0x0000006F
                US_DEATH_02 = 112, // 0x00000070
                US_DEATH_03 = 113, // 0x00000071
                US_STONE_DEATH_01 = 114, // 0x00000072
                US_STONE_DEATH_02 = 115, // 0x00000073
                US_STONE_DEATH_03 = 116, // 0x00000074
                US_APPEAR = 122, // 0x0000007A
                US_DIG = 125, // 0x0000007D
                US_ASSASSIN_THROWING_HOOK = 126, // 0x0000007E
                US_ASSASSIN_CLIMBING_UP = 127, // 0x0000007F
                US_ASSASSIN_START_CLIMBING_DOWN = 128, // 0x00000080
                US_ASSASSIN_CLIMBING_DOWN = 129, // 0x00000081
                UnitStateInt__US_APPLEFARMER_PLUCK_APPLES = 2, // 0x00000002
                UnitStateInt__US_Appear = 122, // 0x0000007A
                UnitStateInt__US_Dig = 125 // 0x0000007D

            } UnitState;

            static_assert_cpp98_obj(sizeof(UnitState) == 4, UnitState);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
