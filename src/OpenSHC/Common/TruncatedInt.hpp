/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Common/TruncatedInt.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Common {

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union TruncatedInt {

        int intValue; // 0x00000000 length: 4
        short shortValue; // 0x00000000 length: 2
        byte byteValue; // 0x00000000 length: 1

    } TruncatedInt;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TruncatedInt) == 4, TruncatedInt);
} // namespace Common
} // namespace OpenSHC
