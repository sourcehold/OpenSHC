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
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
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

        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00427810
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...)
        {
            int iVar3;
            int iVar4;
            int iVar6;
            BOOLEnum BVar2 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar2) {
                return;
            }
            if (param_1 == 0) {
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                iVar4 = (iVar3 / 32) + 32;
                BVar2 = FALSE;
                int iVar10 = 19;
                BGR24 BVar9 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                TextAlignment TVar7 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_ButtonX::instance;
                iVar6 = DAT_ButtonY::instance;
                // added by script: "Players"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 28),
                    iVar3, iVar6, TVar7, BVar9, iVar10, BVar2, iVar4);
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    iVar6 = (iVar3 / 32) + 32;
                    BVar2 = FALSE;
                    iVar10 = 19;
                    BVar9 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                    TVar7 = OpenSHC::Text::TTA_CENTER;
                    iVar4 = DAT_ButtonX::instance + 335;
                    iVar3 = DAT_ButtonY::instance;
                    // added by script: "Status"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 29),
                        iVar4, iVar3, TVar7, BVar9, iVar10, BVar2, iVar6);
                }
                if (!DAT_GameSynchronyState::instance.isHost) {
                    return;
                }
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                iVar6 = (iVar3 / 32) + 32;
                BVar2 = FALSE;
                iVar10 = 19;
                BVar9 = OpenSHC::Rendering::Colors::COL_C2F0EB;
                TVar7 = OpenSHC::Text::TTA_CENTER;
                iVar4 = DAT_ButtonX::instance + 370;
                iVar3 = DAT_ButtonY::instance;
                // added by script: "Eject"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 91),
                    iVar4, iVar3, TVar7, BVar9, iVar10, BVar2, iVar6);
            }
            if (10 < param_1) {
                iVar3
                    = (int)*(char*)((int)DAT_GameSynchronyState::instance.mapSendRequestStatePerPlayer + param_1 + 26);
                DAT_ButtonUnknownZero::instance = 1;
                if (iVar3 < 1) {
                    return;
                }
                byte bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3];
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if ('\0' < (char)bVar1) {
                    if ((bVar1 == 1) || (bVar1 == 3)) {
                        iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 28;
                        while (iVar6 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350) {
                            iVar4 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 22;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 204,
                                iVar6, (int)(DAT_ButtonY::instance), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 72,
                                (iVar4 / 32) + 32);
                            iVar6 += 20;
                        }
                    } else {
                        iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 28;
                        while (iVar6 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350) {
                            iVar4 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 22;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 205,
                                iVar6, (int)(DAT_ButtonY::instance), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 72,
                                (iVar4 / 32) + 32);
                            iVar6 += 20;
                        }
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE
                    && 27
                        < DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        < 350
                    && (int)DAT_ButtonY::instance <= DAT_MouseState::instance.screenSpaceY
                    && DAT_MouseState::instance.screenSpaceY < (int)DAT_ButtonY::instance + 20) {
                    if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        iVar6 = 403;
                    } else if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                        iVar6 = 405;
                    } else {
                        iVar6 = 404;
                    }
                    // added by script: "Computer Opponent"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar6,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 135,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 192, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, FALSE);
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3]) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                            (int)((char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3] + 405),
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 145,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 192, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, TRUE);
                    }
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 402,
                            (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance + 5), 60,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 19, (iVar6 / 32) + 32);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 402,
                            (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance + 5), 60,
                            OpenSHC::Rendering::Colors::COL_7CAAAF, 19, (iVar6 / 32) + 32);
                    }
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == OpenSHC::AI::AITA_NULL) {
                    return;
                }
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)(DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 9 + 230),
                    (int)(DAT_ButtonX::instance + 10), (int)(DAT_ButtonY::instance + 5), 70,
                    OpenSHC::Rendering::Colors::COL_7CAAAF, 19, (iVar6 / 32) + 32);
                return;
            }
            if (0 < param_1) {
                iVar3 = (int)(char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[param_1];
                DAT_ButtonUnknownZero::instance = 1;
                if (iVar3 < 1) {
                    return;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && (iVar3 == DAT_GameSynchronyState::instance.DAT_HostPlayerSlotID
                        || ((DAT_GameSynchronyState::instance.isHost
                            && (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID))))) {
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 138,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 36, (int)(DAT_ButtonY::instance - 2),
                        (iVar6 / 32) + 32);
                }
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar3 + 469,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30, (int)(DAT_ButtonY::instance),
                    (iVar6 / 32) + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                    if (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == OpenSHC::AI::AITA_NULL) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                        (int)(DAT_GameSynchronyState::instance.aiVariationArray[iVar3] + 231
                            + DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 9),
                        (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 5), 280,
                        OpenSHC::Rendering::Colors::COL_7CAAAF, 19, (iVar6 / 32) + 32);
                }
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                DAT_TextManagerObject::instance.field_0x30 = 1;
                if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                        DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[iVar3],
                        (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 5), 280,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 19, (iVar6 / 32) + 32);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                        DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[iVar3],
                        (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 5), 280,
                        OpenSHC::Rendering::Colors::COL_7CAAAF, 19, (iVar6 / 32) + 32);
                }
            }
            if (-10 < param_1) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    return;
                }
                iVar3 = (int)*(char*)((int)DAT_GameSynchronyState::ptr + (1089092 - param_1));
                DAT_ButtonUnknownZero::instance = 0;
                if (iVar3 < 1) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    if (iVar3 != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                    DAT_CurrentButtonGmDataIndex::instance
                        = 207 - (uint)(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[iVar3] != 0);
                    iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        (iVar3 / 32) + 32);
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == OpenSHC::AI::AITA_NULL) {
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                DAT_CurrentButtonGmDataIndex::instance = 627;
                switch (DAT_GameSynchronyState::instance.currentAIArray[iVar3]) {
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
                    DAT_CurrentButtonGmDataIndex::instance = 626;
                }
                DAT_ButtonX::instance -= 6;
                DAT_ButtonY::instance -= 3;
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (iVar3 / 32) + 32);
            }
            if (param_1 < -199) {
                DAT_ButtonUnknownZero::instance = 0;
                if (!DAT_GameSynchronyState::instance.isHost) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                iVar3 = (int)*(char*)((int)DAT_GameSynchronyState::ptr + (1088892 - param_1));
                if (iVar3 < 1) {
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                    if (DAT_GameSynchronyState::instance.slotActionPending[iVar3] != 0) {
                        DAT_ButtonUnknownZero::instance = 0;
                        return;
                    }
                    iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        (iVar3 / 32) + 32);
                }
                if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                BVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(iVar3);
                if (!BVar2) {
                    return;
                }
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (iVar3 / 32) + 32);
            }
            if (param_1 == -101) {
                DAT_ButtonUnknownZero::instance = 1;
                if ((DAT_GameSynchronyState::instance.isHost)
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                    for (int iVar3 = 1; iVar3 < countof(DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray);
                        ++iVar3) {
                        if ((char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[iVar3] < '\x01')
                            goto LAB_00427f46;
                    }
                }
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            } else {
                if (param_1 == -102) {
                    if (!DAT_GameSynchronyState::instance.isHost) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE
                        && DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                        && DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)
                        goto LAB_00427f4c;
                } else {
                    if (param_1 != -103)
                        goto LAB_00427f4c;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                }
            LAB_00427f46:
                DAT_ButtonUnknownZero::instance = 0;
            }
        LAB_00427f4c:
            if (!DAT_GameSynchronyState::instance.isHost) {
                return;
            }
            iVar3 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)((iVar3 / 32) + 32);
        }

    }
}
}
