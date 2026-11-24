#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/GmDataIndex.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00427810
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons(int button, ...)
        {
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            // 0: the list's three headings
            if (button == 0) {
                // the fade written the long way round at every call, as the original computes it
                // "Players"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 28),
                    DAT_ButtonX::instance, DAT_ButtonY::instance, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    // a local for x (with x written in the call the match is lost)
                    int const statusX = DAT_ButtonX::instance + 335;
                    // "Status"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 29),
                        statusX, DAT_ButtonY::instance, OpenSHC::Text::TTA_CENTER,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if (!DAT_GameSynchronyState::instance.isHost) {
                    return;
                }
                // a local for x, as above
                int const ejectX = DAT_ButtonX::instance + 370;
                // "Eject"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 91),
                    ejectX, DAT_ButtonY::instance, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB,
                    19, FALSE, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            // above 10: the row of the seat that is at button - 10 in the round table's order
            if (button > 10) {
                int const slot = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[button - 10];
                DAT_ButtonUnknownZero::instance = TRUE;
                if (slot < 1) {
                    return;
                }
                int const group = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[slot];
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (group > 0) {
                    if (group == 1 || group == 3) {
                        for (int x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 28;
                            x < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350; x += 20) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 204, x,
                                DAT_ButtonY::instance, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 72,
                                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 22 / 32 + 32);
                        }
                    } else {
                        for (int x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 28;
                            x < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350; x += 20) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 205, x,
                                DAT_ButtonY::instance, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 72,
                                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 22 / 32 + 32);
                        }
                    }
                }
                // stored again, as the original does
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        >= 28
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        < 350
                    && DAT_MouseState::instance.screenSpaceY >= DAT_ButtonY::instance
                    && DAT_MouseState::instance.screenSpaceY < DAT_ButtonY::instance + 20) {
                    // a call in each arm (with the text's number in a local the match is lost)
                    if (slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        // "This is you!"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 403,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 135,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 192, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, FALSE);
                    } else if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                        // "Human Opponent"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 404,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 135,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 192, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, FALSE);
                    } else {
                        // "Computer Opponent"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 405,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 135,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 192, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, FALSE);
                    }
                    // read again after the call, as the original does (a local loses the match)
                    if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[slot] > 0) {
                        // "(In Team 1)" to "(In Team 4)"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[slot] + 405,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 145,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 192, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, TRUE);
                    }
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                    // a call in each arm (with the colour in a local the match is lost)
                    if (slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        // "Human"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 402,
                            DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 5, 60,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    } else {
                        // "Human"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 402,
                            DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 5, 60,
                            OpenSHC::Rendering::Colors::COL_7CAAAF, 19,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    }
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[slot] == OpenSHC::AI::AITA_NULL) {
                    return;
                }
                // the AI lord's kind, "Rat" (239) to "Abbot" (374)
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.currentAIArray[slot] * 9 + 230, DAT_ButtonX::instance + 10,
                    DAT_ButtonY::instance + 5, 70, OpenSHC::Rendering::Colors::COL_7CAAAF, 19,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            // 1 to 10: the seat that is at button in the round table's order
            if (button > 0) {
                int const slot = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[button];
                DAT_ButtonUnknownZero::instance = TRUE;
                if (slot < 1) {
                    return;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && (slot == DAT_GameSynchronyState::instance.DAT_HostPlayerSlotID
                        || (DAT_GameSynchronyState::instance.isHost
                            && slot == DAT_GameSynchronyState::instance.currentPlayerSlotID))) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 138,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 36, DAT_ButtonY::instance - 2,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, slot + 469,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, DAT_ButtonY::instance,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                    DAT_TextManagerObject::instance.field_0x30 = 1;
                    // a call in each arm (with the colour in a local the match is lost)
                    if (slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                            DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[slot],
                            DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 5, 280,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                            DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[slot],
                            DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 5, 280,
                            OpenSHC::Rendering::Colors::COL_7CAAAF, 19,
                            (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    }
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[slot] == OpenSHC::AI::AITA_NULL) {
                    return;
                }
                // the AI lord's own name, "Duc de Puce" for the first rat
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[slot] + 231
                        + DAT_GameSynchronyState::instance.currentAIArray[slot] * 9,
                    DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 5, 280, OpenSHC::Rendering::Colors::COL_7CAAAF,
                    19, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            // -1 to -9: the button of the seat at -button; nothing in a single player skirmish
            if (button > -10) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    return;
                }
                int const slot = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[-button];
                DAT_ButtonUnknownZero::instance = FALSE;
                if (slot < 1) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                    if (slot != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                    if (DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[slot] != 0) {
                        DAT_CurrentButtonGmDataIndex::instance
                            = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_206_PIC_260;
                    } else {
                        DAT_CurrentButtonGmDataIndex::instance
                            = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_207_PIC_262;
                    }
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[slot] == OpenSHC::AI::AITA_NULL) {
                    return;
                }
                // 626 for the European lords, 627 for the Arabian ones
                DAT_CurrentButtonGmDataIndex::instance = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_627_PIC_756;
                switch (DAT_GameSynchronyState::instance.currentAIArray[slot]) {
                case OpenSHC::AI::AITA_RAT:
                case OpenSHC::AI::AITA_SNAKE:
                case OpenSHC::AI::AITA_PIG:
                case OpenSHC::AI::AITA_WOLF:
                case OpenSHC::AI::AITA_RICHARD:
                case OpenSHC::AI::AITA_FREDERICK:
                case OpenSHC::AI::AITA_PHILIPP:
                case OpenSHC::AI::AITA_SHERIFF:
                case OpenSHC::AI::AITA_MARSHAL:
                case OpenSHC::AI::AITA_ABBOT:
                    DAT_CurrentButtonGmDataIndex::instance
                        = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_626_PIC_755;
                    break;
                }
                DAT_ButtonX::instance -= 6;
                DAT_ButtonY::instance -= 3;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            // -10 to -199: the buttons -101, -102 and -103; any other number here only draws the button for the host
            if (button > -200) {
                if (button == -101) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    BOOLEnum emptySeat = FALSE;
                    if (DAT_GameSynchronyState::instance.isHost
                        && DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                        for (int i = 1; i < countof(DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray); ++i) {
                            if (DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[i] < 1) {
                                emptySeat = TRUE;
                                break;
                            }
                        }
                    }
                    if (emptySeat) {
                        DAT_ButtonUnknownZero::instance = FALSE;
                    } else {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                } else if (button == -102) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    if (!DAT_GameSynchronyState::instance.isHost) {
                        return;
                    }
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE
                        || DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                        || DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                        DAT_ButtonUnknownZero::instance = FALSE;
                    }
                } else if (button == -103) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        return;
                    }
                    DAT_ButtonUnknownZero::instance = FALSE;
                }
                if (!DAT_GameSynchronyState::instance.isHost) {
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            // -200 and below: the seat at -button - 200; the non-host code stands last (first, the match is lost)
            DAT_ButtonUnknownZero::instance = FALSE;
            if (DAT_GameSynchronyState::instance.isHost) {
                int const slot = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[-button - 200];
                if (slot < 1) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                    if (slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        return;
                    }
                    if (DAT_GameSynchronyState::instance.slotActionPending[slot] != 0) {
                        return;
                    }
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                    return;
                }
                if (slot == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (!MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(slot)) {
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            DAT_ButtonUnknownZero::instance = TRUE;
        }

    }
}
}
