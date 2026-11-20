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
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00434350
        void InGameMenu::MenuItemActionHandler_InGameMenu_PeasantBuildAndRightClickMenuSelection(int unused, ...)
        {
            if (DAT_GameSynchronyState::instance.syncStatus != 0) {
                return;
            }
            if (DAT_GameSynchronyState::instance.saveRelated != 0) {
                return;
            }
            // in a multiplayer game, command 117 goes out every 1.5 seconds with a counter, until that reaches 66
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_00b960f8::instance != 66) {
                if (INT_00b960f0::instance == 0) {
                    INT_00b960f0::instance = timeGetTime() + 20000;
                } else {
                    DWORD const now = timeGetTime();
                    if ((int)(now - INT_00b960f0::instance) > 1500) {
                        INT_00b960f0::instance = now;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_00b960f8::instance;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                            OpenSHC::Commands::GCT_UPDATE_LOBBY_FACE_BITMAPSPECIALTRANSMITLOGIC);
                        DAT_00b960f8::instance++;
                    }
                }
            }
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk
                    || DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)
                && DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getArmySize, DAT_UnitsState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    == 0) {
                    if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_CASTLE_KEEPS) {
                        if (DAT_GameCore::instance.menuSwitchDelay == -1) {
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                                    DAT_GameState::ptr)()
                                != 1) {
                                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::
                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 1);
                                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                            } else {
                                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::
                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                    = OpenSHC::UI::Enums::BMTT_CASTLE;
                                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                            }
                        } else {
                            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                            MACRO_CALL(
                                OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                        }
                    } else if (DAT_GameCore::instance.activeMenuTab.buildMenuTab
                        == OpenSHC::UI::Enums::BMTT_UNKNOWN_49) {
                        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 2);
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    } else {
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                            OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                    }
                } else if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_UNKNOWN_49) {
                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 2);
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                // a call in each arm with its own constant: the original pushes the constant inside the arm
                if (DAT_UnitsState::instance.unitCount >= 2300) {
                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        OpenSHC::UI::Enums::DEID_PEOPLE_LEFT_TO_PLACE, 1);
                } else {
                    MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        OpenSHC::UI::Enums::DEID_PEOPLE_LEFT_TO_PLACE, 0);
                }
            }
            // the mouse's view events; each is recorded for the tutorial
            if (DAT_MouseState::instance.mouseBasedEvent == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(3);
                DAT_GameCore::instance.field_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(4);
                }
            } else if ((!DAT_MouseState::instance.rightClickState || DAT_MouseState::instance.mouseBasedEvent == 2)
                && (DAT_ModifierKeyState::instance.ctrl == 0 || DAT_ModifierKeyState::instance.downArrow == 0)
                && DAT_ModifierKeyState::instance.v == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::triggerLoweredView, DAT_TileMapState::ptr)(4);
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(5);
                }
            } else if (DAT_MouseState::instance.mouseBasedEvent == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMapRotation, DAT_TileMapState::ptr)(
                    DAT_MouseState::instance.mapOrientationCopy3);
                DAT_GameCore::instance.field_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(2);
                }
            } else if (DAT_MouseState::instance.mouseBasedEvent == 4) {
                DAT_MouseState::instance.field_0x198 = 2;
                // a call in each arm here too, each pushing its own argument as the original does
                if (DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(0);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport, DAT_ViewportRenderState::ptr)(1);
                }
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                DAT_GameCore::instance.field_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(3);
                }
            } else if (DAT_MouseState::instance.mouseBasedEvent == 5) {
                DAT_MouseState::instance.field_0x19c = 2;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::toggleFlatView, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.flatViewToggleValue1 ^ 1);
                DAT_GameCore::instance.field_0x15c = 1;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::RecordTutorialPlayerAction)(17);
                }
            }
            // the mouse is not over the map
            if (DAT_ViewportRenderState::instance.viewportState.field_0x0 == 0) {
                if (DAT_MouseState::instance.rightClickStart) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                    DAT_GameCore::instance.field_0x15c = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::storeXYAndResetMouseState, DAT_MouseState::ptr)();
                return;
            }
            if (DAT_MouseState::instance.rightClickStart) {
                if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_MOAT) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                }
                DAT_GameCore::instance.field_0x15c = 0;
                return;
            }
            if (DAT_MouseState::instance.rightClickStop
                && DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_MOAT
                && DAT_GameCore::instance.field_0x15c == 0) {
                DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::noop1, DAT_TileMapState::ptr)(
                DAT_ViewportRenderState::instance.viewportState.mouseFlatTile);
            if (!DAT_MouseState::instance.leftClickState) {
                if (DAT_UnitsState::instance.unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    <= 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::processBuildingClickBonus,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID);
                }
                if (!DAT_MouseState::instance.draggingStopped) {
                    return;
                }
                if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_NULL) {
                    return;
                }
            } else if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                // no mapper command: the click is handled below. This arm stays empty on purpose: written as
                // `else if (command != M_MAPPER_NULL) { ... }` without it, the match is lost
            } else {
                if (!DAT_MouseState::instance.leftClickStart
                    && DAT_ViewportRenderState::instance.viewportState.previousMouseTile
                        == DAT_ViewportRenderState::instance.viewportState.mouseFlatTile) {
                    return;
                }
                DAT_ViewportRenderState::instance.viewportState.previousMouseTile
                    = DAT_ViewportRenderState::instance.viewportState.mouseFlatTile;
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                return;
            }
            if (DAT_UnitsState::instance.unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                > 0) {
                return;
            }
            if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
                return;
            }
            // nothing selected: a click selects the unit or opens the building under the mouse, or the stockpile
            // menu when the tile has the stockpile flag and belongs to the player
            DWORD const clickTime = timeGetTime();
            if (!DAT_MouseState::instance.draggingStopped) {
                return;
            }
            if (DAT_MouseState::instance.selectionBoxState != 0) {
                return;
            }
            if (DAT_MouseState::instance.savedSelectionBoxState != 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::selectUnitAndOpenStatusMenu,
                    AlphaAndButtonSurfaceObj::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID)) {
                return;
            }
            // within 200 ms, the unit that was under the mouse before counts too (the result in a local: tested
            // on the call, the match is lost)
            BOOLEnum selectedLast = FALSE;
            if ((int)(clickTime - DAT_ViewportRenderState::instance.viewportState.field_0x34) < 200) {
                selectedLast = MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::selectUnitAndOpenStatusMenu,
                    AlphaAndButtonSurfaceObj::ptr)(DAT_ViewportRenderState::instance.viewportState.mouseRayLastUnitID);
            }
            if (selectedLast) {
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::openBuildingStatusMenuForBuildingID,
                    AlphaAndButtonSurfaceObj::ptr)(
                    DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID)) {
                return;
            }
            if ((DAT_TileMapState::instance
                        .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                    & 2)
                == 0) {
                return;
            }
            if ((DAT_TileMapState::instance
                        .WallOwnerLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                    & 7)
                    + 1
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                    .id
                == 0) {
                return;
            }
            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = OpenSHC::UI::Enums::BASMTT_STOCKPILE;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
            DAT_BuildingsState::instance.newSelectedUnitID = 0;
            DAT_BuildingsState::instance.newSelectedBuildingID
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                      .id;
        }

    }
}
}
