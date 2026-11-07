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
        void ScenarioDescription::MenuItemRenderFunction_ScenarioDescription_Main(int param_1, ...)
        {
            bool bVar1;
            uint uVar2;
            DAT_ButtonUnknownZero::instance = 1;
            DAT_StopHandlingMenuItems::instance = 0;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk && param_1 != 10 && param_1 != 12
                && param_1 != 13 && param_1 != -3 && param_1 != -4 && param_1 != -1) {
                DAT_StopHandlingMenuItems::instance = 0;
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            if ((INT_00ed27bc::instance == 1) && (param_1 != 12)) {
                DAT_StopHandlingMenuItems::instance = 0;
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            if (param_1 == -1) {
                if ((DAT_00ed2798::instance) && (DAT_00ed2798::instance != 1)) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    if (DAT_GameCore::instance.missionNumber1to20 < 4) {
                        return;
                    }
                } else if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.mapU4Int1) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                DAT_ButtonUnknownZero::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    uVar2 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                } else {
                    uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, 24, (int)(DAT_ButtonX::instance + 10),
                    (int)(DAT_ButtonY::instance + 8), OpenSHC::Text::TTA_LEFT, uVar2, 18, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, DAT_GameState::instance.mapAndTime.difficulty + 19,
                    (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_00FF00, 18, FALSE);
                return;
            }
            if (param_1 == -2) {
                if (DAT_00ed2798::instance) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_ARRAY_00ed26d0::instance[0].y == 0) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (INT_00ed27bc::instance) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    uVar2 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                } else {
                    uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MISSION_BUTTONS, 10,
                    (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                    OpenSHC::Text::TTA_CENTER, uVar2, 18, FALSE);
                return;
            }
            if (param_1 == -3) {
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.gameSuspended != 1) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    uVar2 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                } else {
                    uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MISSION_BUTTONS, 11,
                    (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                    OpenSHC::Text::TTA_CENTER, uVar2, 18, FALSE);
                return;
            }
            if (param_1 == -4) {
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (INT_00ed27c4::instance < 2) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    uVar2 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                } else {
                    uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 10, (int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 8), OpenSHC::Text::TTA_CENTER, uVar2, 18, FALSE);
                return;
            }
            if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1))
                && INT_00ed27bc::instance != 1) {
                if (param_1 == 12) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
            LAB_004d8543:
                if (param_1 == 13) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1)
                    goto LAB_004d8563;
                if (param_1 == 12) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                bVar1 = param_1 == 13;
            } else {
                if (param_1 == 11) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
                    || (DAT_GameCore::instance.gameSuspended != 1))
                    goto LAB_004d8543;
                bVar1 = param_1 == 12;
            }
            if (bVar1) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            }
        LAB_004d8563:
            DAT_ButtonUnknownZero::instance = 0;
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
