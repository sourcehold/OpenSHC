/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Text/FontRenderType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {
    typedef enum FontRenderType {

        FRT_COLOR = 0, // 0x00000000
        FRT_BLENDED_COLOR = 1, // 0x00000001
        FRT_RAW = 2 // 0x00000002

    } FontRenderType;

    static_assert_cpp98_obj(sizeof(FontRenderType) == 4, FontRenderType);
} // namespace Text
} // namespace OpenSHC
