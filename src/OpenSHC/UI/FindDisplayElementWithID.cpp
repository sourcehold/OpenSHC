#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"



#include "OpenSHC/Globals/DAT_PointerToDisplayElementStackTop.hpp"

namespace OpenSHC {

using OpenSHC::UI::DisplayElement;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AF630
DisplayElement * UI::FindDisplayElementWithID(int elementID)

{
DisplayElement *pDVar1;
DisplayElement *_displayElementPtrUnk;

pDVar1 = DAT_PointerToDisplayElementStackTop::instance;
while( true ) {
if (pDVar1 == (DisplayElement *)0x0) {
return (DisplayElement *)0x0;
}
if (pDVar1->elementID_0x8 == elementID) break;
pDVar1 = pDVar1->nextDisplayElement_0x20;
}
return pDVar1;
}


}