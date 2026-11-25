/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/WorkerBlockingState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {
            typedef enum WorkerBlockingState {

                WBS_NONE = 0, // 0x00000000
                WBS_STOCKPILE_FULL = 47, // 0x0000002F
                WBS_GRANARY_FULL = 48, // 0x00000030
                WBS_ARMOURY_FULL = 49, // 0x00000031
                WBS_NO_TREES = 50, // 0x00000032
                WBS_NO_WOOD = 51, // 0x00000033
                WBS_NO_DEER = 52, // 0x00000034
                WBS_NO_WHEAT = 53, // 0x00000035
                WBS_NO_FLOUR = 54, // 0x00000036
                WBS_NO_HOPS = 55, // 0x00000037
                WBS_NO_IRON = 56, // 0x00000038
                WBS_NO_COWS = 57, // 0x00000039
                WBS_NO_ALE = 58 // 0x0000003A

            } WorkerBlockingState;

            static_assert_cpp98_obj(sizeof(WorkerBlockingState) == 4, WorkerBlockingState);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
