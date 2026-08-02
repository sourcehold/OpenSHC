/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Helpers/ColorUnion.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Helpers {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef union ColorUnion {

            short shortValue; // 0x00000000 length: 2
            int intValue; // 0x00000000 length: 4

        } ColorUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ColorUnion) == 4, ColorUnion);
    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
