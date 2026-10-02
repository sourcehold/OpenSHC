#include "../SoundOptions.func.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x00492690
        void SoundOptions::MenuItemRenderFunction_SoundOptions_Buttons(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            eTextSections offsetIndex;
            int iVar1;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 == -10) {
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    color = 0xc2f0eb;
                    yParam = DAT_ButtonY::instance + 7;
                    xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    iVar1 = 0xc;
                    offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    color = 0xccfaff;
                    yParam = DAT_ButtonY::instance + 7;
                    xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    iVar1 = 0xc;
                    offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC;
                }
            } else {
                if ((param_1 < -1) && (param_1 != -5)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                }
                if (-1 < param_1) {
                    if (param_1 - 0x23U < 3) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE);
                    }
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1,
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE);
                }
                iVar1 = DAT_MenuTextInputState::instance.DAT_GenieVoiceActiveMenuVar;
                if ((param_1 != -5)
                    && (iVar1 = DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar, param_1 != -1)) {}
                if (iVar1 == 0) {
                    iVar1 = 0xe;
                } else {
                    if (iVar1 != 1) {}
                    iVar1 = 0xd;
                }
                color = 0xccfaff;
                yParam = DAT_ButtonY::instance + 7;
                xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS;
            }
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(offsetIndex, iVar1), xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
