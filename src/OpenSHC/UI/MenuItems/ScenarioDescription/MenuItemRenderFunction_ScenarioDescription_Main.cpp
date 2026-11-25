#include "../ScenarioDescription.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_00ed2798.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/INT_00ed27bc.hpp"
#include "OpenSHC/Globals/INT_00ed27c4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8250
        void ScenarioDescription::MenuItemRenderFunction_ScenarioDescription_Main(int button, ...)
        {
            DAT_ButtonUnknownZero::instance = TRUE;
            DAT_StopHandlingMenuItems::instance = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk && button != 10 && button != 12
                && button != 13 && button != -3 && button != -4 && button != -1) {
                return;
            }
            if (INT_00ed27bc::instance == 1 && button != 12) {
                return;
            }
            // -1: the difficulty and its setting, in a campaign mission after the third or an economic one
            if (button == -1) {
                if (DAT_00ed2798::instance != 0 && DAT_00ed2798::instance != 1) {
                    return;
                }
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                        || DAT_GameCore::instance.missionNumber1to20 <= 3)
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                    return;
                }
                if (DAT_GameCore::instance.mapU4Int1) {
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    return;
                }
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                DAT_ButtonUnknownZero::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // a call for each colour: the original pushes the colour inside each arm
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24, DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, DAT_GameState::instance.mapAndTime.difficulty + 19,
                    DAT_ButtonX::instance + DAT_ButtonW::instance - 10, DAT_ButtonY::instance + 8,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_00FF00, 18, FALSE);
                return;
            }
            // -2 to -4: three text buttons
            if (button == -2) {
                if (DAT_00ed2798::instance) {
                    return;
                }
                if (DAT_ARRAY_00ed26d0::instance[0].y == 0) {
                    return;
                }
                if (INT_00ed27bc::instance) {
                    return;
                }
                DAT_ButtonUnknownZero::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MISSION_BUTTONS, 10, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                        DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                        18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MISSION_BUTTONS, 10, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                        DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB,
                        18, FALSE);
                }
                return;
            }
            if (button == -3) {
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                    return;
                }
                if (DAT_GameCore::instance.gameSuspended != 1) {
                    return;
                }
                DAT_ButtonUnknownZero::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MISSION_BUTTONS, 11, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                        DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                        18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MISSION_BUTTONS, 11, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                        DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB,
                        18, FALSE);
                }
                return;
            }
            if (button == -4) {
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                    return;
                }
                if (INT_00ed27c4::instance <= 1) {
                    return;
                }
                DAT_ButtonUnknownZero::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 10, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                        DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                        18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 10, DAT_ButtonX::instance + DAT_ButtonW::instance / 2,
                        DAT_ButtonY::instance + 8, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB,
                        18, FALSE);
                }
                return;
            }
            // the other buttons are drawn as they are, but for the ones the game mode hides
            if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)
                || INT_00ed27bc::instance == 1) {
                if (button == 11) {
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                    && DAT_GameCore::instance.gameSuspended == 1) {
                    if (button == 12) {
                        return;
                    }
                } else if (button == 13) {
                    return;
                }
            } else if (button == 12 || button == 13) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                && (button == 12 || button == 13)) {
                return;
            }
            DAT_ButtonUnknownZero::instance = FALSE;
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
