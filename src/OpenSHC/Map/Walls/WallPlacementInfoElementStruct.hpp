/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Walls/WallPlacementInfoElementStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Walls {

#pragma pack(push, 1)
        // SIZE: 0x0000000C
        typedef struct WallPlacementInfoElementStruct {

            int tile_OR_pitchID; // 0x00000000 length: 4
            byte damage; // 0x00000004 length: 1
            byte height; // 0x00000005 length: 1
            short field3_0x6; // 0x00000006 length: 2
            uint logic; // 0x00000008 length: 4

        } WallPlacementInfoElementStruct;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(WallPlacementInfoElementStruct) == 12, WallPlacementInfoElementStruct);
    } // namespace Walls
} // namespace Map
} // namespace OpenSHC
