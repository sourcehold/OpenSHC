/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/Helpers/Buffer.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Helpers {

#pragma pack(push, 1)
        // SIZE: 0x0000000C
        typedef struct Buffer {

            uchar* data; // 0x00000000 length: 4
            uint offset; // 0x00000004 length: 4
            uint size; // 0x00000008 length: 4

        } Buffer;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Buffer) == 12, Buffer);
    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
