/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/Graphics/ImageHeader.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Graphics {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct ImageHeader {

            short width; // 0x00000000 length: 2
            short height; // 0x00000002 length: 2
            short offsetX; // 0x00000004 length: 2
            short offsetY; // 0x00000006 length: 2
            short alternativeImageIndexUnk; // 0x00000008 length: 2
            short tileOffset; // 0x0000000A length: 2
            byte direction; // 0x0000000C length: 1
            byte horizontalOffsetImage; // 0x0000000D length: 1
            byte buildingWidth; // 0x0000000E length: 1
            byte animatedColor; // 0x0000000F length: 1

        } ImageHeader;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ImageHeader) == 16, ImageHeader);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
