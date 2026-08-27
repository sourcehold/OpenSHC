#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00433230
void UI::MenuItemActionHandler_InGameMenu_UnknownBinkRelated(int param_1, ...)
{
    if (DAT_GameCore::instance.isBinkVideoPlaying != 0) {
        if (DAT_BinkControlState::instance.binkObjPtrArray[1] == NULL) {
            DAT_GameCore::instance.isBinkVideoPlaying = 0;
        }
        DAT_GameCore::instance.countdown = 1;
    }
}

}
