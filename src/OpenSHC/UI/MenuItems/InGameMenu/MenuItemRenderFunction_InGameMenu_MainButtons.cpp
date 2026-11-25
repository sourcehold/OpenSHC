#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004643F0
        void InGameMenu::MenuItemRenderFunction_InGameMenu_MainButtons(int button, ...)
        {
            int pictureOffset = 0;
            DAT_ButtonUnknownZero::instance = FALSE;
            // in the barracks and the mercenary post only the scribe, -4 and the buttons from -10 down stay active
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)
                && button != 71 && button != -4 && button > -10) {
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            // the open tab's button is drawn pressed
            if (DAT_GameCore::instance.activeMenuTab.tabType == button && button != 71) {
                pictureOffset = 2;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            if (button == 71
                && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            if (button == -4) {
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            } else {
                if (button == -5) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                        && DAT_GameCore::instance.field_0x6c != 0) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    } else if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                                   && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL
                                       || (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                                           && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)))
                        || (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && (DAT_GameSynchronyState::instance.currentGameMode
                                    != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                                || (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                                    // != TRUE rather than == FALSE: the original compares the flag with 1
                                    && DAT_GameCore::instance.isSkirmishTrail != TRUE)))) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                }
                // the editor's player buttons: in an invasion players 1 to 5, in other single-player maps only player
                // 1, the current player's drawn pressed
                if (button <= -10 && button != -90 && button != -91) {
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        return;
                    }
                    if (button > -100) {
                        int const player = -9 - button;
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION) {
                                if (player > 5) {
                                    DAT_ButtonUnknownZero::instance = TRUE;
                                    return;
                                }
                            } else if (player != 1) {
                                DAT_ButtonUnknownZero::instance = TRUE;
                                return;
                            }
                        }
                        if (player == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                            pictureOffset = 8;
                        }
                    }
                }
                if (button == -1) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_QUIT_DIALOG
                        && DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 47) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                } else if (button == -6) {
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                        && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                } else if ((button == OpenSHC::UI::Enums::BMTT_ARAB_SOLDIERS
                               || button == OpenSHC::UI::Enums::BMTT_EUROP_SOLDIERS
                               || (button == OpenSHC::UI::Enums::BMTT_RUINS
                                   && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (button < 0 && button > -10
                    && DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                    && DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if ((button == -90 || button == -91)
                    && (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                            && DAT_GameSynchronyState::instance.currentGameMode
                                == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                            && button == -90))) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                // the build menu's buttons: without a keep and a granary (or in the stocks tab) they are drawn greyed
                if (button == -90 || button == -91
                    || (button >= OpenSHC::UI::Enums::BMTT_CASTLE && button <= OpenSHC::UI::Enums::BMTT_UNKNOWN_49)) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                        if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                            DAT_ButtonUnknownZero::instance = TRUE;
                            return;
                        }
                    } else {
                        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                            && DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                            DAT_ButtonUnknownZero::instance = TRUE;
                            return;
                        }
                        if (MACRO_CALL_MEMBER(
                                OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                                DAT_GameState::ptr)()
                                <= 0
                            || (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                                && DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_STOCKS)) {
                            if (button == -90 || button == -91) {
                                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                                return;
                            }
                            DAT_ButtonUnknownZero::instance = TRUE;
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            int picture = 1;
                            switch (button) {
                            case OpenSHC::UI::Enums::BMTT_CASTLE:
                                picture = 54;
                                break;
                            case OpenSHC::UI::Enums::BMTT_INDUSTRY:
                                picture = 55;
                                break;
                            case OpenSHC::UI::Enums::BMTT_FARMS:
                                picture = 56;
                                break;
                            case OpenSHC::UI::Enums::BMTT_TOWN:
                                picture = 57;
                                break;
                            case OpenSHC::UI::Enums::BMTT_WEAPONS:
                                picture = 58;
                                break;
                            case OpenSHC::UI::Enums::BMTT_FOOD:
                                picture = 59;
                                break;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                (OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                    .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                    .gmId_0x0,
                                picture, DAT_ButtonX::instance, DAT_ButtonY::instance);
                            DAT_CurrentButtonPictureInGm::instance = picture;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                            return;
                        }
                    }
                }
                if (button == -2 && DAT_WallAndPitchState::instance.countdown == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    pictureOffset = 2;
                }
            }
            // held as a pointer: the original keeps it in ecx across the getPictureNumberInGm call
            OpenSHC::UI::Rendering::ButtonGmData* const buttonGmData
                = &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance];
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)buttonGmData->gmId_0x0,
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                    DAT_ButtonCurrentlyInteracting::instance)
                    + pictureOffset,
                DAT_ButtonX::instance, DAT_ButtonY::instance);
            // read through the index again, not buttonGmData: the original reloads it after the draw call
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4
                + pictureOffset;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (button == -4) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance - 1, DAT_ButtonY::instance + 17, DAT_ButtonX::instance - 1,
                    DAT_ButtonH::instance + DAT_ButtonY::instance - 1, COL_BLACK::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance - 2, DAT_ButtonY::instance + 17, DAT_ButtonX::instance - 2,
                    DAT_ButtonH::instance + DAT_ButtonY::instance - 1, COL_BLACK::instance.shortValue);
                return;
            }
            if (button == 71) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScribeFrame)();
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGoldValue)();
            }
        }

    }
}
}
