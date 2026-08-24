#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI.func.hpp"





namespace OpenSHC {
namespace UI {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::UI::Enums::DisplayElementID;
using OpenSHC::UI::DisplayElement;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AF6E0
BOOLEnum Helpers::GetIfDisplayElementStateNotZero(DisplayElementID displayElementID)

{
DisplayElement *_displayElementPtr;

_displayElementPtr = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(displayElementID);
if (_displayElementPtr != (DisplayElement *)0x0) {
return (uint)(_displayElementPtr->elementStateUnk_0xc != 0);
}
return FALSE;
}


}
}