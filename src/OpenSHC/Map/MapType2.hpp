/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/MapType2.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    typedef enum MapType2 {

        MT_SIEGE = 0, // 0x00000000
        MT_INVASION = 1, // 0x00000001
        MT_ECONOMIC = 2, // 0x00000002
        MT_JUST_BUILD = 3 // 0x00000003

    } MapType2;

    static_assert_cpp98_obj(sizeof(MapType2) == 4, MapType2);
} // namespace Map
} // namespace OpenSHC
