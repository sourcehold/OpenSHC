#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042FEC0
        void Unused::MenuItemRenderFunction_UnusedChooseAvailableKeeps_Main(int button, ...)
        {
            // nothing while a dialog is open
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            if (button == 7) {
                // "Back"
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            if (button < 0) {
                // buttons -1 to -5 are the five keep flags: one that is off shows button picture 112
                if (DAT_GameCore::instance.mapU2MiddleBytes[-button - 1] == 0) {
                    DAT_CurrentButtonGmDataIndex::instance = 112;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            // five tests, not a range (button >= 14 && button <= 18: quick_diff 0.9231 -> 0.6019)
            if (button != 14 && button != 15 && button != 16 && button != 17 && button != 18) {
                // "Done" is greyed out while no keep is available; a loop loses the match (quick_diff 0.9231 -> 0.8917)
                if (button == 11
                    && DAT_GameCore::instance.mapU2MiddleBytes[0] + DAT_GameCore::instance.mapU2MiddleBytes[1]
                            + DAT_GameCore::instance.mapU2MiddleBytes[2] + DAT_GameCore::instance.mapU2MiddleBytes[3]
                            + DAT_GameCore::instance.mapU2MiddleBytes[4]
                        == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                        DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F,
                        17, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // two calls, one per colour (one call with a colour local: 100.0% -> 73.3%)
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                        DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                        17, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 17,
                    FALSE);
                return;
            }
            // 14 to 18 are the keeps' names, drawn as titles
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17,
                FALSE);
        }

    }
}
}
