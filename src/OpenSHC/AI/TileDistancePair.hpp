/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/TileDistancePair.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct TileDistancePair {

        int tile; // 0x00000000 length: 4
        int distance; // 0x00000004 length: 4

    } TileDistancePair;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TileDistancePair) == 8, TileDistancePair);
} // namespace AI
} // namespace OpenSHC
