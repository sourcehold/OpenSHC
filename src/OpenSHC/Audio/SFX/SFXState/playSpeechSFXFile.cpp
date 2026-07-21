// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_LastSpeechSFXFilename.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A5A0
        void SFXState::playSpeechSFXFile(char* filename)
        {
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_SPEECH_1)) {
                return;
            }
            if (MACRO_CALL_MEMBER(MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    MSS::enums::SND_STR_SPEECH_2)) {
                return;
            }
            strcpy(DAT_LastSpeechSFXFilename::instance, filename);

            char _filePath[64];
            MACRO_CALL(OS_Func::_sprintf)(_filePath, "fx\\speech\\%s", filename);
            MACRO_CALL_MEMBER(MSS::SoundSystem_Func::playSoundOnSpeechStream, DAT_SoundSystemState::ptr)(_filePath);
        }

    }
}
}
