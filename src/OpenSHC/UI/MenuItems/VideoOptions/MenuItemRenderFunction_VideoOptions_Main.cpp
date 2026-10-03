#include "../VideoOptions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
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
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492170
        void VideoOptions::MenuItemRenderFunction_VideoOptions_Main(int param_1, ...)
        {
            int iVar1;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 < -9) {
                iVar1 = 0;
                if (param_1 == -10) {
                    if (DAT_MenuTextInputState::instance.menuCursorType == 2) {
                        iVar1 = 2;
                    }
                    iVar1 = iVar1 + 0xb6;
                } else {
                    if (param_1 != -0x14) {}
                    if (DAT_MenuTextInputState::instance.menuCursorType == 1) {
                        iVar1 = 2;
                    }
                    iVar1 = iVar1 + 0xb7;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar1,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
            }
            if (param_1 < 0) {
                if (param_1 == -3) {
                    if (DAT_MenuTextInputState::instance.menuScrollSpeedSetting == 0) {
                        param_1 = 0x14;
                    } else if (DAT_MenuTextInputState::instance.menuScrollSpeedSetting == 1) {
                        param_1 = 0x15;
                    } else {
                        if (DAT_MenuTextInputState::instance.menuScrollSpeedSetting != 2) {}
                        param_1 = 0x13;
                    }
                } else {
                    if (param_1 != -2) {
                        if (param_1 != -1) {}
                        switch (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution) {
                        case 1:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("800x600",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 2:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1024x768",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 3:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1280x720",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 4:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1280x1024",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 5:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1366x768",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 6:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1440x900",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 7:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1600x900",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 8:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1600x1200",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 9:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1680x1050",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 10:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1920x1080",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 0xb:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1920x1200",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 0xc:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("2560x1440",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 0xd:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("2560x1600",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 0xe:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1360x768",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        case 0xf:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                DAT_TextManagerObject::ptr)("1024x600",
                                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12,
                                FALSE, 0);
                            return;
                        default:
                            break;
                        }
                    }
                    if (DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01 == 0) {
                        param_1 = 0xe;
                    } else {
                        if (DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01 != 1) {}
                        param_1 = 0xd;
                    }
                }
                yParam = DAT_ButtonY::instance + 7;
                iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                iVar1 = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance + 7;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color = 0xc2f0eb;
                    goto LAB_00492602;
                }
            }
            color = 0xccfaff;
        LAB_00492602:
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1),
                iVar1, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
