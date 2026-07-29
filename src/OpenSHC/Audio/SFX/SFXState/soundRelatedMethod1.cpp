#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/BOOLEnum_00b9870c.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C740
        void SFXState::soundRelatedMethod1()
        {
            if (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != Game::GM_SOLITARY) {
                MACRO_CALL(Global_Func::PlaySFXVoices)();
            }
            MACRO_CALL_MEMBER(
                Audio::MSS::SoundSystem_Func::restoreMusicVolumeAfterSpeechEnds, DAT_SoundSystemState::ptr)();
            MACRO_CALL_MEMBER(SFXState_Func::updateAmbientSoundStream, this)();
            BOOLEnum_00b9870c::instance ^= TRUE;
            if (BOOLEnum_00b9870c::instance) {
                return;
            }

            for (int _loadedSoundIndex = 0;
                _loadedSoundIndex < DAT_SoundSystemState::ptr->loadedSoundsCountAndIndex_0x316c + 1;
                ++_loadedSoundIndex) {
                if (MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::getAndUpdateSampleStatus,
                        DAT_SoundSystemState::ptr)(_loadedSoundIndex)
                    || this->DAT_SoundStructures[_loadedSoundIndex].scheduledPlayCounter <= 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::findSamplePlaceForSoundUnk, DAT_SoundSystemState::ptr)(
                    _loadedSoundIndex);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupSampleForNextSound, DAT_SoundSystemState::ptr)(
                    _loadedSoundIndex, this->DAT_SoundStructures[_loadedSoundIndex].volumePercentage,
                    this->DAT_SoundStructures[_loadedSoundIndex].samplePan);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSound, DAT_SoundSystemState::ptr)(
                    _loadedSoundIndex);
            }
            MACRO_CALL_MEMBER(SFXState_Func::resetScheduledSoundRequests, this)();
        }

    }
}
}
