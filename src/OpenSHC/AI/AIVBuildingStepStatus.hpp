/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AIVBuildingStepStatus.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AIVBuildingStepStatus {

        AIVBSS_disabled = 0, // 0x00000000
        AIVBSS_unbuilt = 1, // 0x00000001
        AIVBSS_built = 3, // 0x00000003
        AIVBSS_insufficient_roomUnk = 4, // 0x00000004
        AIVBSS_insufficient_resources = 5 // 0x00000005

    } AIVBuildingStepStatus;

    static_assert_cpp98_obj(sizeof(AIVBuildingStepStatus) == 4, AIVBuildingStepStatus);
} // namespace AI
} // namespace OpenSHC
