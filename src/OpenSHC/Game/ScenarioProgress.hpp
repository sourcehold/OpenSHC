/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioProgress.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct ScenarioProgress {

        int progressCallToArms; // 0x00000000 length: 4
        int progressSaladinsConquest; // 0x00000004 length: 4
        int progressTheKingsCrusade; // 0x00000008 length: 4
        int progressCrusaderStates; // 0x0000000C length: 4

    } ScenarioProgress;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ScenarioProgress) == 16, ScenarioProgress);
} // namespace Game
} // namespace OpenSHC
