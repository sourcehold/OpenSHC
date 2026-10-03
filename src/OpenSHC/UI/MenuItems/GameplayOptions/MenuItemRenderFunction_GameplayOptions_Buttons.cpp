#include "../GameplayOptions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491EB0
        void GameplayOptions::MenuItemRenderFunction_GameplayOptions_Buttons(int param_1, ...)
        {
            int iVar1;
            char* pcVar2;
            int iVar3;
            TextAlignment TVar4;
            uint foregroundColor;
            BGR24 color;
            uint backgroundColor;
            int iVar5;
            BOOLEnum BVar6;
            int iVar7;
            if (param_1 < 0) {
                if (param_1 == -2) {
                    param_1 = 0xe - (uint)(DAT_MenuTextInputState::instance.field15_0x3c != '\0');
                } else {
                    if (param_1 != -1) {}
                    if (DAT_MenuTextInputState::instance.field14_0x38 == 0) {
                        param_1 = 0xe;
                    } else {
                        if (DAT_MenuTextInputState::instance.field14_0x38 != 1) {}
                        param_1 = 0xd;
                    }
                }
                backgroundColor = 0;
            } else {
                if (param_1 == 0xf) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    iVar7 = 0;
                    BVar6 = FALSE;
                    iVar5 = 0x12;
                    color = 0xccfaff;
                    TVar4 = OpenSHC::Text::TTA_CENTER;
                    iVar3 = DAT_ButtonY::instance + 7;
                    iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0xf),
                        iVar1, iVar3, TVar4, color, iVar5, BVar6, iVar7);
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    backgroundColor = 0;
                    foregroundColor = 0xccfaff;
                    goto LAB_00491f8b;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                backgroundColor = 0x3e66;
            }
            foregroundColor = 0xc2f0eb;
        LAB_00491f8b:
            iVar7 = 0;
            BVar6 = FALSE;
            iVar5 = 0x12;
            TVar4 = OpenSHC::Text::TTA_CENTER;
            iVar3 = DAT_ButtonY::instance + 7;
            iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1),
                iVar1, iVar3, TVar4, foregroundColor, backgroundColor, iVar5, BVar6, iVar7);
        }

    }
}
}
