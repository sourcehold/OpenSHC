#include "../Helpers.func.hpp"

#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB180
    void Helpers::BuildIntroLogoSequence(undefined4, undefined4)
    {
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        // "logo1.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_logo1_tgx_005a1f74);
        // "logo2.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_logo2_tgx_005a1f68);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsListTerminator)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(18);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 60);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(19);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsPauseCommand)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(8, 0);
    }

}
}
