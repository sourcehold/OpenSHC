// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LastSpeechSFXFilename.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A3A0
        void SFXState::playSpeechSFX(SpeechEffectID speechID)
        {
            if (speechID < SEID_GENERAL_STARTGAME || SEID_GENERAL_MESSAGE3 < speechID
                || (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE
                    && SEID_POP_FALLING <= speechID && speechID <= SEID_TAXES_RATE8)) {
                return;
            }

            char fullSoundPath[64];
            MACRO_CALL(OS_Func::_sprintf)(fullSoundPath, s_fx_speech_s_005a4d68,
                DAT_SpeechDefinedData::instance.DAT_SpeechEffectFileArray[speechID]);
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
