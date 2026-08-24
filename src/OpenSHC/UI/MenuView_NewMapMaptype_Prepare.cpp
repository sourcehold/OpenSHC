#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0042EFE0
void UI::MenuView_NewMapMaptype_Prepare()

{
DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("frontend_builder.tgx");
MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
DAT_GameCore::instance.mapU3EndInt = 0;
return;
}


}