#include "OpenSHC/UI/MinimapViewState.func.hpp"





namespace OpenSHC {
namespace UI {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004B5300
void MinimapViewState::triggerMinimapRedraw()

{
if (this->field14_0x38 == 0) {
this->field13_0x34 = 0;
this->field14_0x38 = 2;
return;
}
this->field14_0x38 = 1;
return;
}


}
}