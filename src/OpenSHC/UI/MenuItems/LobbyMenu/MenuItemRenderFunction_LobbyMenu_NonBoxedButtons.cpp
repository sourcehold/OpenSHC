#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b95950.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0042AE90
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_NonBoxedButtons(int param_1, ...)
        {
            BOOLEnum BVar1;
            int* piVar2;
            int iVar3;
            int iVar4;
            bool bVar5;
            uint uVar6;
            BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar1 != FALSE) {}
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                if (((param_1 != 2) && (param_1 != 3)) && ((param_1 != -0x14 && (param_1 != -1)))) {
                    bVar5 = param_1 == -2;
                LAB_0042aef2:
                    if (!bVar5) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                }
            } else if ((((DAT_MenuModalComposition1::instance.activeModalDialogID
                             == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT)
                            || (DAT_MenuModalComposition1::instance.activeModalDialogID
                                == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT))
                           && (param_1 != 2))
                && (((param_1 != -0x14 && (param_1 != -1)) && ((param_1 != -2 && (param_1 != -200)))))) {
                bVar5 = param_1 == -0xc9;
                goto LAB_0042aef2;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            bVar5 = true;
            DAT_ButtonUnknownZero::instance = 0;
            if (param_1 < 0x6a) {
                if (param_1 == 0x69) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        }
                        if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected < 0) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        }
                        if (DAT_GameSynchronyState::instance
                                .unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance
                                                                   .DAT_MapSelectionScrollOffset
                                            + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected + -1]]
                            != 0) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        }
                        if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState != 0) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(
                            DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                            uVar6 = 0xc2f0eb;
                        } else {
                            uVar6 = 0xccfaff;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x69,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, uVar6, 0x12, FALSE,
                            ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    }
                } else {
                    switch (param_1) {
                    case 1:
                        if (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                                DAT_ButtonUnknownZero::instance = 1;
                                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                    = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            }
                            piVar2 = DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue + 1;
                            while ((piVar2[-0x419c2] == -1 || (*piVar2 != 0))) {
                                piVar2 = piVar2 + 1;
                                if (0x1a2453b < (int)piVar2) {
                                LAB_0042afea:
                                    iVar4 = MACRO_CALL_MEMBER(
                                        OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid,
                                        DAT_GameSynchronyState::ptr)();
                                    if ((1 < iVar4) && (bVar5)) {
                                        iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                        MACRO_CALL(OpenSHC::UI::Rendering_Func::
                                                RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                                            ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                                    }
                                    iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x10;
                                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                                    MACRO_CALL(
                                        OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                                        ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                                }
                            }
                            bVar5 = false;
                            goto LAB_0042afea;
                        }
                        break;
                    case 2:
                        iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                            ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        return;
                    case 3:
                        if (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                                AlphaAndButtonSurfaceObj::ptr)(DAT_ButtonBackgroundBlendStrength::instance,
                                OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                            iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                                uVar6 = 0xc2f0eb;
                            } else {
                                uVar6 = 0xccfaff;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                                (int)((int)(DAT_ButtonW::instance / 2 + -10 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, uVar6, 0x12, FALSE,
                                ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        break;
                    case 4:
                        if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                            DAT_ButtonUnknownZero::instance = 1;
                        }
                        piVar2 = DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue + 1;
                        while ((piVar2[-0x419c2] == -1 || (*piVar2 != 0))) {
                            piVar2 = piVar2 + 1;
                            if (0x1a2453b < (int)piVar2) {
                            LAB_0042b17a:
                                iVar4 = MACRO_CALL_MEMBER(
                                    OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid,
                                    DAT_GameSynchronyState::ptr)();
                                if (iVar4 < 2) {
                                    bVar5 = false;
                                }
                                iVar4 = 0x20;
                                if (((!bVar5)
                                        || (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                                + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                                            < 0))
                                    || (DAT_GameSynchronyState::instance
                                            .unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                                                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance
                                                                               .DAT_MapSelectionScrollOffset
                                                        + DAT_GameSynchronyState::instance
                                                            .DAT_MapSelectionRelativeSelected
                                                        + -1]]
                                        < 1)) {
                                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                                    iVar4 = 0x10;
                                }
                                iVar4 = (0x20 - DAT_ButtonBackgroundBlendStrength::instance) * iVar4;
                                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                                    0x20 - ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5));
                            }
                        }
                        bVar5 = false;
                        goto LAB_0042b17a;
                    case -200:
                        iVar4 = 0;
                        do {
                            iVar3 = DAT_GameCore::instance.keepPositions[iVar4].x;
                            if ((((-1 < iVar3)
                                     && (iVar3 + 0x23c + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                                         <= DAT_MouseState::instance.screenSpaceX))
                                    && (DAT_MouseState::instance.screenSpaceX
                                        <= iVar3 + 0x253 + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth))
                                && ((iVar3 = DAT_GameCore::instance.keepPositions[iVar4].y
                                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                                    iVar3 + 3 <= DAT_MouseState::instance.screenSpaceY
                                        && (DAT_MouseState::instance.screenSpaceY <= iVar3 + 0x23)))) {
                                INT_00b95950::instance = iVar4;
                            }
                            iVar4 = iVar4 + 1;
                        } while (iVar4 < 8);
                        break;
                    case -0x65:
                    case -0xb:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                            DAT_PencilRenderCore::ptr)(1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                        return;
                    case -100:
                    switchD_0042af3a_caseD_ffffff9c:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                            DAT_PencilRenderCore::ptr)(0, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                        return;
                    case -0x14:
                        if (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        }
                        DAT_ButtonUnknownZero::instance = 0;
                        if (DAT_GameSynchronyState::instance.DAT_TwoIfNotHost != 2) {
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        }
                        if (DAT_GameSynchronyState::instance
                                .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            == 0) {
                            DAT_CurrentButtonGmDataIndex::instance = DAT_CurrentButtonGmDataIndex::instance + 1;
                        }
                        iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                            ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        return;
                    case -10:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                            DAT_PencilRenderCore::ptr)(0, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                        return;
                    case -2:
                        if (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                                DAT_PencilRenderCore::ptr)(
                                1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                        }
                        break;
                    case -1:
                        if (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                            goto switchD_0042af3a_caseD_ffffff9c;
                    }
                }
            } else if (param_1 == 0x19d) {
                DAT_ButtonUnknownZero::instance = 0;
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    DAT_ButtonUnknownZero::instance = 1;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                }
                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            DAT_ButtonUnknownZero::instance = 0;
        }

    }
}
}
