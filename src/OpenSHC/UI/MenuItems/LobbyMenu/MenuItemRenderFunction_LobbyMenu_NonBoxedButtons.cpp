#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
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

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042AE90
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_NonBoxedButtons(int buttonID, ...)
        {
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            // while the round table or an AI lord select is open, only some buttons stay live
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                if (buttonID != 2 && buttonID != 3 && buttonID != -20 && buttonID != -1 && buttonID != -2) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            } else if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                if (buttonID != 2 && buttonID != -20 && buttonID != -1 && buttonID != -2 && buttonID != -200
                    && buttonID != -201) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            // every human player in the lobby is ready (buttons 1 and 4); declared in those cases the match is lost
            BOOLEnum allReady = TRUE;
            DAT_ButtonUnknownZero::instance = FALSE;
            switch (buttonID) {
            // the scroll buttons (up, down): -1 / -2 the chat, -10 / -11 the map list, -100 / -101 the map description
            // six cases in this order (-11 and -101 may swap): the compiler joins them itself; joined here, no match
            case -10:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -1:
                // the chat's scroll buttons are not drawn in a single-player skirmish
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -11:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -2:
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -100:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            case -101:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, DAT_ButtonBackgroundBlendStrength::instance);
                break;
            // 1: the host's Load button, lit once every human player is ready and checkPlayerSetValid gives 2 or more
            case 1: {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    break;
                }
                if (!DAT_GameSynchronyState::instance.isHost) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    break;
                }
                for (int i = 1; i < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++i) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] != -1
                        && DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[i] == 0) {
                        allReady = FALSE;
                        break;
                    }
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid, DAT_GameSynchronyState::ptr)()
                        >= 2
                    && allReady) {
                    // the fade written the long way round, for the match; it comes back to the blend strength itself
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                } else {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
                }
                break;
            }
            // 2: Main Menu (leave the lobby), always lit
            case 2:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                break;
            // 3: a Ready text button (its click toggles ready, as -20's does); the text is lighter while it is
            // interacted with
            case 3:
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // two calls: one call with the colour chosen in it compiles without the branch
                // "Ready" (the button's own number, 3)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, buttonID,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance - 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, buttonID,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance - 10, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                break;
            // -20: the Ready picture button
            case -20:
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    break;
                }
                // cleared again, as the original does
                DAT_ButtonUnknownZero::instance = FALSE;
                if (DAT_GameSynchronyState::instance.DAT_TwoIfNotHost != 2) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                // a player who is not ready yet gets the next picture
                if (DAT_GameSynchronyState::instance
                        .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    == 0) {
                    ++DAT_CurrentButtonGmDataIndex::instance;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                break;
            // 4: the host's Launch Game button, lit once every human player is ready, checkPlayerSetValid gives 2 or
            // more and the selected map's entry is above zero
            case 4: {
                if (!DAT_GameSynchronyState::instance.isHost) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    break;
                }
                for (int i = 1; i < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++i) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] != -1
                        && DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[i] == 0) {
                        allReady = FALSE;
                        break;
                    }
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::checkPlayerSetValid, DAT_GameSynchronyState::ptr)()
                    < 2) {
                    allReady = FALSE;
                }
                int strength = 32;
                if (!allReady
                    || DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        < 0
                    || DAT_GameSynchronyState::instance
                            .unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected]]
                        <= 0) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    strength = 16;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    32 - (32 - DAT_ButtonBackgroundBlendStrength::instance) * strength / 32);
                break;
            }
            // -200: the keeps on the map preview; the one under the mouse is remembered
            case -200:
                for (int i = 0; i < countof(DAT_GameCore::instance.keepPositions); ++i) {
                    if (DAT_GameCore::instance.keepPositions[i].x >= 0
                        && DAT_MouseState::instance.screenSpaceX >= DAT_GameCore::instance.keepPositions[i].x
                                + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 572
                        && DAT_MouseState::instance.screenSpaceX <= DAT_GameCore::instance.keepPositions[i].x
                                + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 595
                        && DAT_MouseState::instance.screenSpaceY >= DAT_GameCore::instance.keepPositions[i].y
                                + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 3
                        && DAT_MouseState::instance.screenSpaceY <= DAT_GameCore::instance.keepPositions[i].y
                                + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 35) {
                        INT_00b95950::instance = i;
                        return;
                    }
                }
                break;
            // 105: the host's Send Map button, drawn only while the selected map's entry is zero and no map file is
            // being received
            case 105:
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    break;
                }
                if (!DAT_GameSynchronyState::instance.isHost
                    || DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected < 0
                    || DAT_GameSynchronyState::instance
                            .unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected]]
                        != 0
                    || DAT_GameSynchronyState::instance.DAT_MapFileReceivingState != 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // two calls, as for button 3
                // "Send Map"
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 105,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 105,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                        (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                break;
            // 413: Skirmish Masters (the rankings), shown only in a single-player skirmish
            case 413:
                // cleared again, as the original does
                DAT_ButtonUnknownZero::instance = FALSE;
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    break;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                break;
            }
        }

    }
}
}
