#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004271E0
void UI::MenuView_General_DoEveryFrame_FirstGfxCentered()

{
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface, DAT_TextureRenderCoreObject::ptr)(0, 
(DAT_WindowAndDirectDraw::instance.resolutionX -
DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width) / 2, 
(DAT_WindowAndDirectDraw::instance.resolutionY -
DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height) / 2);
return;
}


}