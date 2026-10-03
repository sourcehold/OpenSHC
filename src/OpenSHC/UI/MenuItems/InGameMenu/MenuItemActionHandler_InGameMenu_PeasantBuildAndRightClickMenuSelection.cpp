#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::BuildMenuTabType;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00434350
        void InGameMenu::MenuItemActionHandler_InGameMenu_PeasantBuildAndRightClickMenuSelection(int param_1, ...)
        {
            DWORD DVar1;
            int iVar2;
            BOOLEnum BVar3;
            dword elementState;
            if (DAT_GameSynchronyState::instance.syncStatus != 0) {}
            if (DAT_GameSynchronyState::instance.saveRelated != 0) {}
            if (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                && (DAT_00b960f8::instance != 0x42)) {
                if (INT_00b960f0::instance == 0) {
                    DVar1 = timeGetTime();
                    INT_00b960f0::instance = DVar1 + 20000;
                } else {
                    DVar1 = timeGetTime();
                    if (0x5dc < (int)(DVar1 - INT_00b960f0::instance)) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_00b960f8::instance;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        INT_00b960f0::instance = DVar1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                            OpenSHC::Commands::GCT_UPDATE_LOBBY_FACE_BITMAPSPECIALTRANSMITLOGIC);
                        DAT_00b960f8::instance = DAT_00b960f8::instance + 1;
                    }
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            LAB_004344b0:
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_PEOPLE_LEFT_TO_PLACE,
                    (dword)((int)((uint)(0x8fb < (int)DAT_UnitsState::instance.unitCount))));
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            LAB_004344a8:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    goto LAB_004344b0;
            } else if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
                || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)) {
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU) {
                    iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getArmySize, DAT_UnitsState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID);
                    if (iVar2 == 0) {
                        if (DAT_GameCore::instance.activeMenuTab.buildMenuTab
                            == OpenSHC::UI::Enums::BMTT_CASTLE_KEEPS) {
                            if (DAT_GameCore::instance.menuSwitchDelay == -1) {
                                iVar2 = MACRO_CALL_MEMBER(
                                    OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                                    DAT_GameState::ptr)();
                                if (iVar2 == 1) {
                                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::
                                            CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                        OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                        = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView,
                                        DAT_GameCore::ptr)(OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                                    goto LAB_004344a8;
                                }
                                elementState = 1;
                                goto LAB_00434498;
                            }
                        } else if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == ((BuildMenuTabType)0x31))
                            goto LAB_00434497;
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                    } else if (DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_UNUSED_WITCHHOIST) {
                    LAB_00434497:
                        elementState = 2;
                    LAB_00434498:
                        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, (dword)((int)(elementState)));
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    }
                }
                goto LAB_004344a8;
            }
            if (DAT_MouseState::instance.mouseBasedEvent == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
                DAT_GameCore::instance.field83_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                    goto LAB_004345e4;
                iVar2 = 4;
            } else if ((((DAT_MouseState::instance.rightClickState == FALSE)
                            || (DAT_MouseState::instance.mouseBasedEvent == 2))
                           && ((DAT_ModifierKeyState::instance.ctrl == 0
                               || (DAT_ModifierKeyState::instance.downArrow == 0))))
                && (DAT_ModifierKeyState::instance.v == 0)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(4);
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                    goto LAB_004345e4;
                iVar2 = 5;
            } else if (DAT_MouseState::instance.mouseBasedEvent == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                    DAT_MouseState::instance.mapOrientationCopy3);
                DAT_GameCore::instance.field83_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                    goto LAB_004345e4;
                iVar2 = 2;
            } else if (DAT_MouseState::instance.mouseBasedEvent == 4) {
                DAT_MouseState::instance.field51_0x198 = 2;
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(
                    (uint)(DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk == 0));
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                DAT_GameCore::instance.field83_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                    goto LAB_004345e4;
                iVar2 = 3;
            } else {
                if (DAT_MouseState::instance.mouseBasedEvent != 5)
                    goto LAB_004345e4;
                DAT_MouseState::instance.field52_0x19c = 2;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                DAT_GameCore::instance.field83_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                    goto LAB_004345e4;
                iVar2 = 0x11;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(iVar2);
        LAB_004345e4:
            if (DAT_ViewportRenderState::instance.viewportState.field0_0x0 == 0) {
                if (DAT_MouseState::instance.rightClickStart != 0) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                    DAT_GameCore::instance.field83_0x15c = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
            }
            if (DAT_MouseState::instance.rightClickStart == 0) {
                if (((DAT_MouseState::instance.rightClickStop != 0)
                        && (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_MOAT))
                    && (DAT_GameCore::instance.field83_0x15c == 0)) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::noop1, DAT_TileMapState::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseTile);
                if (DAT_MouseState::instance.leftClickState == FALSE) {
                    if (DAT_UnitsState::instance
                            .unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        < 1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::ProcessBuildingClickBonus,
                            AlphaAndButtonSurfaceObj::ptr)(
                            DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID);
                    }
                    if (DAT_MouseState::instance.draggingStopped == FALSE) {}
                    if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_NULL) {}
                } else if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_NULL) {
                    if ((DAT_MouseState::instance.leftClickStart == 0)
                        && (DAT_ViewportRenderState::instance.viewportState.field4_0x10
                            == DAT_ViewportRenderState::instance.viewportState.mouseTile)) {}
                    DAT_ViewportRenderState::instance.viewportState.field4_0x10
                        = DAT_ViewportRenderState::instance.viewportState.mouseTile;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                }
                if (((((DAT_UnitsState::instance
                               .unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           < 1)
                          && (DAT_UnitsState::instance.totalUnitsInSelection < 1))
                         && ((DVar1 = timeGetTime(),
                             DAT_MouseState::instance.draggingStopped != FALSE
                                 && ((((DAT_MouseState::instance.field31_0x94 == 0
                                           && ((*(int*)&DAT_MouseState::instance.padding_0x98[0]) == 0))
                                          && (BVar3
                                              = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::
                                                                      SelectUnitAndOpenStatusMenu,
                                                  AlphaAndButtonSurfaceObj::ptr)(
                                                  DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID),
                                              BVar3 == FALSE))
                                     && ((199 < (int)(DVar1
                                              - DAT_ViewportRenderState::instance.viewportState.field13_0x34)
                                         || (BVar3
                                             = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::
                                                                     SelectUnitAndOpenStatusMenu,
                                                 AlphaAndButtonSurfaceObj::ptr)(
                                                 DAT_ViewportRenderState::instance.viewportState.mouseRayLastUnitID),
                                             BVar3 == FALSE))))))))
                        && ((
                            BVar3 = MACRO_CALL_MEMBER(
                                OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                                AlphaAndButtonSurfaceObj::ptr)(
                                DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID),
                            BVar3 == FALSE
                                && (((DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                              .viewportState.mouseAtomRefFloorTile]
                                         & 2)
                                        != 0
                                    && ((DAT_TileMapState::instance.WallOwnerLayer[DAT_ViewportRenderState::instance
                                                 .viewportState.mouseAtomRefFloorTile]
                                            & 7)
                                            + 1
                                        == DAT_GameSynchronyState::instance.currentPlayerSlotID))))))
                    && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .stockpile.id
                        != 0)) {
                    DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0xb;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                    DAT_BuildingsState::instance.newSelectedUnitID = 0;
                    DAT_BuildingsState::instance.newSelectedBuildingID
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .stockpile.id;
                }
            } else {
                if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_MOAT) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                }
                DAT_GameCore::instance.field83_0x15c = 0;
            }
        }

    }
}
}
