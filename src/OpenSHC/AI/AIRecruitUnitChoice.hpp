/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIRecruitUnitChoice.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIRecruitUnitChoice {

        AIRUC_DEFENSIVE = 0, // 0x00000000
        AIRUC_RAIDING = 1, // 0x00000001
        AIRUC_ATTACKING = 2 // 0x00000002

    } AIRecruitUnitChoice;

    static_assert_cpp98_obj(sizeof(AIRecruitUnitChoice) == 4, AIRecruitUnitChoice);
} // namespace AI
} // namespace OpenSHC
