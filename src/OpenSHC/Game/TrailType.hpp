/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/TrailType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    typedef enum TrailType {

        TT_FIRST_EDITION = 0, // 0x00000000
        TT_WARCHEST = 1, // 0x00000001
        TT_EXTREME = 2 // 0x00000002

    } TrailType;

    static_assert_cpp98_obj(sizeof(TrailType) == 4, TrailType);
} // namespace Game
} // namespace OpenSHC
