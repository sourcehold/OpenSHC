#include "../OptionsMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491840
        void OptionsMenu::MenuItemRenderFunction_OptionsMenu_Buttons(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 == 2) {
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAIN_MENU) {
                LAB_004918a4:
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 0)
                            goto LAB_0049192c;
                    } else {
                    LAB_0049194d:
                        if (param_1 == 2) {
                            if (DAT_GameSynchronyState::instance.currentGameMode
                                == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            LAB_00491978:
                                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                                    goto LAB_00491982;
                                goto LAB_0049198b;
                            }
                        } else if ((param_1 != 0x27)
                            && ((param_1 != 3 || (DAT_GameSynchronyState::instance.isHost != FALSE))))
                            goto LAB_00491978;
                    }
                LAB_004918c8:
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    blendStrength = 0;
                    yParam = DAT_ButtonY::instance + 7;
                    xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    color = 0x7f7f7f;
                    goto LAB_00491904;
                }
            } else {
                if (param_1 == 3)
                    goto LAB_004918a4;
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    goto LAB_0049194d;
            LAB_0049192c:
                if (((param_1 != 0x27) || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION))
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1))
                    goto LAB_00491978;
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
                    || (DAT_MapPropertiesState::instance.scenarionMissionType == 0))
                    goto LAB_004918c8;
            LAB_00491982:
                if ((DAT_GameCore::instance.field24_0x6c != 0)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)) {
                LAB_0049198b:
                    if (((param_1 == 2) || (param_1 == 0x27)) || (param_1 == 3))
                        goto LAB_004918c8;
                }
                if (((((param_1 == 0x2c) && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION))
                         && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1))
                        && ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk
                            || (DAT_GameCore::instance.field24_0x6c != 0))))
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                        AlphaAndButtonSurfaceObj::ptr)(0);
                    /*
                      added by script: "Restart Mission"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x2c,
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, 0x7f7f7f, 0x12, FALSE);
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            yParam = DAT_ButtonY::instance + 7;
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                blendStrength = 4;
                color = 0xc2f0eb;
            } else {
                blendStrength = 2;
                color = 0xccfaff;
            }
        LAB_00491904:
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1),
                xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
