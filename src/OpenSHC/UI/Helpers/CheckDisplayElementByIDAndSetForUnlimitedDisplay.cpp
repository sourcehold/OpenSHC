#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/BOOL_RelatedToInitialGranaryAndKeepPlacement.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::UI::Enums::DisplayElementID;
using OpenSHC::UI::DisplayElement;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AF650
void Helpers::CheckDisplayElementByIDAndSetForUnlimitedDisplay(DisplayElementID displayElementID,dword elementState)

{
DisplayElement *_displayElementPtr;

_displayElementPtr = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(displayElementID);
if (_displayElementPtr != (DisplayElement *)0x0) {
if (_displayElementPtr->elementStateUnk_0xc != elementState) {
BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = FALSE;
}
_displayElementPtr->elementStateUnk_0xc = elementState;
_displayElementPtr->displayDuration_0x14 = -1;
}
return;
}


}
}