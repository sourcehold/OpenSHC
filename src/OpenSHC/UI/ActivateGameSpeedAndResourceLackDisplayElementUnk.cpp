#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

namespace OpenSHC {

using OpenSHC::UI::DisplayElement;
using OpenSHC::UI::Enums::DisplayElementID;

// FUNCTION: STRONGHOLDCRUSADER 0x004AF680
void UI::ActivateGameSpeedAndResourceLackDisplayElementUnk(
    DisplayElementID elementId, dword elementState, int displayDuration)
{
    DisplayElement* _displayElementPtr = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(elementId);
    if (_displayElementPtr != (DisplayElement*)0x0) {
        _displayElementPtr->elementStateUnk_0xc = elementState;
        _displayElementPtr->displayDuration_0x14 = displayDuration;
        DWORD _currentTime = timeGetTime();
        _displayElementPtr->activationTime_0x10 = _currentTime;
    }
}

}
