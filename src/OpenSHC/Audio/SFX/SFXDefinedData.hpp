/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Audio/SFX/SFXDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/MusicSfx.hpp"
#include "mmsystem.h"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using OpenSHC::Audio::SFX::MusicSfx;

#pragma pack(push, 1)
        // SIZE: 0x000004EC
        typedef struct SFXDefinedData {

            MMRESULT SND_SomeTimerIdentifier; // 0x00000000 length: 4
            MusicSfx DAT_SFX_Pointers[116]; // 0x00000004 length: 928
            int field2_0x3a4[8][8]; // 0x000003A4 length: 256
            int field3_0x4a4[8]; // 0x000004A4 length: 32
            int field4_0x4c4[6]; // 0x000004C4 length: 24
            int DAT_LastUsedSpeechStream; // 0x000004DC length: 4
            undefined4 field6_0x4e0; // 0x000004E0 length: 4
            undefined4 field7_0x4e4; // 0x000004E4 length: 4
            undefined1 padding_0x4e8[4]; // 0x000004E8 length: 4

        } SFXDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SFXDefinedData) == 1260, SFXDefinedData);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
