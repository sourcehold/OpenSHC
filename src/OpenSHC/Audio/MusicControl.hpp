/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MusicControl.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {

#pragma pack(push, 1)
    // SIZE: 0x00000020
    typedef struct MusicControl {

        int field0_0x0; // 0x00000000 length: 4
        int field1_0x4; // 0x00000004 length: 4
        int volumeLevel; // 0x00000008 length: 4
        int musicTracker; // 0x0000000C length: 4
        int troopValueLevel; // 0x00000010 length: 4
        int incrementorUpTo4; // 0x00000014 length: 4
        int field6_0x18; // 0x00000018 length: 4
        int field7_0x1c; // 0x0000001C length: 4

    } MusicControl;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MusicControl) == 32, MusicControl);
} // namespace Audio
} // namespace OpenSHC
