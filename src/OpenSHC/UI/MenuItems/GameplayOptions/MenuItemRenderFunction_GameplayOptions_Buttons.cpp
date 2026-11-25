#include "../GameplayOptions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00491EB0
        void GameplayOptions::MenuItemRenderFunction_GameplayOptions_Buttons(int button, ...)
        {
            if (button >= 0) {
                if (button == 15) {
                    // "Game Speed" is a label, never drawn hovered
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    // y before x: that schedules the + 7 as the original does (x first: quick_diff 0.9451 -> 0.9341)
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    return;
                }
                // one call per path, which MSVC merges (one call with colour locals: 100.0% -> 58.6%)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB,
                        OpenSHC::Rendering::Colors::COL_003E66, 18, FALSE, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                int const textY = DAT_ButtonY::instance + 7;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                    OpenSHC::Rendering::Colors::COL_000000, 18, FALSE, 0);
                return;
            }
            // -1 "Bubble Help" and -2 "Extreme Scoring" (pendingUnusedOption1) show their setting: 13 "On" or 14 "Off"
            int textIndex;
            switch (button) {
            case -1:
                // a switch (an if chain: quick_diff 0.9451 -> 0.8901)
                switch (DAT_MenuTextInputState::instance.pendingSettingBubbleHelp) {
                case 1:
                    textIndex = 13;
                    break;
                case 0:
                    textIndex = 14;
                    break;
                default:
                    // a value other than 0 or 1 shows nothing
                    return;
                }
                break;
            case -2:
                if (DAT_MenuTextInputState::instance.pendingUnusedOption1) {
                    textIndex = 13;
                } else {
                    textIndex = 14;
                }
                break;
            default:
                // other negative buttons draw nothing
                return;
            }
            int const textY = DAT_ButtonY::instance + 7;
            int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, textIndex),
                textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB,
                OpenSHC::Rendering::Colors::COL_000000, 18, FALSE, 0);
        }

    }
}
}
