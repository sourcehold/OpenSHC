/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS/SoundSystem.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/UnkSoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStreamInt.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDsInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "Mss32.h"
#include "WinDef.h"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        using OpenSHC::Audio::MSS::UnkSoundFlagsAndLoopCount;
        using OpenSHC::Audio::MSS::enums::SHC_SoundStreamInt;
        using OpenSHC::DE::SHCDE::eMusicIDsInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0000328C
        class SoundSystem {
        public:
            DWORD soundActiveUnk_0x0; // 0x00000000 length: 4
            HDIGDRIVER digSndDriver_0x4; // 0x00000004 length: 4
            BOOLEnum waveOutOpenUnk_0x8; // 0x00000008 length: 4
            HSTREAM stream_0xc[5]; // 0x0000000C length: 20
            int streamActiveUnk_0x20[5]; // 0x00000020 length: 20
            UnkSoundFlagsAndLoopCount streamFlagsUnkAndLoopCount_0x34[5]; // 0x00000034 length: 20
            int streamFileVolumeNextUnk_0x48[5]; // 0x00000048 length: 20
            int streamFileVolumeCurrentUnk_0x5c[5]; // 0x0000005C length: 20
            int streamVolume[5]; // 0x00000070 length: 20
            char currIdSoundFilenameUnk_0x84[200]; // 0x00000084 length: 200
            int mbr_0x14c; // 0x0000014C length: 4
            int currIdSoundFileVolumeUnk_0x150; // 0x00000150 length: 4
            dword mbr_0x154; // 0x00000154 length: 4
            dword someSoundTime_0x158; // 0x00000158 length: 4
            int streamPaused_0x15c[5]; // 0x0000015C length: 20
            HSAMPLE musicSampleUnk_0x170; // 0x00000170 length: 4
            int musicSampleFileHandleUnk_0x174; // 0x00000174 length: 4
            int musicFileHandle_0x178; // 0x00000178 length: 4
            void* sampleBufferPtrUnk_0x17c[2]; // 0x0000017C length: 8
            int sampleBufferSizeUnk_0x184; // 0x00000184 length: 4
            dword mbr_0x188; // 0x00000188 length: 4
            dword mbr_0x18c; // 0x0000018C length: 4
            HSAMPLE sample_0x190[31]; // 0x00000190 length: 124
            int sampleSoundIndex_0x20c[32]; // 0x0000020C length: 128
            int soundFileCurrSampleNum_0x28c[1000]; // 0x0000028C length: 4000
            void* soundFileDataPointerArray_0x122c[1000]; // 0x0000122C length: 4000
            int soundFileSizes_0x21cc[1000]; // 0x000021CC length: 4000
            int loadedSoundsCountAndIndex_0x316c; // 0x0000316C length: 4
            int sampleVolume; // 0x00003170 length: 4
            int sampleSndStructVolumePercentage_0x3174[32]; // 0x00003174 length: 128
            int samplePaused_0x31f4[32]; // 0x000031F4 length: 128
            int sec_Section1055_0x3274; // 0x00003274 length: 4
            int currentSoundID_0x3278; // 0x00003278 length: 4
            dword currentSoundIDVolumeUnk_0x327c; // 0x0000327C length: 4
            dword mbr_0x3280; // 0x00003280 length: 4
            int lastUsedSpeechStreamUnk_0x3284; // 0x00003284 length: 4
            dword mbr_0x3288; // 0x00003288 length: 4

        private:
            SoundSystem(SoundSystem const&);
            void operator=(SoundSystem const&);

        public:
            SoundSystem() {};
            ~SoundSystem() {};

            void stopSpeechStreams();

            void stopMusicPlayback();

            void endAllSoundStreams();

            void endSoundStream(SHC_SoundStreamInt sndStreamIndex);

            BOOLEnum isSampleOrStreamPlaying(SHC_SoundStreamInt streamIndex);

            BOOLEnum shouldSoundXNotBePlaying();

            void setSoundStreamVolume(SHC_SoundStreamInt sndStreamIndex, int volumeParam);

            void updateMusicStreamVolume();

            void allocateSampleSlotForSound(int soundIndex);

            void setupSampleForNextSound(int soundIndex, int sampleVolumePercentage, int samplePan);

            BOOLEnum getAndUpdateSampleStatus(int soundIndex);

            void playSound(int soundIndex);

            void setStreamOrSampleVolume(int streamIndex, int volume);

            void deactivateAllSound();

            void pauseAudioSample();

            void resumeAudioSample();

            void resetSoundAndBattleStateOnLaunch();

            void setupVolumeAndSoundID(eMusicIDsInt soundID);

            void setupVolumeAndSoundIDWithMultiplier(eMusicIDsInt soundID, int soundMultiplier);

            void setSoundSystemFlag();

            void setSomeSoundTime();

            void setupVolumeAndSoundID0xF0_100();

            void setSection1079_28_4_(int param_1);

            void playBattleGloryMusic();

            void playDarMehqOrGlory();

            void playWinMusicVariation();

            void setupLossMusic();

            void shutdownSoundSystem();

            void serviceMusicStreamBuffer();

            void stopAllSpeechAndSamples();

            void endSpeechSoundStreams();

            void playRandomMusic02(int param_1);

            void handleBattleEndMusicTransition();

            void playSoundStreamOnSlot(
                SHC_SoundStreamInt sndStreamIndex, char* filename, UnkSoundFlagsAndLoopCount flagsAndLoopCount);

            void setCurrentSoundFile(char* filename);

            void playMusicOnceWithVolume(char* filename, int someVolumeUnk);

            void playMusicLoopingWithVolume(char* filename, int volume);

            void openSound(char* filePath);

            void playSfx1StreamLooping(char* filename);

            void playSoundOnSoundStream2(char* filename);

            void playSoundOnSpeechStream(char* filename);

            void playSpeechSfx(char* soundFileName);

            void playSoundStreamFile(char* param_1);

            void playMusicFile(char* filename, UnkSoundFlagsAndLoopCount flagsAndLoop);

            void playSfx1Stream(char* soundFileName, UnkSoundFlagsAndLoopCount flagsAndLoopCount);

            void playSoundOnSfxSoundStream2(char* filename, UnkSoundFlagsAndLoopCount flagsAndLoopCount);

            void playSpeechOnStream(char* filename, UnkSoundFlagsAndLoopCount flagsAndLoopCount);

            void resumeMusicPlayback();

            void playRandomAmbientMusic();

            void chooseNextBattleMusicTrack();

            void initMiles();
        };

        static_assert_cpp98_obj(sizeof(SoundSystem) == 12940, SoundSystem);

#pragma pack(pop)

    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
