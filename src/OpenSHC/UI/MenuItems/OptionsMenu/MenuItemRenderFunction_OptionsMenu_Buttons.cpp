#include "../OptionsMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00491840
        void OptionsMenu::MenuItemRenderFunction_OptionsMenu_Buttons(int button, ...)
        {
            // "Load" from the main menu skips the tests: it is always drawn enabled
            if (!(button == 2 && DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAIN_MENU)) {
                // greyed by the player's death, the game mode, or not being the host
                if (((button == 2 || button == 3)
                        && DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                        && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            != 0)
                    // a ?: on the game mode: written as two tests the mode is read twice, which loses the match
                    || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                            ? (button == 39
                                  && !(DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                                      || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                                      || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                                          && DAT_MapPropertiesState::instance.scenarionMissionType != 0)))
                            : ((button == 2
                                   && DAT_GameSynchronyState::instance.currentGameMode
                                       != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                                  || button == 39 || (button == 3 && !DAT_GameSynchronyState::instance.isHost)))
                    || ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                            || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
                            || DAT_GameCore::instance.field_0x6c != 0
                            || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                        && (button == 2 || button == 39 || button == 3))) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F, 18, FALSE, 0);
                    return;
                }
                // "Restart Mission", for campaign missions, plain scenarios and skirmishes
                if (button == 44
                    && !(DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                            && DAT_GameCore::instance.field_0x6c == 0)
                        || DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                        AlphaAndButtonSurfaceObj::ptr)(0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 44, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F,
                        18, FALSE);
                    return;
                }
            }
            // enabled
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            int const textY = DAT_ButtonY::instance + 7;
            int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 4);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, button),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 2);
            }
        }

    }
}
}
