/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/CharPointerArrayUnion.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Text {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef union CharPointerArrayUnion {

        char charArray[16]; // 0x00000000 length: 16
        char* pCharArray; // 0x00000000 length: 4

    } CharPointerArrayUnion;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CharPointerArrayUnion) == 16, CharPointerArrayUnion);
} // namespace Text
} // namespace OpenSHC
