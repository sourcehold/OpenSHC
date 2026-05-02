/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIUnitBehaviourType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIUnitBehaviourType {

        AIUBT_PATROL = 4, // 0x00000004
        AIUBT_ENGINEERING = 10, // 0x0000000A
        AIUBT_DIGGING = 11, // 0x0000000B
        AIUBT_ASSASSINATION = 12, // 0x0000000C
        AIUBT_ATTUNIT2 = 13, // 0x0000000D
        AIUBT_LADDERING = 14, // 0x0000000E
        AIUBT_TUNNELING = 15, // 0x0000000F
        AIUBT_PATROLLING = 16, // 0x00000010
        AIUBT_BACKUPING = 17, // 0x00000011
        AIUBT_ENGAGING = 18, // 0x00000012
        AIUBT_SIEGEDEFENSE = 19, // 0x00000013
        AIUBT_ATTUNITMAIN = 20, // 0x00000014
        AIUBT_SIEGE_01 = 21, // 0x00000015
        AIUBT_HARASS_SIEGE = 22 // 0x00000016

    } AIUnitBehaviourType;

    static_assert_cpp98_obj(sizeof(AIUnitBehaviourType) == 4, AIUnitBehaviourType);
} // namespace AI
} // namespace OpenSHC
