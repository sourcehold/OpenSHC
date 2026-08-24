#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004ABE50
void UI::MenuModalRenderFunction_SkirmishConnectionOptions(int x,int y,int width,int height)

{
/* 
  added by script: "Connection options"
 */

MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(0x4f, 0x5d, x, y, width);
return;
}


}