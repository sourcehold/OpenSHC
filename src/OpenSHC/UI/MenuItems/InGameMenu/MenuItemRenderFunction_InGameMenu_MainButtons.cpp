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
        void InGameMenu::MenuItemRenderFunction_InGameMenu_MainButtons(int param_1, ...)
        {
            ButtonGmData* buttonGmData;
            int iVar1;
            int iVar2;
            int iVar3;
            bool bVar4;
            iVar3 = 0;
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))
                && param_1 != 71 && param_1 != -4 && param_1 <= -10) {
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == param_1) {
                if (param_1 != 71) {
                    iVar3 = 2;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    goto LAB_00464449;
                }
            LAB_0046444e:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
            } else {
            LAB_00464449:
                if (param_1 == 71)
                    goto LAB_0046444e;
            }
            if (param_1 == -4) {
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                goto LAB_00464732;
            }
            if (param_1 == -5) {
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                    && (DAT_GameCore::instance.field_0x6c != 0)) {
                    DAT_ButtonUnknownZero::instance = 1;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                } else if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL
                        || (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk))) {
                    LAB_004644dc:
                        DAT_ButtonUnknownZero::instance = 1;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        return;
                    }
                } else {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                        goto LAB_004644dc;
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                        bVar4 = DAT_GameCore::instance.isSkirmishTrail == TRUE;
                        goto LAB_004644d6;
                    }
                }
            LAB_004645b6:
                if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
            LAB_004645c8:
                if ((param_1 == -90) || (param_1 == -91)) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                    if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                        goto LAB_004645f5;
                    if (param_1 == -90) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else {
                LAB_004645f5:
                    if (param_1 == -90)
                        goto LAB_00464611;
                }
                if (param_1 == -91 || (10 <= param_1 && (param_1 <= 49)))
                    goto LAB_00464611;
            } else {
                if (param_1 <= -10 && param_1 != -90 && param_1 != -91) {
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                    if (-100 < param_1) {
                        iVar1 = -9 - param_1;
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION) {
                                if (5 < iVar1) {
                                    DAT_ButtonUnknownZero::instance = 1;
                                    return;
                                }
                            } else if (iVar1 != 1) {
                                DAT_ButtonUnknownZero::instance = 1;
                            }
                        }
                        if (iVar1 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                            iVar3 = 8;
                        }
                    }
                }
                if (param_1 == -1) {
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_ButtonUnknownZero::instance = 1;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        return;
                    }
                    if ((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_QUIT_DIALOG)
                        && (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 47)) {
                        DAT_ButtonUnknownZero::instance = 1;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        return;
                    }
                    goto LAB_004645b6;
                }
                if (param_1 == -6) {
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                        bVar4 = DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT;
                    LAB_004644d6:
                        if (!bVar4)
                            goto LAB_004644dc;
                    }
                    goto LAB_004645b6;
                }
                if ((param_1 == 29) || (param_1 == 26)) {
                LAB_004645a4:
                    if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                        && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                LAB_004645ad:
                    if ((param_1 <= -1) && (-10 < param_1))
                        goto LAB_004645b6;
                    goto LAB_004645c8;
                }
                if (param_1 != 27)
                    goto LAB_004645ad;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)
                    goto LAB_004645a4;
            LAB_00464611:
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                } else {
                    if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                        && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS)) {
                        DAT_ButtonUnknownZero::instance = 1;
                        return;
                    }
                    iVar1
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                            DAT_GameState::ptr)();
                    if (iVar1 < 1
                        || (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                            && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_STOCKS))) {
                        if ((param_1 != -90) && (param_1 != -91)) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            iVar3 = 1;
                            switch (param_1) {
                            case 10:
                                iVar3 = 54;
                                break;
                            case 20:
                                iVar3 = 55;
                                break;
                            case 40:
                                iVar3 = 56;
                                break;
                            case 30:
                                iVar3 = 57;
                                break;
                            case 28:
                                iVar3 = 58;
                                break;
                            case 25:
                                iVar3 = 59;
                                break;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                (OpenSHC::DE::SHCDE::eGM)(DAT_UIButtonDefinedData::instance
                                        .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                        .gmId_0x0),
                                iVar3, (int)(DAT_ButtonX::instance), DAT_ButtonY::instance);
                            DAT_CurrentButtonPictureInGm::instance = iVar3;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                            return;
                        }
                        MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    }
                }
            }
            if ((param_1 == -2) && (DAT_WallAndPitchState::instance.countdown == 0)) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                iVar3 = 2;
            }
        LAB_00464732:
            buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            iVar2 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                DAT_ButtonCurrentlyInteracting::instance);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)(buttonGmData->gmId_0x0), iVar2 + iVar3,
                DAT_ButtonX::instance, DAT_ButtonY::instance);
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4
                + iVar3;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (param_1 == -4) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance - 1, (int)(DAT_ButtonY::instance + 17), (int)(DAT_ButtonX::instance - 1),
                    (int)(DAT_ButtonH::instance - 1 + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance - 2, (int)(DAT_ButtonY::instance + 17), (int)(DAT_ButtonX::instance - 2),
                    (int)(DAT_ButtonH::instance - 1 + DAT_ButtonY::instance), (ushort)(COL_BLACK::instance.shortValue));
                return;
            }
            if (param_1 == 71) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScribeFrame)();
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGoldValue)();
                return;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
