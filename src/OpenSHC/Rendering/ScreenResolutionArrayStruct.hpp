/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ScreenResolutionArrayStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x00000040
    typedef struct ScreenResolutionArrayStruct {

        int noneUnk; // 0x00000000 length: 4
        int _800x600; // 0x00000004 length: 4
        int _1024x768; // 0x00000008 length: 4
        int _1280x720; // 0x0000000C length: 4
        int _1280x1024; // 0x00000010 length: 4
        int _1366x768; // 0x00000014 length: 4
        int _1440x900; // 0x00000018 length: 4
        int _1600x900; // 0x0000001C length: 4
        int _1600x1200; // 0x00000020 length: 4
        int _1680x1050; // 0x00000024 length: 4
        int _1920x1080; // 0x00000028 length: 4
        int _1920x1200; // 0x0000002C length: 4
        int _2560x1440; // 0x00000030 length: 4
        int _2560x1600; // 0x00000034 length: 4
        int _1360x768; // 0x00000038 length: 4
        int _1024x600; // 0x0000003C length: 4

    } ScreenResolutionArrayStruct;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ScreenResolutionArrayStruct) == 64, ScreenResolutionArrayStruct);
} // namespace Rendering
} // namespace OpenSHC
