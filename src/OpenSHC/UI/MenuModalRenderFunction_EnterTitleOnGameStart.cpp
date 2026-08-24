#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00491BF0
void UI::MenuModalRenderFunction_EnterTitleOnGameStart(int x,int y,int width,int height)

{
/* 
  added by script: "Enter Your Title"
 */

MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(5, 6, x, y, width);
return;
}


}