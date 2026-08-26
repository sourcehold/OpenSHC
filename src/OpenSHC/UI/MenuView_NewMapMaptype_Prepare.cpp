#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042EFE0
void UI::MenuView_NewMapMaptype_Prepare()
{
    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
        s_frontend_builder_tgx_005a2084);
    MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
    DAT_GameCore::instance.mapU3EndInt = 0;
}

}
