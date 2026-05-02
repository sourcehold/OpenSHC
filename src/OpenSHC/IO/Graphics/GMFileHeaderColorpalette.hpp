/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Graphics/GMFileHeaderColorpalette.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmImageTypeInt.hpp"

namespace OpenSHC {
namespace IO {
    namespace Graphics {

        using OpenSHC::IO::Graphics::GmImageTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00001458
        typedef struct GMFileHeaderColorpalette {

            int unknown0; // 0x00000000 length: 4
            int unknown1; // 0x00000004 length: 4
            int unknown2; // 0x00000008 length: 4
            int numberOfPicturesInFile; // 0x0000000C length: 4
            int unknown3; // 0x00000010 length: 4
            GmImageTypeInt ImageType; // 0x00000014 length: 4
            int unknown4; // 0x00000018 length: 4
            int unknown5; // 0x0000001C length: 4
            int unknown6; // 0x00000020 length: 4
            int unknown7; // 0x00000024 length: 4
            int unknown8; // 0x00000028 length: 4
            int unknown9; // 0x0000002C length: 4
            int width; // 0x00000030 length: 4
            int heigth; // 0x00000034 length: 4
            int unknown12; // 0x00000038 length: 4
            int unknown13; // 0x0000003C length: 4
            int unknown14; // 0x00000040 length: 4
            int unknown15; // 0x00000044 length: 4
            int originX; // 0x00000048 length: 4
            int originY; // 0x0000004C length: 4
            int dataSize; // 0x00000050 length: 4
            int unknown18; // 0x00000054 length: 4
            short colorPalette[10][256]; // 0x00000058 length: 5120

        } GMFileHeaderColorpalette;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GMFileHeaderColorpalette) == 5208, GMFileHeaderColorpalette);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
