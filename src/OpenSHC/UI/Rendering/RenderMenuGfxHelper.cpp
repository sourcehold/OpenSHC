#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004DA640
void Rendering::RenderMenuGfxHelper(int gfxIndex,int x,int y,int blendStrength)

{
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGfxTgxWithBlending, DAT_TextureRenderCoreObject::ptr)(gfxIndex, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + x, 
DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + y, blendStrength);
return;
}


}
}