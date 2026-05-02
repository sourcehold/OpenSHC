/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/SFXState.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/AmbientSFXTypeInt.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectIDInt.hpp"
#include "OpenSHC/Audio/SFX/SoundStructure1.hpp"
#include "OpenSHC/Audio/SFX/SoundStructure2.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectIDInt.hpp"
#include "OpenSHC/DE/SHCDE/eSFXInt.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using OpenSHC::Audio::SFX::AmbientSFXTypeInt;
        using OpenSHC::Audio::SFX::SoundEffectIDInt;
        using OpenSHC::Audio::SFX::SoundStructure1;
        using OpenSHC::Audio::SFX::SoundStructure2;
        using OpenSHC::Audio::SFX::SpeechEffectIDInt;
        using OpenSHC::DE::SHCDE::eSFXInt;

#pragma pack(push, 1)

        // SIZE: 0x00008E90
        class SFXState {
        public:
            undefined4 DAT_SFXCounter1; // 0x00000000 length: 4
            undefined4 highestSFXCounter; // 0x00000004 length: 4
            pointer* DAT_SoundFileNameArrayMemoryPointer; // 0x00000008 length: 4
            char* DAT_SoundFileNamePointersArray[1000]; // 0x0000000C length: 4000
            int DAT_SoundVolumeArray[1000]; // 0x00000FAC length: 4000
            undefined4 DAT_SoundTotalCount; // 0x00001F4C length: 4
            SoundStructure1 DAT_SoundStructures[1000]; // 0x00001F50 length: 24000
            SoundStructure2 DAT_SoundStructures2[270]; // 0x00007D10 length: 4320
            int ambientEventCounters[10][4]; // 0x00008DF0 length: 160

        private:
            SFXState(SFXState const&);
            void operator=(SFXState const&);

            SFXState();
            ~SFXState();

        public:
            // Constructor
            SFXState* Constructor_SFXState();

            void freeMemoryAt(int param_1);

            void loadWavSounds(char* param_1);

            void setUpSFXToPlayUnk(SoundEffectIDInt sfxOffsetInArray);

            void setSoundWithVariation(int unknownSfxID, int volumePercentage);

            void scheduleSFXVariation(int sfxGroupID, int variationIndex);

            void playSFXAtLocation(int xPosition, int yPosition, eSFXInt sfxOffsetInArray);

            void someVolumeAdjustmentFunction(int param_1, int param_2, int param_3);

            void meth_0x44a050();

            void notifyAmbientSoundEvent(int ambientSoundType);

            void playAmbientSoundStreamUnk(AmbientSFXTypeInt ambientSoundIndexUnk);

            void playAmbientSoundStream2Unk(int ambientSoundIndexUnk);

            int getSoundVolumeForFilename(char* soundFileName);

            void playUnitSpeechEffect(uint speechEffectID);

            void PlaySpeechSFX(SpeechEffectIDInt speechID);

            void playWAVSFX(char* wav_filename);

            void playOnSpeechSfxStream(char* filename);

            void playSpeechSFX(char* filename);

            void playSFXWeAreUnderAttack();

            void tweakVolume(int param_1, float param_2);

            void readVolumeFileAndSetupSoundVolumes();

            void loadSFX();

            void updateAmbientSoundStream();

            void soundRelatedMethod1();
        };

        static_assert_cpp98_obj(sizeof(SFXState) == 36496, SFXState);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(SFXState, false, Address::SHC_3BB0A8C1_0x00F22500) pDAT_SFXState;

    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
