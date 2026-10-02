#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00427810
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons(int param_1, ...)
        {
            byte bVar1;
            BOOLEnum BVar2;
            int iVar3;
            int iVar4;
            char* pcVar5;
            int iVar6;
            TextAlignment TVar7;
            uint uVar8;
            BGR24 BVar9;
            int iVar10;
            BVar2 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar2 != FALSE) {}
            if (param_1 == 0) {
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar4 = ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                BVar2 = FALSE;
                iVar10 = 0x13;
                BVar9 = 0xc2f0eb;
                TVar7 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_ButtonX::instance;
                iVar6 = DAT_ButtonY::instance;
                /*
                  added by script: "Players"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x1c),
                    iVar3, iVar6, TVar7, BVar9, iVar10, BVar2, iVar4);
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    iVar6 = ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                    BVar2 = FALSE;
                    iVar10 = 0x13;
                    BVar9 = 0xc2f0eb;
                    TVar7 = OpenSHC::Text::TTA_CENTER;
                    iVar4 = DAT_ButtonX::instance + 0x14f;
                    iVar3 = DAT_ButtonY::instance;
                    /*
                      added by script: "Status"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x1d),
                        iVar4, iVar3, TVar7, BVar9, iVar10, BVar2, iVar6);
                }
                if (DAT_GameSynchronyState::instance.isHost == FALSE) {}
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar6 = ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                BVar2 = FALSE;
                iVar10 = 0x13;
                BVar9 = 0xc2f0eb;
                TVar7 = OpenSHC::Text::TTA_CENTER;
                iVar4 = DAT_ButtonX::instance + 0x172;
                iVar3 = DAT_ButtonY::instance;
                /*
                  added by script: "Eject"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5b),
                    iVar4, iVar3, TVar7, BVar9, iVar10, BVar2, iVar6);
            }
            if (10 < param_1) {
                iVar3 = (int)*(char*)((int)DAT_GameSynchronyState::instance.field290_0x109e20 + param_1 + 0x1a);
                DAT_ButtonUnknownZero::instance = 1;
                if (iVar3 <= 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3];
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if ('\0' < (char)bVar1) {
                    if ((bVar1 == 1) || (bVar1 == 3)) {
                        iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1c;
                        if (iVar6 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e) {
                            do {
                                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x16;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    0xcc, iVar6, (int)((int)(DAT_ButtonY::instance)),
                                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x48,
                                    ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                                iVar6 = iVar6 + 0x14;
                            } while (iVar6 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e);
                        }
                    } else {
                        iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1c;
                        if (iVar6 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e) {
                            do {
                                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x16;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    0xcd, iVar6, (int)((int)(DAT_ButtonY::instance)),
                                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x48,
                                    ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                                iVar6 = iVar6 + 0x14;
                            } while (iVar6 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e);
                        }
                    }
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if ((((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)
                         && (0x1b < DAT_MouseState::instance.screenSpaceX
                                 - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth))
                        && (DAT_MouseState::instance.screenSpaceX
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                            < 0x15e))
                    && ((DAT_ButtonY::instance <= DAT_MouseState::instance.screenSpaceY
                        && (DAT_MouseState::instance.screenSpaceY < DAT_ButtonY::instance + 0x14)))) {
                    if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        iVar6 = 0x193;
                    } else if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                        iVar6 = 0x195;
                    } else {
                        iVar6 = 0x194;
                    }
                    /*
                      added by script: "Computer Opponent"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar6,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x87,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xc0, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x12, FALSE);
                    if ('\0' < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3]) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                            (int)((int)((char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3] + 0x195)),
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x91,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xc0, OpenSHC::Text::TTA_LEFT,
                            0xccfaff, 0, 0x12, TRUE);
                    }
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        uVar8 = 0xc2f0eb;
                    } else {
                        uVar8 = 0x7caaaf;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x192,
                        (int)((int)(DAT_ButtonX::instance + 10)), (int)((int)(DAT_ButtonY::instance + 5)), 0x3c, uVar8,
                        0x13, ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == 0) {}
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)((int)(DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 9 + 0xe6)),
                    (int)((int)(DAT_ButtonX::instance + 10)), (int)((int)(DAT_ButtonY::instance + 5)), 0x46, 0x7caaaf,
                    0x13, ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (0 < param_1) {
                iVar3 = (int)(char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[param_1];
                DAT_ButtonUnknownZero::instance = 1;
                if (iVar3 <= 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                    && ((iVar3 == DAT_GameSynchronyState::instance.DAT_HostPlayerSlotID
                        || ((DAT_GameSynchronyState::instance.isHost != FALSE
                            && (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID)))))) {
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x8a,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x24,
                        (int)((int)(DAT_ButtonY::instance + -2)), ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar3 + 0x1d5,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e, (int)((int)(DAT_ButtonY::instance)),
                    ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                    if (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == 0) {
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText4Unk,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                        (int)((int)(DAT_GameSynchronyState::instance.aiVariationArray[iVar3] + 0xe7
                            + DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 9)),
                        (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 5)), 0x118,
                        0x7caaaf, 0x13, ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                DAT_TextManagerObject::instance.field12_0x30 = 1;
                if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    uVar8 = 0xc2f0eb;
                } else {
                    uVar8 = 0x7caaaf;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.DAT_PlayerNames[iVar3], (int)((int)(DAT_ButtonX::instance + 0x14)),
                    (int)((int)(DAT_ButtonY::instance + 5)), 0x118, uVar8, 0x13,
                    ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (-10 < param_1) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {}
                iVar3 = (int)*(char*)((int)DAT_GameSynchronyState::ptr + (0x109e44 - param_1));
                DAT_ButtonUnknownZero::instance = 0;
                if (iVar3 < 1) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    if (iVar3 != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                    DAT_CurrentButtonGmDataIndex::instance
                        = 0xcf - (uint)(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[iVar3] != 0);
                    iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                if (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == 0) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
                DAT_CurrentButtonGmDataIndex::instance = 0x273;
                switch (DAT_GameSynchronyState::instance.currentAIArray[iVar3]) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 8:
                case 9:
                case 10:
                case 0xe:
                case 0xf:
                case 0x10:
                    DAT_CurrentButtonGmDataIndex::instance = 626;
                }
                DAT_ButtonX::instance = DAT_ButtonX::instance + -6;
                DAT_ButtonY::instance = DAT_ButtonY::instance + -3;
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 < -199) {
                DAT_ButtonUnknownZero::instance = 0;
                if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                iVar3 = (int)*(char*)((int)DAT_GameSynchronyState::ptr + (0x109d7c - param_1));
                if (iVar3 < 1) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                    if (DAT_GameSynchronyState::instance.field294_0x109e5f[iVar3] != 0) {
                        DAT_ButtonUnknownZero::instance = 0;
                    }
                    iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                }
                if (iVar3 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                BVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(iVar3);
                if (BVar2 == FALSE) {}
                iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 == -0x65) {
                DAT_ButtonUnknownZero::instance = 1;
                if ((DAT_GameSynchronyState::instance.isHost != FALSE)
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                    iVar3 = 1;
                    do {
                        if ((char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[iVar3] < '\x01')
                            goto LAB_00427f46;
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < 9);
                }
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            } else {
                if (param_1 == -0x66) {
                    DAT_ButtonUnknownZero::instance = 1;
                    if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                    if (((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE)
                            && (DAT_MenuModalComposition1::instance.activeModalDialogID
                                != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                        && (DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT))
                        goto LAB_00427f4c;
                } else {
                    if (param_1 != -0x67)
                        goto LAB_00427f4c;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                }
            LAB_00427f46:
                DAT_ButtonUnknownZero::instance = 0;
            }
        LAB_00427f4c:
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {}
            iVar3 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
        }

    }
}
}
