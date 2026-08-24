#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MissingResourceState.func.hpp"



#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace UI {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AF840
void Rendering::RenderResourceMissing2DisplayElement(int posX,int posY,DWORD elementState)

{
MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::renderResourceMissingText, DAT_MissingResourceState::ptr)(posX, posY, (dword)((int)(elementState)), 2);
return;
}


}
}