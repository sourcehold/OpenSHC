/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIVUnitType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIVUnitType {

        AIVUT_NONE = 0, // 0x00000000
        AIVUT_ENGINEER = 1, // 0x00000001
        AIVUT_MANGONEL = 2, // 0x00000002
        AIVUT_BALLISTA = 3, // 0x00000003
        AIVUT_TREBUCHET = 4, // 0x00000004
        AIVUT_FIRE_BALLISTA = 5, // 0x00000005
        AIVUT_ARCHER = 6, // 0x00000006
        AIVUT_CROSSBOWMAN = 7, // 0x00000007
        AIVUT_SPEARMAN = 8, // 0x00000008
        AIVUT_PIKEMAN = 9, // 0x00000009
        AIVUT_MACEMAN = 10, // 0x0000000A
        AIVUT_SWORDSMAN = 11, // 0x0000000B
        AIVUT_KNIGHT = 12, // 0x0000000C
        AIVUT_SLAVE = 13, // 0x0000000D
        AIVUT_SLINGER = 14, // 0x0000000E
        AIVUT_ASSASSIN = 15, // 0x0000000F
        AIVUT_ARABIAN_ARCHER = 16, // 0x00000010
        AIVUT_HORSE_ARCHER = 17, // 0x00000011
        AIVUT_ARABIAN_SWORDSMAN = 18, // 0x00000012
        AIVUT_FIRE_THROWER = 19, // 0x00000013
        AIVUT_BRAZIER = 20, // 0x00000014
        AIVUT_FLAG = 21 // 0x00000015

    } AIVUnitType;

    static_assert_cpp98_obj(sizeof(AIVUnitType) == 4, AIVUnitType);
} // namespace AI
} // namespace OpenSHC
