#include "../SoundSystem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A220
        void SoundSystem::setupVolumeAndSoundIDWithMultiplier(eMusicIDs soundID, int soundMultiplier)
        {
            int soundIDTemp = (int)soundID;

            // Indicator to handle as mission sound (?)
            if (soundIDTemp == DE::SHCDE::MUSIC_TUNE_NARR1) {
                // missionNumber1to20 might be unsigned, but found signs inconclusive
                if (DAT_GameCore::ptr->missionNumber1to20 - 1U <= 19) {
                    // This makes the soundID "missionNumber1to20 + 46", which would use the enums 47 to 66.
                    // These are only filled by 4 enums for 4 mission intros, so this space could be made for 20.
                    soundIDTemp = DAT_GameCore::ptr->missionNumber1to20 + 46;
                } else {
                    soundIDTemp = DE::SHCDE::MUSIC_TUNE_OFF;
                }
            }

            if (soundIDTemp == this->currentSoundID_0x3278) {
                return;
            }
            this->currentSoundID_0x3278 = soundIDTemp;
            int const fileVolume = MACRO_CALL_MEMBER(SFX::SFXState_Func::getSoundVolumeForFilename, DAT_SFXState::ptr)(
                DAT_SFXDefinedData::ptr->DAT_SFX_Pointers[soundIDTemp].musicFile);
            // 0x7f is the maximum volume of the MSS32 volume API.
            this->currentSoundIDVolumeUnk_0x327c = (fileVolume * soundMultiplier) / 0x7f;
            this->mbr_0x3280 = 0;
        }

    }
}
}
