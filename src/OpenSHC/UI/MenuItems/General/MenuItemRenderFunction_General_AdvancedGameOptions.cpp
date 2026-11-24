#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00428AC0
        void General::MenuItemRenderFunction_General_AdvancedGameOptions(int button, ...)
        {
            // nothing behind the map dialogs, the round table or the lord choices; skirmish options: only their items
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_LOAD_MAP
                || DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_SEND_MAP_TO
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == OpenSHC::UI::Enums::MMT_SKIRMISH_PLAY_OPTIONS) {
                if (button != -1000 && button != -10 && button != -11 && button != -12 && button != -13 && button != -14
                    && button != 99 && button != 100 && button != 83 && button != 109 && button != 82 && button != 94) {
                    return;
                }
            } else if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && (button == 93 || button == 31)) {
                return;
            }
            if (button == 103) {
                DAT_ButtonUnknownZero::instance = FALSE;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            }
            if (!DAT_GameSynchronyState::instance.isHost) {
                if (button == 103) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (button == 93) {
                    return;
                }
            }
            if (button == -1) {
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            // not set for 103, whose button another function draws (a first value loses the match)
            uint color;
            if (button != 103) {
                // the colour before the call here and after it below (the other way, the match is lost)
                if (DAT_ButtonCurrentlyInteracting::instance && DAT_GameSynchronyState::instance.isHost) {
                    color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                        AlphaAndButtonSurfaceObj::ptr)(DAT_ButtonBackgroundBlendStrength::instance);
                    color = OpenSHC::Rendering::Colors::COL_C2F0EB;
                }
            }
            // one block per item, in the original's order (another order loses the match)
            if (button == 31) {
                // before the first call (computed in the call, the match is lost)
                int const levelText = DAT_GameSynchronyState::instance.skirmishTechLevel / 2 + 79;
                // the alpha written the long way round at every call, as the original computes it
                // "Tech Level"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 85, DAT_ButtonX::instance + 20,
                    DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                // "Early", "Middle" or "Late" (79 to 81)
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, levelText,
                    DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 36) {
                // "Win: Regicide" (36), "Win: 10000 Gold" (37), "Win: 3" to "Win: 10" (38 to 45)
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.skirmishWinCondition + 36,
                    DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_CENTER, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 83) {
                // "Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 86, DAT_ButtonX::instance + 20,
                    DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                // the parameter becomes the value's text number, 83 or 84 (a variable of its own loses the match)
                if (DAT_GameSynchronyState::instance.skirmishTroopsCostGold) {
                    button = 84;
                }
                // "Free" (83) or "Cost Gold" (84)
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button,
                    DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 109) {
                // "Fog Of War"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 109, DAT_ButtonX::instance + 20,
                    DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                // the number in a local and one call (a call in each arm loses the match)
                int fogText;
                // "Off" (95), "Fog Of War" (109) or "Reveal Map" (110)
                if (DAT_GameState::instance.mapAndTime.skirmishFogOfWar == 0) {
                    fogText = 95;
                } else if (DAT_GameState::instance.mapAndTime.skirmishFogOfWar == 1) {
                    fogText = 109;
                } else {
                    fogText = 110;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, fogText,
                    DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == -1000) {
                // "Back"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 17, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_CENTER, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 103) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            // the alpha written out in every call (one local for the items from here on loses the match)
            if (button == -10) {
                // "No Cow Throwing"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 5, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                // 206 when the option is on, 208 when it is off
                // a call in each arm (one call with a conditional expression loses the match)
                if (DAT_GameSynchronyState::instance.skirmishNoCowThrowing) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 206,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 208,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (button == -11) {
                // "No Dogs"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 6, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameSynchronyState::instance.skirmishNoDogs) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 206,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 208,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (button == -13) {
                // "Extreme Mode"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 13, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameSynchronyState::instance.skirmishExtremeMode) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 206,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 208,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (button == -14) {
                // "Extreme Powers Around Lord"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 14, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameSynchronyState::instance.skirmishExtremeMode2
                    && DAT_GameSynchronyState::instance.skirmishExtremeMode) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 206,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 208,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (button == 99) {
                // "Strong Walls"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 99, DAT_ButtonX::instance + 20,
                    DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameSynchronyState::instance.skirmishStrongWalls) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 206,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 208,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 50, DAT_ButtonY::instance);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (button == -12) {
                // "No Rush"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                // each value its own if (an else-if chain loses the match)
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 0) {
                    // "Off"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 95,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 1) {
                    // "5 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 96,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 2) {
                    // "10 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 97,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 3) {
                    // "20 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 98,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 4) {
                    // "30 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 8, DAT_ButtonW::instance + DAT_ButtonX::instance - 20,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0,
                        18, FALSE, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 5) {
                    // "1 hour"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 9, DAT_ButtonW::instance + DAT_ButtonX::instance - 20,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0,
                        18, FALSE, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                return;
            }
            // the other items: their own text, "Gold" (14), "Popularity" (15), "Game Speed" (82),
            // "Connection options" (93), "Auto save game" (94) or "Alliances" (100), and for some a value
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, button, DAT_ButtonX::instance + 20,
                DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            if (button == 14) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.skirmishStartGold,
                    DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 15) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.skirmishDefaultPopularity,
                    DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 82) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.skirmishGameSpeedLevel,
                    DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (button == 94) {
                // each value its own if, as above
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 0) {
                    // "Off"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 95,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                    // "5 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 96,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                    // "10 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 97,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 20) {
                    // "20 minutes"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 98,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                return;
            }
            if (button == 100) {
                // a truth test (== 0 with the arms swapped loses the match)
                if (DAT_GameSynchronyState::instance.skirmishAlliances) {
                    // "Start Only"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 102,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                } else {
                    // "Anytime"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 101,
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 20, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
            }
        }

    }
}
}
