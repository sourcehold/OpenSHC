/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/Speech/SpeechDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/AmbientSfx.hpp"
#include "OpenSHC/Audio/SFX/NameSpeechPair.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectPath.hpp"
#include "OpenSHC/Audio/SFX/UnitSpeechData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace Speech {

        using OpenSHC::Audio::SFX::AmbientSfx;
        using OpenSHC::Audio::SFX::NameSpeechPair;
        using OpenSHC::Audio::SFX::SpeechEffectPath;
        using OpenSHC::Audio::SFX::UnitSpeechData;

#pragma pack(push, 1)
        // SIZE: 0x0049D4C4
        typedef struct SpeechDefinedData {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            char SFX_WavFileGroups[2][270][8][1000]; // 0x00000004 length: 4320000
            AmbientSfx field5_0x41eb04[10]; // 0x0041EB04 length: 720
            UnitSpeechData field6_0x41edd4[42]; // 0x0041EDD4 length: 6216
            SpeechEffectPath DAT_SpeechEffectPathArray[40]; // 0x0042061C length: 640
            char DAT_SpeechEffectFileArray[65][1000]; // 0x0042089C length: 65000
            NameSpeechPair LordNameToCall[223]; // 0x00430684 length: 446000
            int field10_0x49d4b4; // 0x0049D4B4 length: 4
            undefined4 field11_0x49d4b8; // 0x0049D4B8 length: 4
            int currentStreamID; // 0x0049D4BC length: 4
            undefined1 padding_0x49d4c0[4]; // 0x0049D4C0 length: 4

        } SpeechDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SpeechDefinedData) == 4838596, SpeechDefinedData);
    } // namespace Speech
} // namespace Audio
} // namespace OpenSHC
