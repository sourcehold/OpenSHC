#include "../VideoOptions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/CursorType.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"
#include "OpenSHC/string-literals.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00492170
        void VideoOptions::MenuItemRenderFunction_VideoOptions_Main(int button, ...)
        {
            if (button <= -10) {
                // 0 or 2 first, then the base added, as the original computes the icon
                int icon = 0;
                if (button == -10) {
                    if (DAT_MenuTextInputState::instance.menuCursorType == OpenSHC::UI::Enums::CT_WINDOWS_LIKE_CURSOR) {
                        icon = 2;
                    }
                    icon += 182;
                } else {
                    if (button != -20) {
                        return;
                    }
                    if (DAT_MenuTextInputState::instance.menuCursorType == OpenSHC::UI::Enums::CT_ANI_CURSOR) {
                        icon = 2;
                    }
                    icon += 183;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, icon, DAT_ButtonX::instance, DAT_ButtonY::instance);
                return;
            }
            if (button >= 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // each path reads its own text position, y first, for the original's merged call
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    return;
                }
                int const textY = DAT_ButtonY::instance + 7;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                return;
            }
            int textID;
            // the negated tests keep the -3 and -2 bodies last, as the original lays them out
            if (button != -3) {
                if (button != -2) {
                    if (button != -1) {
                        return;
                    }
                    // the cases in the original's block order
                    switch (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution) {
                    case OpenSHC::Rendering::SRE_800x600:
                        // "800x600"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_800x600_005a7598,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1024x600:
                        // "1024x600"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1024x600_005a758c,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1024x768:
                        // "1024x768"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1024x768_005a7580,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1280x1024:
                        // "1280x1024"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1280x1024_005a7574,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1600x1200:
                        // "1600x1200"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1600x1200_005a7568,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1280x720:
                        // "1280x720"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1280x720_005a755c,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1440x900:
                        // "1440x900"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1440x900_005a7550,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1920x1080:
                        // "1920x1080"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1920x1080_005a7544,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1920x1200:
                        // "1920x1200"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1920x1200_005a7538,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_2560x1440:
                        // "2560x1440"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_2560x1440_005a752c,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_2560x1600:
                        // "2560x1600"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_2560x1600_005a7520,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1366x768:
                        // "1366x768"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1366x768_005a7514,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1360x768:
                        // "1360x768"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1360x768_005a7508,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1680x1050:
                        // "1680x1050"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1680x1050_005a74fc,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case OpenSHC::Rendering::SRE_1600x900:
                        // "1600x900"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_1600x900_005a74f0,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    default:
                        return;
                    }
                }
                // the zoom flag's cases, 1 first, as the original tests them
                switch (DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01) {
                case 1:
                    // "On"
                    textID = 13;
                    break;
                case 0:
                    // "Off"
                    textID = 14;
                    break;
                default:
                    return;
                }
            } else {
                // the scroll speed's cases in the reverse of the original's test order
                switch (DAT_MenuTextInputState::instance.menuScrollSpeedSetting) {
                case OpenSHC::UI::SS_SLOW:
                    // "Slow"
                    textID = 19;
                    break;
                case OpenSHC::UI::SS_FAST:
                    // "Fast"
                    textID = 21;
                    break;
                case OpenSHC::UI::SS_NORMAL:
                    // "Normal"
                    textID = 20;
                    break;
                default:
                    return;
                }
            }
            int const textY = DAT_ButtonY::instance + 7;
            int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, textID),
                textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
        }

    }
}
}
