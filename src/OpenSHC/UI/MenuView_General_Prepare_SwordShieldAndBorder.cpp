#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {




/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0042BB70
void UI::MenuView_General_Prepare_SwordShieldAndBorder()

{
DAT_GameSynchronyState::instance.field225_0x106ee4 = 0;
DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("frontend_combat3.tgx");
MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
return;
}


}