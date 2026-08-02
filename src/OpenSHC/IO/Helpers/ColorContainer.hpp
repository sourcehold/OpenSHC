/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Helpers/ColorContainer.hpp'
*/

#pragma once

#include "OpenSHC/IO/Helpers/ColorUnion.hpp"

namespace OpenSHC {
namespace IO {
    namespace Helpers {

        using OpenSHC::IO::Helpers::ColorUnion;

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef struct ColorContainer {

            ColorUnion data; // 0x00000000 length: 4

        } ColorContainer;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ColorContainer) == 4, ColorContainer);
    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
