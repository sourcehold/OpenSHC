/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Graphics/ImageHeaders.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/ImageHeader.hpp"

namespace OpenSHC {
namespace IO {
    namespace Graphics {

        using OpenSHC::IO::Graphics::ImageHeader;

#pragma pack(push, 1)
        // SIZE: 0x00101D00
        typedef struct ImageHeaders {

            ImageHeader imh[66000]; // 0x00000000 length: 1056000

        } ImageHeaders;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ImageHeaders) == 1056000, ImageHeaders);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
