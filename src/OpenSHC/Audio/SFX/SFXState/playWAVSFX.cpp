// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_LastSpeechSFXFilename.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A460
        void SFXState::playWAVSFX(char const* wav_filename)
        {
            if (!MACRO_CALL(OS_Func::__stricmp)(wav_filename, DAT_LastSpeechSFXFilename::instance)) {
                if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SPEECH_1)
                    || MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                        MSS::enums::SND_STR_SPEECH_2)) {
                    if (MACRO_CALL(OS_Func::__stricmp)(wav_filename, s_buildingwreck_01_wav_005a4d78)) {
                        return;
                    }
                }
            }
            strcpy(DAT_LastSpeechSFXFilename::instance, wav_filename);

            char fullSoundPath[64];
            MACRO_CALL(OS_Func::_sprintf)(fullSoundPath, s_fx_speech_s_005a4d68, wav_filename);
            MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSpeechStream, DAT_SoundSystemState::ptr)(fullSoundPath);
        }

    }
}
}
