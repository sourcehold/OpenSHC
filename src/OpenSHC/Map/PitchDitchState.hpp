/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/PitchDitchState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    typedef enum PitchDitchState {

        PDS_REMOVE = -1, // 0xFFFFFFFF
        PDS_PLACED = 0, // 0x00000000
        PDS_READY = 1, // 0x00000001
        PDS_BURNING = 2, // 0x00000002
        PDS_BURNT_OUT = 3 // 0x00000003

    } PitchDitchState;

    static_assert_cpp98_obj(sizeof(PitchDitchState) == 4, PitchDitchState);
} // namespace Map
} // namespace OpenSHC
