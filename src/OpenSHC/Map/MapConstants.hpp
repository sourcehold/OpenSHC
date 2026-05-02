/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/MapConstants.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    typedef enum MapConstants {

        MAP_XY_LIMIT_INCLUSIVE = 399, // 0x0000018F
        MAP_XY_LIMIT = 400, // 0x00000190
        MAP_TILES_COUNT = 80400 // 0x00013A10

    } MapConstants;

    static_assert_cpp98_obj(sizeof(MapConstants) == 4, MapConstants);
} // namespace Map
} // namespace OpenSHC
