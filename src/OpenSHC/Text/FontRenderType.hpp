/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

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
