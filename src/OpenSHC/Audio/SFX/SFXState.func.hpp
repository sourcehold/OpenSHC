/**
  path: 'OpenSHC/Audio/SFX/SFXState.func.hpp'
*/

#include "OpenSHC/Audio/SFX/AmbientSFXType.hpp"
#include "OpenSHC/Audio/SFX/SFXState.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
namespace OpenSHC {
namespace Audio {
    namespace SFX {
        namespace SFXState_Func {

            using OpenSHC::Audio::SFX::AmbientSFXType;
            using OpenSHC::Audio::SFX::SoundEffectID;
            using OpenSHC::Audio::SFX::SpeechEffectID;
            using OpenSHC::DE::SHCDE::eSFX;
            using OpenSHC::Map::Units::UnitType;

            // Constructor

            MACRO_FUNCTION_RESOLVER(
                SFXState* (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044AB70, &SFXState::Constructor_SFXState)
            Constructor_SFXState;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x00449B20, &SFXState::freeMemoryAt)
            freeMemoryAt;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(char*), false, Address::SHC_3BB0A8C1_0x00449B30, &SFXState::loadWavSounds)
            loadWavSounds;

            MACRO_FUNCTION_RESOLVER(void (SFXState::*)(SoundEffectID), false, Address::SHC_3BB0A8C1_0x00449C40,
                &SFXState::setUpSFXToPlayUnk)
            setUpSFXToPlayUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00449CC0, &SFXState::setSoundWithVariation)
            setSoundWithVariation;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00449D50, &SFXState::scheduleSFXVariation)
            scheduleSFXVariation;

            MACRO_FUNCTION_RESOLVER(void (SFXState::*)(int, int, eSFX), false, Address::SHC_3BB0A8C1_0x00449DC0,
                &SFXState::playSFXAtLocation)
            playSFXAtLocation;

            MACRO_FUNCTION_RESOLVER(void (SFXState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00449F10,
                &SFXState::someVolumeAdjustmentFunction)
            someVolumeAdjustmentFunction;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x00449FF0, &SFXState::resetScheduledSoundRequests)
            resetScheduledSoundRequests;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044A050, &SFXState::resetAmbientEventCounters)
            resetAmbientEventCounters;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(int), false, Address::SHC_3BB0A8C1_0x0044A0D0, &SFXState::notifyAmbientSoundEvent)
            notifyAmbientSoundEvent;

            MACRO_FUNCTION_RESOLVER(void (SFXState::*)(AmbientSFXType), false, Address::SHC_3BB0A8C1_0x0044A0F0,
                &SFXState::playAmbientSoundStreamUnk)
            playAmbientSoundStreamUnk;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(int), false, Address::SHC_3BB0A8C1_0x0044A1B0, &SFXState::playAmbientSoundStream2Unk)
            playAmbientSoundStream2Unk;

            MACRO_FUNCTION_RESOLVER(
                int (SFXState::*)(char*), false, Address::SHC_3BB0A8C1_0x0044A240, &SFXState::getSoundVolumeForFilename)
            getSoundVolumeForFilename;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(uint), false, Address::SHC_3BB0A8C1_0x0044A290, &SFXState::playUnitSpeechEffect)
            playUnitSpeechEffect;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(SpeechEffectID), false, Address::SHC_3BB0A8C1_0x0044A3A0, &SFXState::PlaySpeechSFX)
            PlaySpeechSFX;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(char const*), false, Address::SHC_3BB0A8C1_0x0044A460, &SFXState::playWAVSFX)
            playWAVSFX;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(char*), false, Address::SHC_3BB0A8C1_0x0044A500, &SFXState::playOnSpeechSfxStream)
            playOnSpeechSfxStream;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(char*), false, Address::SHC_3BB0A8C1_0x0044A5A0, &SFXState::playSpeechSFX)
            playSpeechSFX;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044A620, &SFXState::playVictoryMusic678)
            playVictoryMusic678;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044A6E0, &SFXState::playSFXWeAreUnderAttack)
            playSFXWeAreUnderAttack;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(int, float), false, Address::SHC_3BB0A8C1_0x0044ABB0, &SFXState::tweakVolume)
            tweakVolume;

            MACRO_FUNCTION_RESOLVER(void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044AE90,
                &SFXState::readVolumeFileAndSetupSoundVolumes)
            readVolumeFileAndSetupSoundVolumes;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(UnitType, int), false, Address::SHC_3BB0A8C1_0x0044B210, &SFXState::playUnitSpeech)
            playUnitSpeech;

            MACRO_FUNCTION_RESOLVER(void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044BCA0, &SFXState::loadSFX)
            loadSFX;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044BCE0, &SFXState::updateAmbientSoundStream)
            updateAmbientSoundStream;

            MACRO_FUNCTION_RESOLVER(
                void (SFXState::*)(), false, Address::SHC_3BB0A8C1_0x0044C740, &SFXState::soundRelatedMethod1)
            soundRelatedMethod1;

        } // namespace SFXState_Func
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
