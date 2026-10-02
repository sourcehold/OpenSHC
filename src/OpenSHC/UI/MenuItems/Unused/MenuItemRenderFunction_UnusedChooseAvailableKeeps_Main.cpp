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
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0042FEC0
        void Unused::MenuItemRenderFunction_UnusedChooseAvailableKeeps_Main(int param_1, ...)
        {
            uint color;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                if (param_1 == 7) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                if (param_1 < 0) {
                    if (*(int*)((int)DAT_GameCore::ptr + param_1 * -4 + 0x1534) == 0) {
                        DAT_CurrentButtonGmDataIndex::instance = 0x70;
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                if ((((param_1 != 0xe) && (param_1 != 0xf)) && (param_1 != 0x10))
                    && ((param_1 != 0x11 && (param_1 != 0x12)))) {
                    if ((param_1 == 0xb)
                        && (DAT_GameCore::instance.mapU2MiddleBytes[4] + DAT_GameCore::instance.mapU2MiddleBytes[3]
                                + DAT_GameCore::instance.mapU2MiddleBytes[2]
                                + DAT_GameCore::instance.mapU2MiddleBytes[1]
                                + DAT_GameCore::instance.mapU2MiddleBytes[0]
                            == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0xb,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 10)), OpenSHC::Text::TTA_CENTER, 0x7f7f7f, 0x11, FALSE);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        color = 0xc2f0eb;
                    } else {
                        color = 0xccfaff;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, param_1,
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 10)), OpenSHC::Text::TTA_CENTER, color, 0x11, FALSE);
                }
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, param_1,
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 10)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x11, FALSE);
            }
        }

    }
}
}
