#include "../Credits.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00b95b3c.hpp"
#include "OpenSHC/Globals/DAT_00b95b70.hpp"
#include "OpenSHC/Globals/DAT_00b9610c.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b95954.hpp"
#include "OpenSHC/Globals/INT_00b960d0.hpp"
#include "OpenSHC/Globals/INT_00b960d4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Credits {

            // FUNCTION: STRONGHOLDCRUSADER 0x004261E0
            void MenuView_Credits_Prepare()
            {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                if (INT_00b95954::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_credits_1_tgx_005a20e8);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_credits_2_tgx_005a20d8);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_credits_3_tgx_005a20c8);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_credits_4_tgx_005a20b8);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_end_credit_tgx_005a20a8);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::openCreditsScrollDialog, DAT_TextEditorState::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                        DAT_TextEditorState::ptr)((char*)s_credits_hlp_005a209c));
                DAT_TextEditorState::instance.helpContentScrollOffsetY = -600;
                DAT_00b95b3c::instance = 0;
                INT_00b960d0::instance = timeGetTime();
                DAT_00b95b70::instance = 0;
                DAT_00b9610c::instance = 1;
                MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
                INT_00b960d4::instance = timeGetTime();
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                    DAT_WindowAndDirectDraw::instance.resolutionY, COL_BLACK::instance.shortValue);
            }

        }
    }
}
}
