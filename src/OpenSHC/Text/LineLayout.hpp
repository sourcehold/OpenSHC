/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/LineLayout.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {

#pragma pack(push, 1)
    // SIZE: 0x00000006
    typedef struct LineLayout {

        short leftBorder; // 0x00000000 length: 2
        short rightBorder; // 0x00000002 length: 2
        short widthForCentering; // 0x00000004 length: 2

    } LineLayout;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(LineLayout) == 6, LineLayout);
} // namespace Text
} // namespace OpenSHC
