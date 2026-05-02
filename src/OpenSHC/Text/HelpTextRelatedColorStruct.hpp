/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/HelpTextRelatedColorStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct HelpTextRelatedColorStruct {

        char* name_0x0; // 0x00000000 length: 4
        int r_0x4; // 0x00000004 length: 4
        int g_0x8; // 0x00000008 length: 4
        int b_0xc; // 0x0000000C length: 4

    } HelpTextRelatedColorStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(HelpTextRelatedColorStruct) == 16, HelpTextRelatedColorStruct);
} // namespace Text
} // namespace OpenSHC
