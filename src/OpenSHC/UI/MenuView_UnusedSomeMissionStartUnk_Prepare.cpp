#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x00426F80
void UI::MenuView_UnusedSomeMissionStartUnk_Prepare()
{
    DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
        s_multi_background_tgx_005a211c);
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
        s_gm_fly_tgx_005a2110);
    MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
}

}
