/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/UserHelpDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Text/HelpTextRelatedColorStruct.hpp"
#include "OpenSHC/Text/UnkHelpTextRelatedFontStruct.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::HelpTextRelatedColorStruct;
    using OpenSHC::Text::UnkHelpTextRelatedFontStruct;

#pragma pack(push, 1)
    // SIZE: 0x0007A23C
    typedef struct UserHelpDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        char HLP_HelpSections[500][1000]; // 0x00000004 length: 500000
        UnkHelpTextRelatedFontStruct field5_0x7a124[9]; // 0x0007A124 length: 72
        HelpTextRelatedColorStruct field6_0x7a16c[13]; // 0x0007A16C length: 208

    } UserHelpDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(UserHelpDefinedData) == 500284, UserHelpDefinedData);
} // namespace UI
} // namespace OpenSHC
