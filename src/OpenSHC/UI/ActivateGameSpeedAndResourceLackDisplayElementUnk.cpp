#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"





namespace OpenSHC {

using OpenSHC::UI::Enums::DisplayElementID;
using OpenSHC::UI::DisplayElement;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AF680
void UI::ActivateGameSpeedAndResourceLackDisplayElementUnk(DisplayElementID elementId,dword elementState,int displayDuration)

{
DisplayElement *_displayElementPtr;
DWORD _currentTime;

_displayElementPtr = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(elementId);
if (_displayElementPtr != (DisplayElement *)0x0) {
_displayElementPtr->elementStateUnk_0xc = elementState;
_displayElementPtr->displayDuration_0x14 = displayDuration;
_currentTime = timeGetTime();
_displayElementPtr->activationTime_0x10 = _currentTime;
}
return;
}


}