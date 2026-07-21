// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LastSpeechSFXFilename.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // TODO: Confirm: Seems to be for engineers speech, triggers on them and has switch for second campaign

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A290
        void SFXState::playUnitSpeechEffect(uint speechEffectID)
        {
            int iVar4 = 0;
            if (speechEffectID > 39) {
                return;
            }

            int iVar2 = DAT_SpeechDefinedData::instance.DAT_SpeechEffectPathArray[speechEffectID].field0_0x0;
            if (!iVar2) {
                return;
            }
            if (1 < iVar2) {
                iVar4 = DAT_SpeechDefinedData::instance.DAT_SpeechEffectPathArray[speechEffectID].field3_0xc++;
                if (DAT_SpeechDefinedData::instance.DAT_SpeechEffectPathArray[speechEffectID].field3_0xc >= iVar2) {
                    DAT_SpeechDefinedData::instance.DAT_SpeechEffectPathArray[speechEffectID].field3_0xc = 0;
                }
            }

            char fullSoundPath[64];
            if (DAT_GameCore::instance.historicCampaignNumber == 2) {
                MACRO_CALL(OS_Func::_sprintf)(fullSoundPath, "fx\\speech\\%s",
                    DAT_SpeechDefinedData::instance.DAT_SpeechEffectPathArray[iVar4 + speechEffectID].arabianSound);
            } else {
                MACRO_CALL(OS_Func::_sprintf)(fullSoundPath, "fx\\speech\\%s",
                    DAT_SpeechDefinedData::instance.DAT_SpeechEffectPathArray[iVar4 + speechEffectID].europeanSound);
            }

            if (!MACRO_CALL(OS_Func::__stricmp)(fullSoundPath, DAT_LastSpeechSFXFilename::instance)) {
                if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SPEECH_1)
                    || MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SPEECH_2)) {
                    return;
                }
            }
            strcpy(DAT_LastSpeechSFXFilename::instance, fullSoundPath);
            MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSpeechStream, DAT_SoundSystemState::ptr)(fullSoundPath);
        }

    }
}
}
