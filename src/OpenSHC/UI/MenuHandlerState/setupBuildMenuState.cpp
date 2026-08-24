#include "OpenSHC/UI/MenuHandlerState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace UI {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004F4C60
void MenuHandlerState::setupBuildMenuState(dword param_1,dword param_2)

{
this->isBuildMenuTransitioning_0x18 = FALSE;
this->buildMenuBackgroundLeftShift_0x24 = 0;
this->buildMenuTransitionDirection_0x2c = -1;
this->const017 = param_1;
this->const516 = param_2;
return;
}


}
}