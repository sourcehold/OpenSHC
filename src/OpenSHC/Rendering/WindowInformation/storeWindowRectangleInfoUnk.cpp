#include "OpenSHC/Rendering/WindowInformation.func.hpp"





namespace OpenSHC {
namespace Rendering {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00467F60
void WindowInformation::storeWindowRectangleInfoUnk(LONG param_1,LONG param_2,LONG param_3,LONG param_4)

{
this->RECT_SomeGameWindowRectUnk.left = param_1;
this->RECT_SomeGameWindowRectUnk.top = param_3;
this->RECT_SomeGameWindowRectUnk.right = param_2;
this->RECT_SomeGameWindowRectUnk.bottom = param_4;
return;
}


}
}