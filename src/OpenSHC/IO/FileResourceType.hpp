/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/FileResourceType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {
    typedef enum FileResourceType {

        FRT_UNKNOWN = 1, // 0x00000001
        FRT_CASTLES = 2, // 0x00000002
        FRT_SCENARIOS = 6, // 0x00000006
        FRT_GM = 10, // 0x0000000A
        FRT_GFX = 11, // 0x0000000B
        FRT_HELP = 12, // 0x0000000C
        FRT_BINKS = 13, // 0x0000000D
        FRT_FX = 14, // 0x0000000E
        FRT_MAPS = 15, // 0x0000000F
        FRT_SCORES = 16, // 0x00000010
        FRT_GFX8 = 17, // 0x00000011
        FRT_GFX_SPEECH = 18, // 0x00000012
        FRT_BMP = 19 // 0x00000013

    } FileResourceType;

    static_assert_cpp98_obj(sizeof(FileResourceType) == 4, FileResourceType);
} // namespace IO
} // namespace OpenSHC
