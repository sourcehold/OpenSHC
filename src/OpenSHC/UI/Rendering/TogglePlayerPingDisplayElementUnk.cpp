#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI.func.hpp"





namespace OpenSHC {
namespace UI {

using OpenSHC::UI::Enums::DisplayElementID;
using OpenSHC::UI::DisplayElement;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AF6B0
void Rendering::TogglePlayerPingDisplayElementUnk(DisplayElementID displayElementID,uint toggleValue)

{
DisplayElement *_displayElement;

_displayElement = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(displayElementID);
if (_displayElement != (DisplayElement *)0x0) {
_displayElement->displayDuration_0x14 = -1;
_displayElement->elementStateUnk_0xc =
~-(uint)(_displayElement->elementStateUnk_0xc != 0) &toggleValue;
}
return;
}


}
}