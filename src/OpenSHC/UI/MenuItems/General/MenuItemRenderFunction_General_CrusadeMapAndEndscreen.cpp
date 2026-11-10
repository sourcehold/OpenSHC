#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_SkirmishTrailRelated1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed2bdc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8DF0
        void General::MenuItemRenderFunction_General_CrusadeMapAndEndscreen(int button, ...)
        {
            if (button == 1000) {
                // the skip-mission button, with the number of skips (chickens) left
                // cleared, then set when hovered (a copy of the hover flag: quick_diff 0.9464 -> 0.8000)
                INT_00ed2bdc::instance = FALSE;
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    INT_00ed2bdc::instance = TRUE;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_SkirmishTrailRelated1::instance, DAT_ButtonX::instance + 53, DAT_ButtonY::instance + 98,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 15, FALSE, 0);
                if (!INT_00ed2bdc::instance) {
                    return;
                }
                // hovered: a caption 400 and 583 pixels in from the menu's corner; the count is compared signed
                // y then x, before the test (x first: quick_diff 0.9464 -> 0.8750)
                int const textY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 583;
                int const textX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // one call per caption, merged but for the index (an index local: quick_diff 0.9464 -> 0.8468)
                if (DAT_SkirmishTrailRelated1::instance > 0) {
                    // "Skip Current Mission"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_CHEATS, 0),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    return;
                }
                // "No Chickens Left"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_CHEATS, 1),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                return;
            }
            if (button == 10 || button == 11 || button == 99) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
        }

    }
}
}
