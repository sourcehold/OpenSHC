/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Enums/AttackWaveState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Enums {
        typedef enum AttackWaveState {

            AWS_GATHERING = 0, // 0x00000000
            AWS_ADVANCING = 1, // 0x00000001
            AWS_PREPARING_SIEGE = 2, // 0x00000002
            AWS_ASSIGNING_TARGETS = 3, // 0x00000003
            AWS_DELAYED_TARGET_ASSIGNMENT = 4, // 0x00000004
            AWS_5Unk = 5, // 0x00000005
            AWS_ENDED = 6 // 0x00000006

        } AttackWaveState;

        static_assert_cpp98_obj(sizeof(AttackWaveState) == 4, AttackWaveState);
    } // namespace Enums
} // namespace Map
} // namespace OpenSHC
