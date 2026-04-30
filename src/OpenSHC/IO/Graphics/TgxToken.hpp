/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/Graphics/TgxToken.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Graphics {
        typedef enum TgxToken {

            TT_STREAM_OF_PIXELS = 0, // 0x00000000
            TT_TGX_PIXEL_LENGTH = 31, // 0x0000001F
            TT_TRANSPARENT_PIXELS = 32, // 0x00000020
            TT_REPEATING_PIXELS = 64, // 0x00000040
            TT_NEWLINE = 128, // 0x00000080
            TT_TGX_PIXEL_HEADER = 224 // 0x000000E0

        } TgxToken;

        static_assert_cpp98_obj(sizeof(TgxToken) == 4, TgxToken);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
