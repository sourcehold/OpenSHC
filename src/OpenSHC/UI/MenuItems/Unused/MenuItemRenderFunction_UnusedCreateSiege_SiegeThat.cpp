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
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/INT_00b960ec.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00430BF0
        void Unused::MenuItemRenderFunction_UnusedCreateSiege_SiegeThat(int button, ...)
        {
            if (button == -1 || DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            if (button == 5) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            if ((button == 35 || button == 36) && !INT_00b960ec::instance) {
                // "Save Map" and "Lock Map", greyed out while INT_00b960ec is 0
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                    AlphaAndButtonSurfaceObj::ptr)(0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, 8355711, 17, FALSE);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            if (DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17,
                    FALSE);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_MAPEDIT, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                DAT_ButtonY::instance + 10, OpenSHC::Text::TTA_CENTER, 12775659, 17, FALSE);
        }

    }
}
}
