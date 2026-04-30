/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Navigation/PathHelper12.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {

#pragma pack(push, 1)
        // SIZE: 0x0000000C
        typedef struct PathHelper12 {

            int tile1; // 0x00000000 length: 4
            int tile2OrAHelper; // 0x00000004 length: 4
            int tile3OrAnotherHelper; // 0x00000008 length: 4

        } PathHelper12;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(PathHelper12) == 12, PathHelper12);
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
