#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042BB70
void UI::MenuView_General_Prepare_SwordShieldAndBorder()
{
    DAT_GameSynchronyState::instance.field225_0x106ee4 = 0;
    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
        s_frontend_combat3_tgx_005a2134);
    MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
}

}
