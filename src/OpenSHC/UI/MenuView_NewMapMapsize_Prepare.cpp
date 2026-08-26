#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042F3D0
void UI::MenuView_NewMapMapsize_Prepare()
{
    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
        s_frontend_builder2_tgx_005a206c);
    MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
}

}
