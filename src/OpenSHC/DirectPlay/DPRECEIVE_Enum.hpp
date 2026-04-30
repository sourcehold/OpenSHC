/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/DPRECEIVE_Enum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace DirectPlay {
    typedef enum DPRECEIVE_Enum {

        DPRECEIVE_ALL = 1, // 0x00000001
        DPRECEIVE_TOPLAYER = 2, // 0x00000002
        DPRECEIVE_FROMPLAYER = 4, // 0x00000004
        DPRECEIVE_PEEK = 8 // 0x00000008

    } DPRECEIVE_Enum;

    static_assert_cpp98_obj(sizeof(DPRECEIVE_Enum) == 4, DPRECEIVE_Enum);
} // namespace DirectPlay
} // namespace OpenSHC
