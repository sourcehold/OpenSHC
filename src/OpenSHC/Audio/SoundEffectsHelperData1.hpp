/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SoundEffectsHelperData1.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MusicControl.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
#include "mmsystem.h"

namespace OpenSHC {
namespace Audio {

    using OpenSHC::Audio::MusicControl;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
    // SIZE: 0x00000088
    typedef struct SoundEffectsHelperData1 {

        undefined4 DAT_NegativeCountdownMin1ToMin4Becomes0; // 0x00000000 length: 4
        undefined4 DAT_Music_TotalTroopValue; // 0x00000004 length: 4
        int field2_0x8; // 0x00000008 length: 4
        MusicControl SEC_Section1079; // 0x0000000C length: 32
        int field4_0x2c; // 0x0000002C length: 4
        undefined4 SND_SomeTimerResolution; // 0x00000030 length: 4
        undefined4 field6_0x34; // 0x00000034 length: 4
        int DAT_NumberOfUsedSoundSamplePlaces; // 0x00000038 length: 4
        int field8_0x3c; // 0x0000003C length: 4
        int DAT_RandomVariationCurrentPlayingMusic_01; // 0x00000040 length: 4
        int DAT_SomeSoundTime2; // 0x00000044 length: 4
        int DAT_RandomVariationCurrentPlayingMusic_02; // 0x00000048 length: 4
        undefined4 field12_0x4c; // 0x0000004C length: 4
        undefined4 field13_0x50; // 0x00000050 length: 4
        undefined1 padding_0x54[4]; // 0x00000054 length: 4
        BOOLEnum field18_0x58; // 0x00000058 length: 4
        undefined4 field19_0x5c; // 0x0000005C length: 4
        undefined4 DAT_WinMusicVariation; // 0x00000060 length: 4
        undefined4 field21_0x64; // 0x00000064 length: 4
        undefined4 DAT_LossMusicVariation; // 0x00000068 length: 4
        DWORD DAT_enemyInsideCastleSoundWarningCooldownTimer; // 0x0000006C length: 4
        undefined4 field24_0x70; // 0x00000070 length: 4
        WAVEFORMATEX SND_Waveformat; // 0x00000074 length: 18
        undefined1 padding_0x86[2]; // 0x00000086 length: 2

    } SoundEffectsHelperData1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(SoundEffectsHelperData1) == 136, SoundEffectsHelperData1);
} // namespace Audio
} // namespace OpenSHC
