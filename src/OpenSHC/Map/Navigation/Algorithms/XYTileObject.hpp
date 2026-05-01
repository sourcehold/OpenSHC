/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Navigation/Algorithms/XYTileObject.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        namespace Algorithms {

#pragma pack(push, 1)
            // SIZE: 0x00000010
            typedef struct XYTileObject {

                int x; // 0x00000000 length: 4
                int y; // 0x00000004 length: 4
                int tile; // 0x00000008 length: 4
                undefined1 padding_0xc[4]; // 0x0000000C length: 4

            } XYTileObject;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(XYTileObject) == 16, XYTileObject);
        } // namespace Algorithms
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
