#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        /*
          Plays a WAV sound effect from the mission aesthetics data table. param_1 is the column index
           (0-16) and param_2 is the row index (1-33). Bounds-checks both params and calls
           SFXState::playWAVSFX with the resolved filename pointer.

           renamed by: Claude Sonnet 4.6
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7F60
        void PlayAMessageFromAI(uint messageIndex, int speakerIndex)
        {
            if (messageIndex <= 16 && speakerIndex - 1U <= 32) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    (char const*)DAT_MissionAestheticsDefinedData::instance
                        .field92_0x170[speakerIndex * 17 + messageIndex - 12]);
            }
        }

    }
}
}
