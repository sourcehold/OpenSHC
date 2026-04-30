/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AIAttackWaveTarget.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIAttackWaveTarget {

        AIAWT_Walls = 1010, // 0x000003F2
        AIAWT_Buildings = 1013, // 0x000003F5
        AIAWT_Towers = 1014 // 0x000003F6

    } AIAttackWaveTarget;

    static_assert_cpp98_obj(sizeof(AIAttackWaveTarget) == 4, AIAttackWaveTarget);
} // namespace AI
} // namespace OpenSHC
