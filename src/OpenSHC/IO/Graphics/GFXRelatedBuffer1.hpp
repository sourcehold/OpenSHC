/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Graphics/GFXRelatedBuffer1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    namespace Graphics {

#pragma pack(push, 1)
        // SIZE: 0x0000007A
        typedef struct GFXRelatedBuffer1 {

            byte count; // 0x00000000 length: 1
            undefined1 padding_0x1[1]; // 0x00000001 length: 1
            short x[24]; // 0x00000002 length: 48
            short width[24]; // 0x00000032 length: 48
            byte type[24]; // 0x00000062 length: 24

        } GFXRelatedBuffer1;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GFXRelatedBuffer1) == 122, GFXRelatedBuffer1);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
