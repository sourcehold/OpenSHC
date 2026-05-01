/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Util/IntShortUnion.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Util {

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union IntShortUnion {

        int int_; // 0x00000000 length: 4
        short short_; // 0x00000000 length: 2

    } IntShortUnion;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(IntShortUnion) == 4, IntShortUnion);
} // namespace Util
} // namespace OpenSHC
