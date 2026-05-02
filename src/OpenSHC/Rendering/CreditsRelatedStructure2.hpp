/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/CreditsRelatedStructure2.hpp'
*/

#pragma once

#include "OpenSHC/Audio/mss/UnkSoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/mss/_enums/SHC_SoundStreamInt.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Audio::mss::UnkSoundFlagsAndLoopCount;
    using OpenSHC::Audio::mss::_enums::SHC_SoundStreamInt;

#pragma pack(push, 1)
    // SIZE: 0x0000005C
    typedef struct CreditsRelatedStructure2 {

        int field0_0x0; // 0x00000000 length: 4
        SHC_SoundStreamInt soundStream; // 0x00000004 length: 4
        int x; // 0x00000008 length: 4
        int y; // 0x0000000C length: 4
        int field4_0x10; // 0x00000010 length: 4
        int field5_0x14; // 0x00000014 length: 4
        int field6_0x18; // 0x00000018 length: 4
        undefined1 padding_0x1c[4]; // 0x0000001C length: 4
        UnkSoundFlagsAndLoopCount flagLoopCount; // 0x00000020 length: 4
        int binkObjIndex; // 0x00000024 length: 4
        int field13_0x28; // 0x00000028 length: 4
        int volume; // 0x0000002C length: 4
        int field15_0x30; // 0x00000030 length: 4
        int field16_0x34; // 0x00000034 length: 4
        int field17_0x38; // 0x00000038 length: 4
        char* binkFileName; // 0x0000003C length: 4
        undefined1 padding_0x40[28]; // 0x00000040 length: 28

    } CreditsRelatedStructure2;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CreditsRelatedStructure2) == 92, CreditsRelatedStructure2);
} // namespace Rendering
} // namespace OpenSHC
