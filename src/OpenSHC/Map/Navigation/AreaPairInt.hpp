/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation/AreaPairInt.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Navigation {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct AreaPairInt {

            int area1; // 0x00000000 length: 4
            int area2; // 0x00000004 length: 4

        } AreaPairInt;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AreaPairInt) == 8, AreaPairInt);
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
