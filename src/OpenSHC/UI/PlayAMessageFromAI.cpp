#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {

/*
  Plays a WAV sound effect from the mission aesthetics data table. param_1 is the column index
   (0-16) and param_2 is the row index (1-33). Bounds-checks both params and calls
   SFXState::playWAVSFX with the resolved filename pointer.

   renamed by: Claude Sonnet 4.6
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004B7F60
void UI::PlayAMessageFromAI(uint param_1, int param_2)

{
    if ((param_1 < 0x11) && (param_2 - 1U < 0x21)) {
        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
            (char const*)DAT_MissionAestheticsDefinedData::instance.field92_0x170[param_2 * 0x11 + param_1 + -0xc]);
    }
    return;
}

}
