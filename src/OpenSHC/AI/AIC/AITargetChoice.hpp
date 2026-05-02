/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIC/AITargetChoice.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    namespace AIC {
        typedef enum AITargetChoice {

            AITC_GOLD = 0, // 0x00000000
            AITC_BALANCED = 1, // 0x00000001
            AITC_CLOSEST = 2, // 0x00000002
            AITC_ANY = 3, // 0x00000003
            AITC_PLAYER = 4 // 0x00000004

        } AITargetChoice;

        static_assert_cpp98_obj(sizeof(AITargetChoice) == 4, AITargetChoice);
    } // namespace AIC
} // namespace AI
} // namespace OpenSHC
