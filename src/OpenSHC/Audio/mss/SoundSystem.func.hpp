/**
  path: 'OpenSHC/Audio/mss/SoundSystem.func.hpp'
*/

#include "OpenSHC/Audio/mss/SoundSystem.hpp"
#include "OpenSHC/Audio/mss/UnkSoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/mss/_enums/SHC_SoundStreamInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/_SHCDE/eMusicIDsInt.hpp"
namespace OpenSHC {
namespace Audio {
    namespace mss {
        namespace SoundSystem_Func {

            using OpenSHC::_SHCDE::eMusicIDsInt;
            using OpenSHC::Audio::mss::UnkSoundFlagsAndLoopCount;
            using OpenSHC::Audio::mss::_enums::SHC_SoundStreamInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00424700, &SoundSystem::meth_0x424700)
            meth_0x424700;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00467810, &SoundSystem::stopMusicPlayback)
            stopMusicPlayback;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00467830, &SoundSystem::endSoundStreamsUnk)
            endSoundStreamsUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStreamInt), false, Address::SHC_3BB0A8C1_0x004799A0,
                &SoundSystem::endSoundStream)
            endSoundStream;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (SoundSystem::*)(SHC_SoundStreamInt), false,
                Address::SHC_3BB0A8C1_0x00479A60, &SoundSystem::isSampleOrStreamPlaying)
            isSampleOrStreamPlaying;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00479AB0,
                &SoundSystem::shouldSoundXNotBePlaying)
            shouldSoundXNotBePlaying;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStreamInt, int), false,
                Address::SHC_3BB0A8C1_0x00479AF0, &SoundSystem::setStreamAndSampleVolumeUnk)
            setStreamAndSampleVolumeUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x00479B70, &SoundSystem::meth_0x479b70)
            meth_0x479b70;

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

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(eMusicIDsInt), false, Address::SHC_3BB0A8C1_0x0047A1B0,
                &SoundSystem::setupVolumeAndSoundID)
            setupVolumeAndSoundID;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(eMusicIDsInt, int), false, Address::SHC_3BB0A8C1_0x0047A220,
                &SoundSystem::setupVolumeAndSoundIDWithMultiplier)
            setupVolumeAndSoundIDWithMultiplier;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A290, &SoundSystem::meth_0x47a290)
            meth_0x47a290;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A2A0, &SoundSystem::setSomeSoundTime)
            setSomeSoundTime;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A310,
                &SoundSystem::setupVolumeAndSoundID0xF0_100)
            setupVolumeAndSoundID0xF0_100;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x0047A570, &SoundSystem::setSection1079_28_4_)
            setSection1079_28_4_;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A580, &SoundSystem::meth_0x47a580)
            meth_0x47a580;

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
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A9E0, &SoundSystem::meth_0x47a9e0)
            meth_0x47a9e0;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047AA70, &SoundSystem::endSpeechSoundStreams)
            endSpeechSoundStreams;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(int), false, Address::SHC_3BB0A8C1_0x0047AB10, &SoundSystem::playRandomMusic02)
            playRandomMusic02;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0044A620,
                &SoundSystem::handleBattleEndMusicTransition)
            handleBattleEndMusicTransition;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStreamInt, char*, UnkSoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B060, &SoundSystem::playSoundStreamUnk)
            playSoundStreamUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B250, &SoundSystem::meth_0x47b250)
            meth_0x47b250;

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

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(char*), false, Address::SHC_3BB0A8C1_0x0047B700, &SoundSystem::meth_0x47b700)
            meth_0x47b700;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, UnkSoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B760, &SoundSystem::playSomeMusicUnk)
            playSomeMusicUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, UnkSoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B7D0, &SoundSystem::playOnSfx1SoundStreamUnk)
            playOnSfx1SoundStreamUnk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, UnkSoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B800, &SoundSystem::playSoundOnSfxSoundStream2)
            playSoundOnSfxSoundStream2;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(char*, UnkSoundFlagsAndLoopCount), false,
                Address::SHC_3BB0A8C1_0x0047B830, &SoundSystem::playSoundOnStream3Unk)
            playSoundOnStream3Unk;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047B870,
                &SoundSystem::activateSoundFromMenuFuncUnk)
            activateSoundFromMenuFuncUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047A340, &SoundSystem::playRandomAmbientMusic)
            playRandomAmbientMusic;

            MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047BF20,
                &SoundSystem::playRandomBackgroundMusicUnk)
            playRandomBackgroundMusicUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SoundSystem::*)(), false, Address::SHC_3BB0A8C1_0x0047C400, &SoundSystem::initMiles)
            initMiles;

        } // namespace SoundSystem_Func
    } // namespace mss
} // namespace Audio
} // namespace OpenSHC
