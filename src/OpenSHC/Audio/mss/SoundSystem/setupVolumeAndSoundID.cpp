#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A1B0
        void SoundSystem::setupVolumeAndSoundID(eMusicIDsInt soundID)
        {
            // NOTE: Is this certain that these ids fit to the original game?
            if (soundID == DE::SHCDE::MUSIC_TUNE_NARR1) {
                // missionNumber1to20 might be unsigned, but found signs inconclusive
                if (DAT_GameCore::ptr->missionNumber1to20 - 1U <= 19) {
                    soundID = DAT_GameCore::ptr->missionNumber1to20 + 46;
                } else {
                    soundID = DE::SHCDE::MUSIC_TUNE_OFF;
                }
            }

            if (soundID == this->currentSoundID_0x3278) {
                return;
            }
            this->currentSoundID_0x3278 = soundID;
            int const fileVolume = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(
                DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[soundID].musicFile);
            this->currentSoundIDVolumeUnk_0x327c = (fileVolume * 100) / 0x7f;
            this->mbr_0x3280 = 0;
        }

    }
}
}
