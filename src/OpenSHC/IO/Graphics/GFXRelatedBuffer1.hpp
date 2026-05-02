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
        // SIZE: 0x00011DF0
        typedef struct GFXRelatedBuffer1 {

            undefined1 field0_0x0; // 0x00000000 length: 1
            undefined1 padding_0x1[1]; // 0x00000001 length: 1
            short field2_0x2; // 0x00000002 length: 2
            undefined1 padding_0x4[46]; // 0x00000004 length: 46
            short field49_0x32; // 0x00000032 length: 2
            undefined1 padding_0x34[46]; // 0x00000034 length: 46
            undefined1 field96_0x62; // 0x00000062 length: 1
            undefined1 padding_0x63[23]; // 0x00000063 length: 23
            undefined1 field120_0x7a; // 0x0000007A length: 1
            undefined1 padding_0x7b[219]; // 0x0000007B length: 219
            undefined1 field340_0x156; // 0x00000156 length: 1
            undefined1 padding_0x157[72857]; // 0x00000157 length: 72857

        } GFXRelatedBuffer1;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GFXRelatedBuffer1) == 73200, GFXRelatedBuffer1);
    } // namespace Graphics
} // namespace IO
} // namespace OpenSHC
