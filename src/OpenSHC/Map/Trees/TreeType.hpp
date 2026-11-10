/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Trees/TreeType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Trees {
        typedef enum TreeType {

            TT_DEFAULT = 0, // 0x00000000
            TT_UNKNOWN_1 = 1, // 0x00000001
            TT_UNKNOWN_2 = 2, // 0x00000002
            TT_UNKNOWN_3 = 3, // 0x00000003
            TT_UNKNOWN_4 = 4, // 0x00000004
            TT_APPLEUnk = 15, // 0x0000000F
            TT_UNKNOWN_16 = 16, // 0x00000010
            TT_UNKNOWN_17 = 17, // 0x00000011
            TT_UNKNOWN_18 = 18, // 0x00000012
            TT_UNKNOWN_19 = 19 // 0x00000013

        } TreeType;

        static_assert_cpp98_obj(sizeof(TreeType) == 4, TreeType);
    } // namespace Trees
} // namespace Map
} // namespace OpenSHC
