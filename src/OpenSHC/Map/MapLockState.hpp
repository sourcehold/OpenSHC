/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/MapLockState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    typedef enum MapLockState {

        MLS_EDITABLE = 0, // 0x00000000
        MLS_PLAYABLE = 1, // 0x00000001
        MLS_MISSION = 2 // 0x00000002

    } MapLockState;

    static_assert_cpp98_obj(sizeof(MapLockState) == 4, MapLockState);
} // namespace Map
} // namespace OpenSHC
