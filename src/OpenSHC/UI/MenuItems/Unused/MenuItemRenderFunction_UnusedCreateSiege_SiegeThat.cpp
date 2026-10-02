#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00430BF0
        void Unused::MenuItemRenderFunction_UnusedCreateSiege_SiegeThat(int param_1, ...)
        {
            int yParam;
            uint color_00;
            uint color;
            if (((param_1 != -1)
                    && (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU))
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if (param_1 == 5) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                if (((param_1 == 0x23) || (param_1 == 0x24)) && (INT_00b960ec::instance == 0)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                        AlphaAndButtonSurfaceObj::ptr)(0);
                    color_00 = 0x7f7f7f;
                    yParam = DAT_ButtonY::instance + 10;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        color_00 = 0xc2f0eb;
                        yParam = DAT_ButtonY::instance + 10;
                    } else {
                        color_00 = 0xccfaff;
                        yParam = DAT_ButtonY::instance + 10;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, param_1,
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)), yParam, OpenSHC::Text::TTA_CENTER,
                    color_00, 0x11, FALSE);
            }
        }

    }
}
}
