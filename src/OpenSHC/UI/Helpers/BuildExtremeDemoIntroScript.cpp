#include "../Helpers.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DC1C0
    void Helpers::BuildExtremeDemoIntroScript()
    {
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        // "bullet2.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_bullet2_tgx_005ab220);
        // "p4.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_p4_tgx_005ab1d4);
        // "p3.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_p3_tgx_005ab1cc);
        // "p1.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_p1_tgx_005ab1c4);
        // "p2.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_p2_tgx_005ab1bc);
        // "demo1.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_demo1_tgx_005ab214);
        // "demo2.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_demo2_tgx_005ab208);
        // "demo3.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_demo3_tgx_005ab1fc);
        // "demo4.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_demo4_tgx_005ab1f0);
        // "logo_280x100.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_logo_280x100_tgx_005ab1dc);
        for (int line = 0; line < 5; ++line) {
            // the demo's five feature lines, from "Cut a path through an increasingly tough extreme trail."
            MACRO_CALL(UI::Helpers_Func::StoreStringInMenuStringArray)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_EXTREME_DEMO, line + 8));
        }
        // The repeated blocks are written out: the original has no loop here.
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 5);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(18);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(44, 180);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(19);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 6);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(18);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(44, 180);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(19);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 7);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(18);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(44, 180);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(19);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundEntry)(1, 8);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(18);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(20, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(44, 180);
        MACRO_CALL(UI::Credits_Func::AppendCreditsCommand)(43);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 9, 260, 10, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(2, 9);
        // Written out too: a for loop over these five blocks stays a loop, and the original has none.
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 40);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 95, 128, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 0, 18, 0, 135, 140, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 40);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 95, 208, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 1, 18, 0, 135, 220, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 1);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 40);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 95, 288, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 2, 18, 0, 135, 300, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 2);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 40);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 95, 368, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 3, 18, 0, 135, 380, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 3);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(1, 40);
        MACRO_CALL(UI::Credits_Func::AppendCreditsImageTransitionCommand)(6, 0, 95, 448, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsTextCommand)(15, 4, 18, 0, 135, 460, 600, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(3, 4);
        MACRO_CALL(UI::Credits_Func::AppendCreditsFixedImageCommand)(1, 684, 550);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(22, 0);
        MACRO_CALL(UI::Credits_Func::AppendCreditsSegmentEndCommand)();
        MACRO_CALL(UI::Credits_Func::AppendCreditsSoundStreamCommand)(25, 0);
    }

}
}
