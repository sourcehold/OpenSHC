/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/OpenFlagsEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DirectPlay {
    typedef enum OpenFlagsEnum {

        OFE_JOIN = 1, // 0x00000001
        OFE_CREATE = 2, // 0x00000002
        OFE_RETURN_STATUS = 128 // 0x00000080

    } OpenFlagsEnum;

    static_assert_cpp98_obj(sizeof(OpenFlagsEnum) == 4, OpenFlagsEnum);
} // namespace DirectPlay
} // namespace OpenSHC
