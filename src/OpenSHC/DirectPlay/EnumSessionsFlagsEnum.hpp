/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DirectPlay {
    typedef enum EnumSessionsFlagsEnum {

        ESFE_AVAILABLE = 1, // 0x00000001
        ESFE_ALL = 2, // 0x00000002
        ESFE_ASYNC_ENUMERATION = 16, // 0x00000010
        ESFE_ASYNC_ENUMERATION_STOP = 32, // 0x00000020
        ESFE_PASSWORD_REQUIRED = 64, // 0x00000040
        ESFE_RETURN_STATUS = 128 // 0x00000080

    } EnumSessionsFlagsEnum;

    static_assert_cpp98_obj(sizeof(EnumSessionsFlagsEnum) == 4, EnumSessionsFlagsEnum);
} // namespace DirectPlay
} // namespace OpenSHC
