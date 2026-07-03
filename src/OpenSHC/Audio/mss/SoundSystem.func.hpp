/**
  path: 'OpenSHC/Audio/MSS/SoundSystem.func.hpp'
*/

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Audio {
    namespace MSS {
        namespace SoundSystem_Func {

            using OpenSHC::Audio::MSS::SoundFlagsAndLoopCount;
            using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
            using OpenSHC::DE::SHCDE::eMusicIDs;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00424700,
                &SoundSystem::endSpeechStreamsAndResetLoopFlags)
            endSpeechStreamsAndResetLoopFlags;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00467810, &SoundSystem::stopMusicPlayback)
            stopMusicPlayback;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00467830, &SoundSystem::endSoundStreamsUnk)
            endSoundStreamsUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStream), false, Address::SHC_3BB0A8C1_0x004799A0,
                &SoundSystem::endSoundStream)
            endSoundStream;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (SoundSystem::*)(SHC_SoundStream), false, Address::SHC_3BB0A8C1_0x00479A60,
                &SoundSystem::isSampleOrStreamPlaying)
            isSampleOrStreamPlaying;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00479AB0,
                &SoundSystem::shouldSoundXNotBePlaying)
            shouldSoundXNotBePlaying;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStream, int), false,
                Address::SHC_3BB0A8C1_0x00479AF0, &SoundSystem::setStreamAndSampleVolumeUnk)
            setStreamAndSampleVolumeUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00479B70,
                &SoundSystem::restoreMusicVolumeAfterSpeechEnds)
            restoreMusicVolumeAfterSpeechEnds;

            MACRO_FUNCTION_RESOLVER(int (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x00479C20,
                &SoundSystem::loadSoundFileAndGetIndex)
            loadSoundFileAndGetIndex;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x00479C80,
                &SoundSystem::findSamplePlaceForSoundUnk)
            findSamplePlaceForSoundUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00479CF0,
                &SoundSystem::setupSampleForNextSound)
            setupSampleForNextSound;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x00479D90,
                &SoundSystem::getAndUpdateSampleStatus)
            getAndUpdateSampleStatus;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x00479DF0, &SoundSystem::playSound)
            playSound;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(int, int), false, Address::SHC_3BB0A8C1_0x00479E60, &SoundSystem::setVolumeUnk)
            setVolumeUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00479F30,
                &SoundSystem::deactivateSoundFromMenuFuncUnk)
            deactivateSoundFromMenuFuncUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00479FC0, &SoundSystem::pauseAudioSample)
            pauseAudioSample;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A080, &SoundSystem::resumeAudioSample)
            resumeAudioSample;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A130,
                &SoundSystem::mapLoadingAndLaunchGameRelated1)
            mapLoadingAndLaunchGameRelated1;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(eMusicIDs), false, Address::SHC_3BB0A8C1_0x0047A1B0,
                &SoundSystem::setupVolumeAndSoundID)
            setupVolumeAndSoundID;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(eMusicIDs, int), false, Address::SHC_3BB0A8C1_0x0047A220,
                &SoundSystem::setupVolumeAndSoundIDWithMultiplier)
            setupVolumeAndSoundIDWithMultiplier;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A290, &SoundSystem::markMusicChangePending)
            markMusicChangePending;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A2A0, &SoundSystem::setSomeSoundTime)
            setSomeSoundTime;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A310,
                &SoundSystem::setupVolumeAndSoundID0xF0_100)
            setupVolumeAndSoundID0xF0_100;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A340,
                &SoundSystem::selectAndPlayMoodBasedMusic)
            selectAndPlayMoodBasedMusic;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x0047A570, &SoundSystem::setSection1079_28_4_)
            setSection1079_28_4_;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A580,
                &SoundSystem::playBattleGloryMusicIfConditionsMet)
            playBattleGloryMusicIfConditionsMet;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A5E0, &SoundSystem::playDarMehqOrGlory)
            playDarMehqOrGlory;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A630, &SoundSystem::playWinMusicVariation)
            playWinMusicVariation;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A660, &SoundSystem::setupLossMusic)
            setupLossMusic;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A690, &SoundSystem::shutdownSoundSystem)
            shutdownSoundSystem;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A790, &SoundSystem::playMusicUnk)
            playMusicUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A9E0, &SoundSystem::stopAllActiveSounds)
            stopAllActiveSounds;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047AA70, &SoundSystem::endSpeechSoundStreams)
            endSpeechSoundStreams;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x0047AB10, &SoundSystem::playRandomMusic02)
            playRandomMusic02;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047AF50,
                &SoundSystem::handleBattleEndMusicTransition)
            handleBattleEndMusicTransition;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStream, char*, SoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B060, &SoundSystem::playSoundStreamUnk)
            playSoundStreamUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B250,
                &SoundSystem::playMusicFileByName)
            playMusicFileByName;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, int), false, Address::SHC_3BB0A8C1_0x0047B2F0,
                &SoundSystem::playOrSetupMusicUnk)
            playOrSetupMusicUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, int), false, Address::SHC_3BB0A8C1_0x0047B3C0,
                &SoundSystem::playOrEndMusicUnk)
            playOrEndMusicUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B490, &SoundSystem::openSound)
            openSound;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B590,
                &SoundSystem::playOnSfx1SoundStreamOnceOrOnRepeatUnk)
            playOnSfx1SoundStreamOnceOrOnRepeatUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B5C0,
                &SoundSystem::playSoundOnSoundStream2)
            playSoundOnSoundStream2;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B5F0,
                &SoundSystem::playSoundOnSpeechStream)
            playSoundOnSpeechStream;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B670, &SoundSystem::playSpeechSfx)
            playSpeechSfx;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B700,
                &SoundSystem::playAmbientStreamWithLoop)
            playAmbientStreamWithLoop;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, SoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B760, &SoundSystem::playSomeMusicUnk)
            playSomeMusicUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, SoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B7D0, &SoundSystem::playOnSfx1SoundStreamUnk)
            playOnSfx1SoundStreamUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, SoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B800, &SoundSystem::playSoundOnSfxSoundStream2)
            playSoundOnSfxSoundStream2;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, SoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B830, &SoundSystem::playSoundOnStream3Unk)
            playSoundOnStream3Unk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047B870,
                &SoundSystem::activateSoundFromMenuFuncUnk)
            activateSoundFromMenuFuncUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047B890, &SoundSystem::playRandomAmbientMusic)
            playRandomAmbientMusic;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047BF20,
                &SoundSystem::playRandomBackgroundMusicUnk)
            playRandomBackgroundMusicUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047C400, &SoundSystem::initMiles)
            initMiles;

        } // namespace SoundSystem_Func
    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
