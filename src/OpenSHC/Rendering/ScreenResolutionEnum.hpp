/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Rendering/ScreenResolutionEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    typedef enum ScreenResolutionEnum {

        SRE_800x600 = 1, // 0x00000001
        SRE_1024x768 = 2, // 0x00000002
        SRE_1280x720 = 3, // 0x00000003
        SRE_1280x1024 = 4, // 0x00000004
        SRE_1366x768 = 5, // 0x00000005
        SRE_1440x900 = 6, // 0x00000006
        SRE_1600x900 = 7, // 0x00000007
        SRE_1600x1200 = 8, // 0x00000008
        SRE_1680x1050 = 9, // 0x00000009
        SRE_1920x1080 = 10, // 0x0000000A
        SRE_1920x1200 = 11, // 0x0000000B
        SRE_2560x1440 = 12, // 0x0000000C
        SRE_2560x1600 = 13, // 0x0000000D
        SRE_1360x768 = 14, // 0x0000000E
        SRE_1024x600 = 15, // 0x0000000F
        SRE_640x480 = 20, // 0x00000014
        SRE_neg1 = 4294967295 // 0xFFFFFFFF

    } ScreenResolutionEnum;

    static_assert_cpp98_obj(sizeof(ScreenResolutionEnum) == 4, ScreenResolutionEnum);
} // namespace Rendering
} // namespace OpenSHC
