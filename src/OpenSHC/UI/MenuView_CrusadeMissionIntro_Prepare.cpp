#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"



#include "OpenSHC/Globals/INT_00eb9ae8.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004D8AB0
void UI::MenuView_CrusadeMissionIntro_Prepare()

{
DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("skirmish_background.tgx");
MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
INT_00eb9ae8::instance = 0;
DAT_MissionDefinedData::instance.field26_0xaf8 = true;
return;
}


}