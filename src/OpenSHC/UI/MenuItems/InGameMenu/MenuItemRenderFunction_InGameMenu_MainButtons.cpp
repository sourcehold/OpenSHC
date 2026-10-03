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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::BuildMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Type propagation algorithm not settling
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004643F0
        void InGameMenu::MenuItemRenderFunction_InGameMenu_MainButtons(int param_1, ...)
        {
            ButtonGmData* buttonGmData;
            int iVar1;
            int iVar2;
            int _digitSet2;
            int _color2;
            int iVar3;
            bool bVar4;
            int drawY;
            iVar3 = 0;
            DAT_ButtonUnknownZero::instance = 0;
            if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                && ((((DAT_GameCore::instance.activeMenuTab.tabType
                              == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                          || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))
                         && (param_1 != 0x47))
                    && ((param_1 != -4 && (-10 < param_1)))))) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == param_1) {
                if (param_1 != 0x47) {
                    iVar3 = 2;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    goto LAB_00464449;
                }
            LAB_0046444e:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
            } else {
            LAB_00464449:
                if (param_1 == 0x47)
                    goto LAB_0046444e;
            }
            if (param_1 == -4) {
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                goto LAB_00464732;
            }
            if (param_1 == -5) {
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                    && (DAT_GameCore::instance.field24_0x6c != 0)) {
                    DAT_ButtonUnknownZero::instance = 1;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                } else if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                        || ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION
                            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)))) {
                    LAB_004644dc:
                        DAT_ButtonUnknownZero::instance = 1;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
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
                }
            LAB_004645c8:
                if ((param_1 == -0x5a) || (param_1 == -0x5b)) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                    if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                        goto LAB_004645f5;
                    if (param_1 == -0x5a) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                } else {
                LAB_004645f5:
                    if (param_1 == -0x5a)
                        goto LAB_00464611;
                }
                if ((param_1 == -0x5b) || ((9 < param_1 && (param_1 < 0x32))))
                    goto LAB_00464611;
            } else {
                if (((param_1 < -9) && (param_1 != -0x5a)) && (param_1 != -0x5b)) {
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                    if (-100 < param_1) {
                        iVar1 = -9 - param_1;
                        if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                            if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION) {
                                if (5 < iVar1) {
                                    DAT_ButtonUnknownZero::instance = 1;
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
                    }
                    if ((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_QUIT_DIALOG)
                        && (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter == 0x2f)) {
                        DAT_ButtonUnknownZero::instance = 1;
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
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
                if ((param_1 == 0x1d) || (param_1 == 0x1a)) {
                LAB_004645a4:
                    if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                        && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                LAB_004645ad:
                    if ((param_1 < 0) && (-10 < param_1))
                        goto LAB_004645b6;
                    goto LAB_004645c8;
                }
                if (param_1 != 0x1b)
                    goto LAB_004645ad;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)
                    goto LAB_004645a4;
            LAB_00464611:
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                } else {
                    if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                        && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS)) {
                        DAT_ButtonUnknownZero::instance = 1;
                    }
                    iVar1
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                            DAT_GameState::ptr)();
                    if ((iVar1 < 1)
                        || ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                            && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_STOCKS)))) {
                        if ((param_1 != -0x5a) && (param_1 != -0x5b)) {
                            DAT_ButtonUnknownZero::instance = 1;
                            DAT_ButtonCurrentlyInteracting::instance = FALSE;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            iVar3 = 1;
                            switch (param_1) {
                            case 10:
                                iVar3 = 0x36;
                                break;
                            case 0x14:
                                iVar3 = 0x37;
                                break;
                            case 0x19:
                                iVar3 = 0x3b;
                                break;
                            case 0x1c:
                                iVar3 = 0x3a;
                                break;
                            case 0x1e:
                                iVar3 = 0x39;
                                break;
                            case 0x28:
                                iVar3 = 0x38;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                (OpenSHC::DE::SHCDE::eGM)(DAT_UIButtonDefinedData::instance
                                        .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                        .gmId_0x0),
                                iVar3, (int)((int)(DAT_ButtonX::instance)), DAT_ButtonY::instance);
                            DAT_CurrentButtonPictureInGm::instance = iVar3;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
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
            iVar1 = DAT_ButtonX::instance;
            drawY = DAT_ButtonY::instance;
            iVar2 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(
                DAT_ButtonCurrentlyInteracting::instance);
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                (OpenSHC::DE::SHCDE::eGM)(buttonGmData->gmId_0x0), iVar2 + iVar3, iVar1, drawY);
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4
                + iVar3;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (param_1 == -4) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance + -1, (int)((int)(DAT_ButtonY::instance + 0x11)),
                    (int)((int)(DAT_ButtonX::instance + -1)),
                    (int)((int)(DAT_ButtonH::instance + -1 + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance + -2, (int)((int)(DAT_ButtonY::instance + 0x11)),
                    (int)((int)(DAT_ButtonX::instance + -2)),
                    (int)((int)(DAT_ButtonH::instance + -1 + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
            }
            if (param_1 != 0x47) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScribeFrame)();
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGoldValue)();
        }

    }
}
}
