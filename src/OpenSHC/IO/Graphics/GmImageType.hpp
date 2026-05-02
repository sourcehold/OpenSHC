/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Graphics/GmImageType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Graphics {
        typedef enum GmImageType {

            GIT_InterfaceElement = 1, // 0x00000001
            GIT_Animation = 2, // 0x00000002
            GIT_Tileset = 3, // 0x00000003
            GIT_Font = 4, // 0x00000004
            GIT_UncompressedImage = 5, // 0x00000005
            GIT_CompressedImage = 6, // 0x00000006
            GIT_UncompressedImageUnk = 7 // 0x00000007

        } GmImageType;

        static_assert_cpp98_obj(sizeof(GmImageType) == 4, GmImageType);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
