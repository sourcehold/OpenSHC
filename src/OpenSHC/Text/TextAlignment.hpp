/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/TextAlignment.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {
    typedef enum TextAlignment {

        TTA_LEFT = 0, // 0x00000000
        TTA_CENTER = 1, // 0x00000001
        TTA_RIGHT = 4294967295 // 0xFFFFFFFF

    } TextAlignment;

    static_assert_cpp98_obj(sizeof(TextAlignment) == 4, TextAlignment);
} // namespace Text
} // namespace OpenSHC
