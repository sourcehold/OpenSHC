#include "../InGameMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOLEnum_00b98414.hpp"
#include "OpenSHC/Globals/DAT_00b9841c.hpp"
#include "OpenSHC/Globals/DAT_00b98420.hpp"
#include "OpenSHC/Globals/DAT_00b98424.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/TIME_PreviousClick.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Map::Buildings::BuildingTypeShort;
        using Map::Units::UnitTypeShort;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004348D0
        void InGameMenu::MenuItemActionHandler_InGameMenu_UnitSelectionAndControlsUnk(int param_1, ...)
        {
            int targetArea;
            int selectionArea;
            int manningCount;
            UnitTypeShort unitType;
            BuildingTypeShort buildingType;
            BOOLEnum check;
            uint clickedUnitID;
            uint targetUnitID;
            uint carryingEngineerID;
            short* manningEngineer;
            int id;
            int dy;
            int attackRange2;
            DWORD clickTime;
            undefined4 commandType;
            int dx2;
            int dx;
            dword toArea;
            int attackRange;
            int moatCommand;
            int lordMayAct;
            int buildingTarget;
            int attackGround;
            int secondPass;
            int canReach;
            int canMove;
            int cursorState;
            int combatUnitID;
            undefined4 setRallying;
            int moveFlags;
            DWORD now = timeGetTime();
            cursorState = -2;
            lordMayAct = 0;
            buildingTarget = 0;
            attackGround = 0;
            moatCommand = 0;
            BOOLEnum siegeUnitSelectedUnk = FALSE;
            if (DAT_GameCore::instance.gamePausedLogical) {
                return;
            }
            check = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
            if (check) {
                return;
            }
            if (DAT_GameSynchronyState::instance.syncStatus) {
                if (!DAT_MouseState::instance.selectionBoxMode) {
                    return;
                }
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                return;
            }
            if (DAT_GameSynchronyState::instance.saveRelated) {
                return;
            }
            DAT_MouseState::instance.field_0x1dc = -1;
            DAT_MouseState::instance.savedSelectionBoxState = DAT_MouseState::instance.selectionBoxState;
            DAT_TileMapState::instance.DAT_SelectionIconType = 0;
            if (70 < (int)(now - DAT_TileMapState::instance.cursorAnimationTime)) {
                DAT_TileMapState::instance.cursorAnimationTime = now;
                ++DAT_TileMapState::instance.cursorOverlayAnimationFrame;
                if (16 < DAT_TileMapState::instance.cursorOverlayAnimationFrame) {
                    DAT_TileMapState::instance.cursorOverlayAnimationFrame = 1;
                }
                ++DAT_TileMapState::instance.flagAnimationFrame;
            }
            if (0
                < DAT_UnitsState::instance.unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::drawFlagsAndUnitDestinations, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.DAT_CurrentTribeID);
            }
            if ((((!DAT_TileMapState::instance.shiftRelated0or3) || (DAT_TileMapState::instance.shiftRelated0or3 == 3))
                    || (DAT_TileMapState::instance.shiftRelated0or3 == 2))
                && DAT_MouseState::instance.draggingStopped && DAT_MouseState::instance.selectionBoxMode) {
                DAT_TribesState::instance.rallyCount = 1;
                if (DAT_TileMapState::instance.shiftRelated0or3 == 3) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::createTribeFromSelectedUnits, DAT_UnitsState::ptr)();
                    DAT_UnitsState::instance.pendingUnitControlMode = 1;
                    DAT_UnitsState::instance.unitControlsRelated = 1;
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    DAT_TileMapState::instance.shiftRelated0or3 = 1;
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                } else {
                    if (((DAT_UnitsState::instance.totalUnitsInSelection <= 0)
                            || (DAT_MouseState::instance.leftClickStartMoment == -1))
                        && (MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::applyDragBoxSelectionByPriority, DAT_UnitsState::ptr)(),
                            DAT_UnitsState::instance.totalUnitsInSelection == 0)) {
                        if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                            || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        DAT_UnitsState::instance.lastSelectedUnitID = 0;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                        DAT_TileMapState::instance.shiftRelated0or3 = 0;
                    }
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                    if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                        id = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::createUnitSelection, DAT_UnitsState::ptr)();
                        if (!id) {
                            return;
                        }
                        if ((!DAT_UnitsState::instance.someSelectedUnitID)
                            && (DAT_UnitsState::instance.totalUnitsInSelection == 1)) {
                            DAT_UnitsState::instance.someSelectedUnitID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                            DAT_UnitsState::instance.timePreviousDoubleClick = timeGetTime();
                        }
                        targetUnitID
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer,
                                DAT_UnitsState::ptr)();
                        if (!targetUnitID) {
                            if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    != UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                                && (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    != UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                                DAT_GameCore::instance.tabTypeSiegeSubset
                                    = DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab;
                            }
                            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                                || DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    == UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    = UI::Enums::BASMTT_SIEGETENT_SHIELD;
                            } else {
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    = UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
                            }
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                            DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                        } else if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                       == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                            || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        DAT_UnitsState::instance.pendingUnitControlMode = 1;
                        DAT_UnitsState::instance.unitControlsRelated = 1;
                        DAT_TileMapState::instance.shiftRelated0or3 = 1;
                        DAT_TileMapState::instance.pendingUnitCommand = 0;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                        DAT_TileMapState::instance.cursorOverlayGmID = 107;
                        return;
                    }
                }
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 1) {
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::recountUnitsInSelection, DAT_UnitsState::ptr)();
            }
            if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .lordKilledByPlayerID
                    != 0)
                && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.gameOver
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    return;
                }
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 1
                && DAT_UnitsState::instance.unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    < 1
                && DAT_UnitsState::instance.totalUnitsInSelection <= 0) {
                if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                    || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                        = DAT_GameCore::instance.tabTypeSiegeSubset;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                }
                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                DAT_TileMapState::instance.shiftRelated0or3 = 0;
                return;
            }
            if (DAT_BuildingsState::instance.siegeEngineCreationRelated01 != 0
                && --DAT_BuildingsState::instance.siegeEngineCreationRelated01 == 0) {
                int const siegeUnitID = DAT_BuildingsState::instance.unitID;
                DAT_GameCore::instance.tabTypeSiegeSubset = UI::Enums::BMTT_CASTLE;
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
                DAT_UnitsState::instance.units[siegeUnitID].isSelected = 1;
                DAT_TileMapState::instance.shiftRelated0or3 = 1;
                DAT_UnitsState::instance.totalUnitsInSelection = 1;
                DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::createUnitSelection, DAT_UnitsState::ptr)();
                return;
            }
            if ((!DAT_ViewportRenderState::instance.viewportState.field_0x0)
                && (!DAT_MinimapViewState::instance.minimapClickEnabled)) {
                return;
            }
            if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_NULL) {
                return;
            }
            if (DAT_MouseState::instance.rightClickStart) {
                if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                    || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                    if (DAT_MinimapViewState::instance.minimapClickEnabled) {
                        return;
                    }
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                        = DAT_GameCore::instance.tabTypeSiegeSubset;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                } else if ((DAT_MinimapViewState::instance.minimapClickEnabled)
                    && (DAT_TileMapState::instance.shiftRelated0or3 == 1)) {
                    return;
                }
                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                }
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                DAT_TileMapState::instance.shiftRelated0or3 = 0;
                return;
            }
            if (!DAT_MinimapViewState::instance.minimapClickEnabled) {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 5) {
                if ((!DAT_MouseState::instance.leftClickStart) && (!DAT_MouseState::instance.leftClickState)) {
                    DAT_TileMapState::instance.shiftRelated0or3 = 4;
                }
                goto setMouseCursorState;
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 4) {
                int const tileY = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                      [DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile];
                DAT_TileMapState::instance.cursorOverlayGmID = 107;
                int const tileX = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                    - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
                cursorState = 2;
                DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                bool outOfRange = false;
                bool rangeChecked = false;
                if (DAT_TileMapState::instance.activeTacticalPower == 6
                    && (DAT_TileMapState::instance
                            .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                        & 0x100U)) {
                    outOfRange = true;
                } else {
                    switch (DAT_TileMapState::instance.activeTacticalPower) {
                    case 2:
                    case 3:
                    case 4:
                    case 6:
                    case 13:
                    case 16: {
                        int const keepDy = tileY
                            - DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                                  .yEntry;
                        int const keepDx = tileX
                            - DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                                  .xEntry;
                        int const keepDistance = keepDx * keepDx + keepDy * keepDy;
                        rangeChecked = true;
                        // out of the power's range: cmp / jle at 0x00434E9E-0x00434EAA
                        if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                            if (keepDistance > 12544) {
                                outOfRange = true;
                            }
                        } else if (keepDistance > 2500) {
                            outOfRange = true;
                        }
                        if (DAT_GameState::instance.mapAndTime.skirmishExtremeMode2 && outOfRange) {
                            int const lordID
                                = DAT_GameState::instance
                                      .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                      .lordID;
                            if (lordID
                                && DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .lordUID
                                    == DAT_UnitsState::instance.units[lordID].uid) {
                                int const lordDx = tileX - DAT_UnitsState::instance.units[lordID].x;
                                int const lordDy = tileY - DAT_UnitsState::instance.units[lordID].y;
                                int const lordDistance = lordDy * lordDy + lordDx * lordDx;
                                outOfRange = false;
                                if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                    if (lordDistance > 12544) {
                                        outOfRange = true;
                                    }
                                } else if (lordDistance > 2500) {
                                    outOfRange = true;
                                }
                            }
                        }
                        if (!outOfRange) {
                            // no power within 25 tiles of an enemy keep; in extreme mode only while its lord is out of
                            // the power's range
                            for (int playerID = 1; playerID < countof(DAT_GameState::instance.playerDataArray);
                                ++playerID) {
                                if (0 < DAT_GameState::instance.playerDataArray[playerID]
                                            .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                                            .id
                                    && 0 < DAT_GameState::instance.playerDataArray[playerID]
                                            .buildingEntryInfos[Game::Player::Enums::BEIE_CAMPGROUND]
                                            .id
                                    && DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                                    int const enemyDy = tileY
                                        - DAT_GameState::instance.playerDataArray[playerID]
                                              .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                                              .yEntry;
                                    int const enemyDx = tileX
                                        - DAT_GameState::instance.playerDataArray[playerID]
                                              .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                                              .xEntry;
                                    if (enemyDx * enemyDx + enemyDy * enemyDy < 625) {
                                        if (!DAT_GameState::instance.mapAndTime.skirmishExtremeMode2) {
                                            outOfRange = true;
                                        } else {
                                            int const lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
                                            if (lordID
                                                && DAT_GameState::instance.playerDataArray[playerID].lordUID
                                                    == DAT_UnitsState::instance.units[lordID].uid) {
                                                int const lordDx = tileX - DAT_UnitsState::instance.units[lordID].x;
                                                int const lordDy = tileY - DAT_UnitsState::instance.units[lordID].y;
                                                int const lordDistance = lordDy * lordDy + lordDx * lordDx;
                                                if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                                    if (lordDistance > 12544) {
                                                        outOfRange = true;
                                                    }
                                                } else if (lordDistance > 2500) {
                                                    outOfRange = true;
                                                }
                                            }
                                        }
                                        if (outOfRange) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                    }
                }
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordKilledByPlayerID
                        == 0
                    && !outOfRange
                    && ((!(DAT_TileMapState::instance
                                 .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                             & 0x40501481U)
                            && DAT_TileMapState::instance.PathConnectionLayer[DAT_ViewportRenderState::instance
                                       .viewportState.mouseAtomRefFloorTile]
                                != 0)
                        || !rangeChecked)) {
                    if (DAT_MouseState::instance.leftClickStart) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_TileMapState::instance.activeTacticalPower;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                            = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_ACTIVATE_TACTICAL_POWERS);
                        DAT_TileMapState::instance.shiftRelated0or3 = 0;
                    } else {
                        switch (DAT_TileMapState::instance.activeTacticalPower) {
                        case 2:
                        case 4:
                        case 6:
                        case 13:
                        case 16:
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile,
                                DAT_TileMapState::ptr)(tileX, tileY, (int)(10));
                            break;
                        case 3:
                        case 5:
                        case 7:
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile,
                                DAT_TileMapState::ptr)(tileX, tileY, (int)(14));
                            break;
                        default:
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile,
                                DAT_TileMapState::ptr)(tileX, tileY, (int)(12));
                        }
                    }
                } else {
                    DAT_TileMapState::instance.cursorOverlayImageBase = 65;
                    DAT_TileMapState::instance.flagAnimationDivisor = 16;
                    DAT_TileMapState::instance.cursorOverlayGmID = 172;
                    cursorState = 4;
                }
                goto setMouseCursorState;
            }
            if (!DAT_TileMapState::instance.shiftRelated0or3 || DAT_TileMapState::instance.shiftRelated0or3 == 3
                || DAT_TileMapState::instance.shiftRelated0or3 == 2) {
                if (DAT_MouseState::instance.leftClickStart) {
                    BOOLEnum_00b98414::instance = FALSE;
                    DAT_UnitsState::instance.someSelectedUnitID = -1;
                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                    if (DAT_TileMapState::instance.shiftRelated0or3 == 2) {
                        DAT_UnitsState::instance.lastSelectedUnitID = 0;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    }
                    if (DAT_UnitsState::instance.totalUnitsInSelection <= 0) {
                        MACRO_CALL_MEMBER(Input::MouseState_Func::beginPointSelectionBox, DAT_MouseState::ptr)();
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectFirstUnitInDragBoxAnyPlayer, DAT_UnitsState::ptr)();
                        DAT_UnitsState::instance.lastSelectedUnitID
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(0);
                        if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                            DAT_UnitsState::instance.someSelectedUnitID = 0;
                            DAT_MouseState::instance.selectionBoxState = 1;
                            MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)();
                            BOOLEnum_00b98414::instance = TRUE;
                        }
                    }
                    goto setMouseCursorState;
                }
                if (DAT_MouseState::instance.leftClickState) {
                    if (!DAT_MouseState::instance.selectionBoxMode
                        || (MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)(),
                            DAT_MouseState::instance.selectionBoxState == 0)
                        || (DAT_GameCore::instance.menuSwitchDelay = -1,
                            0 < DAT_UnitsState::instance.totalUnitsInSelection
                                && ((DAT_MouseState::instance.leftClickStartMoment != -1
                                    && ((int)(now - DAT_MouseState::instance.leftClickStartMoment) <= 200)))))
                        goto setMouseCursorState;
                    if (DAT_TileMapState::instance.shiftRelated0or3 != 3) {
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::applyDragBoxSelectionByPriority, DAT_UnitsState::ptr)();
                        goto setMouseCursorState;
                    }
                selectDragBoxUnits:
                    MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectUnitsInDragBoxForCurrentPlayer, DAT_UnitsState::ptr)();
                    goto setMouseCursorState;
                }
                if (!DAT_MouseState::instance.draggingStopped) {
                    DAT_UnitsState::instance.totalUnitsInSelection = 0;
                    MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                    targetUnitID
                        = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(4);
                    if ((targetUnitID) && (DAT_UnitsState::instance.units[targetUnitID].isSelected == 0)) {
                        cursorState = 0;
                    }
                }
                goto setMouseCursorState;
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 != 1)
                goto setMouseCursorState;
            if (DAT_ModifierKeyState::instance.shift && !DAT_TribesState::instance.patrolButtonPressed
                && DAT_MouseState::instance.leftClickStart) {
                cursorState = 0;
                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                clickedUnitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(5);
                if (clickedUnitID) {
                    if (DAT_UnitsState::instance.units[clickedUnitID].isSelected != 0) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                            clickedUnitID);
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = clickedUnitID;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_UNIT_DESELECT);
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    } else {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getFirstSelectedUnitID, DAT_UnitsState::ptr)(
                            clickedUnitID);
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    }
                    goto setMouseCursorState;
                }
            }
            DAT_TileMapState::instance.field_0x5549b8 = 1;
            if (DAT_UnitsState::instance.unitControlsRelated == 4)
                goto moveToTile;
            if (DAT_UnitsState::instance.unitControlsRelated == 1) {
                lordMayAct = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY;
                DAT_TileMapState::instance.pendingUnitCommand = 0;
                DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                DAT_TileMapState::instance.cursorOverlayGmID = 107;
                DAT_TileMapState::instance.DAT_SelectionIconType = 1;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getFirstSelectedSiegeEngineID, DAT_UnitsState::ptr)();
                if (((DAT_ViewportRenderState::instance.viewportState.field_0x38)
                        && (id = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                            id != 0))
                    || (DAT_ViewportRenderState::instance.viewportState.field_0x40
                        && (id = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                            id != 0))) {
                    moatCommand = 1;
                    cursorState = 1;
                    DAT_TileMapState::instance.DAT_SelectionIconType = 25;
                    DAT_TileMapState::instance.cursorOverlayGmID = 16;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 91;
                    DAT_TileMapState::instance.pendingUnitCommand = -1;
                }
                id = DAT_ViewportRenderState::instance.viewportState.somePitchDitchID;
                if (DAT_ViewportRenderState::instance.viewportState.somePitchDitchID
                    && DAT_GameState::instance.mapAndTime.playerTeams[DAT_TileMapState::instance
                               .pitchDitches[DAT_ViewportRenderState::instance.viewportState.somePitchDitchID]
                               .owner]
                        == DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    && (check
                        = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasArchers, DAT_UnitsState::ptr)(),
                        check)) {
                    attackRange = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    dy = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::isBrazierNearby, DAT_EntityState::ptr)(
                        (int)DAT_UnitsState::instance.units[attackRange].x,
                        (int)(DAT_UnitsState::instance.units[attackRange].y),
                        (int)(DAT_UnitsState::instance.units[attackRange].buildingHeight
                            + DAT_UnitsState::instance.units[attackRange].terrainOrClimbHeight));
                    if ((dy)
                        && (dy = (int)DAT_TileMapState::instance.pitchDitches[id].y
                                - (int)DAT_UnitsState::instance.units[attackRange].y,
                            id = (int)DAT_TileMapState::instance.pitchDitches[id].x
                                - (int)DAT_UnitsState::instance.units[attackRange].x,
                            id * id + dy * dy <= 2401)) {
                        DAT_TileMapState::instance.pendingUnitCommand = 12;
                        DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                        cursorState = 2;
                        DAT_TileMapState::instance.cursorOverlayGmID = 107;
                        goto checkLordCursor;
                    }
                }
                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                targetUnitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(1);
                if (targetUnitID && MACRO_CALL(UI::Helpers_Func::SomeUnitAndViewportCheck)(targetUnitID)
                    && (!MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)()
                        || MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                            DAT_UnitsState::ptr)(targetUnitID))) {
                    targetArea = (short)DAT_TileMapState::instance
                                     .PathConnectionLayer[DAT_UnitsState::instance.units[targetUnitID].tile];
                    id = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    selectionArea
                        = (short)
                              DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[id].tile];
                    if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                            DAT_UnitsState::ptr)(targetUnitID)) {
                        if (MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                (dword)targetArea, (dword)selectionArea, 1)) {
                            DAT_TileMapState::instance.pendingUnitCommand = 3;
                            DAT_TileMapState::instance.cursorOverlayImageBase = -3;
                            DAT_UnitsState::instance.units[targetUnitID].field_0x6c = 2;
                            DAT_TileMapState::instance.instructionTargetUnitID = targetUnitID;
                            cursorState = -1;
                            goto checkLordCursor;
                        }
                    } else if (!MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasShieldOrSiegeMobileUnits,
                                   DAT_UnitsState::ptr)()) {
                        switch (DAT_UnitsState::instance.units[id].unitType) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_HARCHER:
                        case Map::Units::UT_S_FBALLISTA:
                            attackRange = 2916;
                            break;
                        default:
                            attackRange = 100000000;
                            dy = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
                            dy = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[id].owner,
                                (dword)targetArea, (dword)selectionArea, dy);
                            if (!dy
                                && (check
                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins,
                                        DAT_UnitsState::ptr)(),
                                    !check
                                        || (check = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                          calculateCanReachUsingCachedAreaLogic,
                                                DAT_PathFindingState::ptr)(
                                                DAT_UnitsState::instance.units[targetUnitID].tile,
                                                DAT_UnitsState::instance.units[id].tile),
                                            !check))) {
                                attackRange = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasNoRangedUnits, DAT_UnitsState::ptr)();
                                attackRange = (-(uint)(attackRange) & 0xfffff49b) + 2916;
                            }
                            break;
                        case Map::Units::UT_S_CATAPULT:
                            attackRange = 5625;
                            break;
                        case Map::Units::UT_S_TREBUCHET:
                        case Map::Units::UT_S_BALLISTA:
                            attackRange = 7225;
                            break;
                        case Map::Units::UT_S_MANGONEL:
                            attackRange = 4900;
                            break;
                        case Map::Units::UT_A_SLINGER:
                            attackRange = 484;
                            break;
                        case Map::Units::UT_A_FIRETHROWER:
                            attackRange = 121;
                        }
                        dy = (int)DAT_UnitsState::instance.units[id].y
                            - (int)DAT_UnitsState::instance.units[targetUnitID].y;
                        dx2 = (int)DAT_UnitsState::instance.units[id].x
                            - (int)DAT_UnitsState::instance.units[targetUnitID].x;
                        // Check if unit under mouse is in range to be attacked
                        if (dx2 * dx2 + dy * dy <= attackRange) {
                            if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                                    DAT_UnitsState::ptr)()) {
                                DAT_TileMapState::instance.pendingUnitCommand = 11;
                            } else {
                                lordMayAct = 1;
                                DAT_TileMapState::instance.pendingUnitCommand = 10;
                            }
                            DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                            DAT_TileMapState::instance.cursorOverlayGmID = 107;
                            DAT_TileMapState::instance.uiSelectedUnitIDUnk = targetUnitID;
                            DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated
                                = DAT_UnitsState::instance.units[targetUnitID].uid;
                            DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                            cursorState = 2;
                            goto checkLordCursor;
                        }
                    }
                } else {
                    targetUnitID
                        = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(2);
                    if (targetUnitID && !DAT_MinimapViewState::instance.minimapClickEnabled
                        && MACRO_CALL(UI::Helpers_Func::SomeUnitAndViewportCheck)(targetUnitID)) {
                        DAT_TileMapState::instance.instructionTargetUnitID = targetUnitID;
                        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                                DAT_UnitsState::ptr)(targetUnitID)
                            && MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)()) {
                            targetArea = (short)DAT_TileMapState::instance
                                             .PathConnectionLayer[DAT_UnitsState::instance.units[targetUnitID].tile];
                            id = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                            id = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                (dword)targetArea,
                                (dword)((int)((short)DAT_TileMapState::instance
                                        .PathConnectionLayer[DAT_UnitsState::instance.units[id].tile])),
                                1);
                            if (id) {
                                DAT_TileMapState::instance.pendingUnitCommand = 3;
                                DAT_TileMapState::instance.cursorOverlayImageBase = -3;
                                DAT_UnitsState::instance.units[targetUnitID].field_0x6c = 2;
                                cursorState = -1;
                                goto checkLordCursor;
                            }
                        } else {
                            manningCount = DAT_UnitsState::instance.units[targetUnitID]
                                               .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                            if ((manningCount) && (DAT_UnitsState::instance.units[targetUnitID].isSelected != 0)) {
                                int noneArriving = 1;
                                if (0 < manningCount) {
                                    id = (int)DAT_UnitsState::instance.units[targetUnitID]
                                             .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                                    manningEngineer = DAT_UnitsState::instance.units[targetUnitID].manningEngineerRef;
                                    do {
                                        if (DAT_UnitsState::instance.units[*manningEngineer].state.generic
                                            == Map::Units::States::US_JESTER_ROAM_TO) {
                                            noneArriving = 0;
                                        }
                                        ++manningEngineer;
                                        --id;
                                    } while (id);
                                    if (!noneArriving)
                                        goto moveToTile;
                                }
                                DAT_TileMapState::instance.pendingUnitCommand = 4;
                                DAT_TileMapState::instance.cursorOverlayImageBase = -4;
                                DAT_UnitsState::instance.units[targetUnitID].field_0x6c = 3;
                                cursorState = -1;
                                goto checkLordCursor;
                            }
                        }
                    } else {
                        if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                            && (DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID)) {
                            switch (DAT_BuildingsState::instance
                                    .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                                    .buildingType) {
                            case Map::Buildings::BT_MANORHOUSE:
                            case Map::Buildings::BT_STONEKEEP:
                            case Map::Buildings::BT_STRONGHOLD:
                            case Map::Buildings::BT_KEEPFOUR:
                            case Map::Buildings::BT_KEEPFIVE:
                            case Map::Buildings::BT_GATEHOUSELARGE:
                            case Map::Buildings::BT_GATEHOUSESMALL:
                            case Map::Buildings::BT_WOODGATE1:
                            case Map::Buildings::BT_TOWER1:
                            case Map::Buildings::BT_TOWER2:
                            case Map::Buildings::BT_TOWER3:
                            case Map::Buildings::BT_TOWER4:
                            case Map::Buildings::BT_TOWER5:
                                break;
                            default:
                                buildingTarget = true;
                                goto buildingUnderMouse;
                            }
                        }
                        do {
                            if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                                    DAT_UnitsState::ptr)()) {
                                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(50, 50);
                            } else {
                                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(30, 30);
                            }
                            targetUnitID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(1);
                            if (!targetUnitID || !MACRO_CALL(UI::Helpers_Func::SomeUnitAndViewportCheck)(targetUnitID)
                                || (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                        DAT_UnitsState::ptr)()
                                    && !MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                                        DAT_UnitsState::ptr)(targetUnitID))) {
                                if ((!DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID)
                                    || (buildingTarget)) {
                                hitBoxLoopDone:
                                    if (cursorState == -2)
                                        goto wallTarget;
                                    break;
                                }
                            buildingUnderMouse:
                                id = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
                                combatUnitID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                                targetUnitID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::getFirstSelectedSiegeEngineID, DAT_UnitsState::ptr)();
                                if (!targetUnitID) {
                                    targetUnitID = MACRO_CALL_MEMBER(
                                        Map::Buildings::BuildingsState_Func::isBuildingPathBlockerOrDamageable,
                                        DAT_BuildingsState::ptr)(id, DAT_UnitsState::instance.units[combatUnitID].tile);
                                    if (targetUnitID
                                        || (check = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                                                DAT_BuildingsState::ptr)(
                                                id, DAT_UnitsState::instance.units[combatUnitID].tile),
                                            check
                                                && (attackRange
                                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::
                                                                            selectionHasMixedAssaultAndInfantry,
                                                        DAT_UnitsState::ptr)(),
                                                    attackRange != 0)))
                                        goto attackableBuilding;
                                } else {
                                attackableBuilding:
                                    if ((DAT_BuildingsState::instance.buildings[id].buildingType
                                            != Map::Buildings::BT_KILLINGPIT)
                                        && (attackRange = MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::selectionHasShieldOrSiegeTower,
                                                DAT_UnitsState::ptr)(),
                                            attackRange == 0)) {
                                        check = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins,
                                            DAT_UnitsState::ptr)();
                                        if (check) {
                                            switch (DAT_BuildingsState::instance.buildings[id].buildingType) {
                                            case Map::Buildings::BT_GATEHOUSELARGE:
                                            case Map::Buildings::BT_GATEHOUSESMALL:
                                            case Map::Buildings::BT_WOODGATE1:
                                            case Map::Buildings::BT_WOODGATE2:
                                            case Map::Buildings::BT_TOWER1:
                                            case Map::Buildings::BT_TOWER2:
                                            case Map::Buildings::BT_TOWER3:
                                            case Map::Buildings::BT_TOWER4:
                                            case Map::Buildings::BT_TOWER5:
                                                check = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                              calculateCanReachUsingCachedAreaLogic,
                                                    DAT_PathFindingState::ptr)(
                                                    DAT_ViewportRenderState::instance.viewportState.cursorTile,
                                                    DAT_UnitsState::instance.units[combatUnitID].tile);
                                                if (check)
                                                    goto moveToTile;
                                            }
                                        }
                                        if ((DAT_GameState::instance.mapAndTime
                                                    .playerTeams[DAT_BuildingsState::instance.buildings[id].owner]
                                                == DAT_GameState::instance.mapAndTime
                                                    .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])
                                            || (check = MACRO_CALL_MEMBER(
                                                    Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                                    DAT_UnitsState::ptr)(),
                                                check)) {
                                            check
                                                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasEngineers,
                                                    DAT_UnitsState::ptr)();
                                            if (check
                                                && (int)DAT_BuildingsState::instance.buildings[id].owner
                                                    == DAT_GameSynchronyState::instance.currentPlayerSlotID
                                                && !DAT_MinimapViewState::instance.minimapClickEnabled
                                                && (buildingType
                                                    = DAT_BuildingsState::instance.buildings[id].buildingType,
                                                    buildingType == Map::Buildings::BT_CATAPULT
                                                        || (((((buildingType == Map::Buildings::BT_FIREBALLISTA
                                                                   || (buildingType == Map::Buildings::BT_TREBUCHET))
                                                                  || (buildingType == Map::Buildings::BT_BATTERINGRAM))
                                                                 || ((buildingType == Map::Buildings::BT_SIEGETOWER
                                                                     || (buildingType == Map::Buildings::BT_SHIELD))))
                                                            || (buildingType == Map::Buildings::BT_OILSMELTER))))) {
                                                DAT_BuildingsState::instance.buildings[id].targetMarker
                                                    = OpenSHC::Map::Buildings::Enums::BTM_ENGINEER_TARGET;
                                                DAT_TileMapState::instance.pendingUnitCommand = 2;
                                                DAT_TileMapState::instance.cursorOverlayImageBase = -2;
                                                cursorState = -1;
                                            }
                                        } else {
                                        buildingAttackRange:
                                            unitType = DAT_UnitsState::instance.units[combatUnitID].unitType;
                                            attackRange = 0;
                                            switch (unitType) {
                                            case Map::Units::UT_E_ARCHER:
                                            case Map::Units::UT_E_XBOW:
                                            case Map::Units::UT_A_ARCHER:
                                            case Map::Units::UT_A_HARCHER:
                                                attackRange = 2916;
                                                switch (DAT_BuildingsState::instance.buildings[id].buildingType) {
                                                case Map::Buildings::BT_GATEHOUSELARGE:
                                                case Map::Buildings::BT_GATEHOUSESMALL:
                                                case Map::Buildings::BT_WOODGATE1:
                                                case Map::Buildings::BT_WOODGATE2:
                                                case Map::Buildings::BT_TOWER1:
                                                case Map::Buildings::BT_TOWER2:
                                                case Map::Buildings::BT_TOWER3:
                                                case Map::Buildings::BT_TOWER4:
                                                case Map::Buildings::BT_TOWER5:
                                                buildingRangeGateOrTower:
                                                    attackRange = -1;
                                                    if (DAT_UnitsState::instance.unitControlsRelated == 5)
                                                        goto buildingRangeDefault;
                                                }
                                                break;
                                            default:
                                            buildingRangeDefault:
                                                if (DAT_GameSynchronyState::instance.currentGameMode
                                                        == Game::GM_SOLITARY
                                                    || !DAT_GameState::instance.mapAndTime.skirmishStrongWalls
                                                    || unitType == Map::Units::UT_S_BATTERINGRAM
                                                    || 4 < (int)(short)DAT_BuildingsState::instance.buildings[id]
                                                                .buildingType
                                                            - 0x4aU) {
                                                    if (attackRange != -1) {
                                                        attackRange = 100000000;
                                                        dy = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                                                   canUnitReachBuildingPerimeter,
                                                            DAT_BuildingsState::ptr)(id, combatUnitID);
                                                        if (!dy) {
                                                            attackRange = MACRO_CALL_MEMBER(
                                                                Map::Units::UnitsState_Func::selectionHasNoRangedUnits,
                                                                DAT_UnitsState::ptr)();
                                                            attackRange = (-(uint)(attackRange) & 0xfffff49b) + 2916;
                                                        }
                                                    }
                                                } else {
                                                    attackRange = -1;
                                                    siegeUnitSelectedUnk = TRUE;
                                                }
                                                break;
                                            case Map::Units::UT_S_CATAPULT:
                                                attackRange = 5625;
                                                break;
                                            case Map::Units::UT_S_TREBUCHET:
                                                attackRange = 7225;
                                                break;
                                            case Map::Units::UT_S_MANGONEL:
                                                attackRange = 4900;
                                                break;
                                            case Map::Units::UT_S_BALLISTA:
                                                attackRange = 7225;
                                                switch (DAT_BuildingsState::instance.buildings[id].buildingType) {
                                                case Map::Buildings::BT_GATEHOUSELARGE:
                                                case Map::Buildings::BT_GATEHOUSESMALL:
                                                case Map::Buildings::BT_WOODGATE1:
                                                case Map::Buildings::BT_WOODGATE2:
                                                case Map::Buildings::BT_TOWER1:
                                                case Map::Buildings::BT_TOWER2:
                                                case Map::Buildings::BT_TOWER3:
                                                case Map::Buildings::BT_TOWER4:
                                                case Map::Buildings::BT_TOWER5:
                                                buildingRangeGateOrTowerBallista:
                                                    attackRange = -1;
                                                }
                                                break;
                                            case Map::Units::UT_A_SLINGER:
                                                attackRange = 484;
                                                switch (DAT_BuildingsState::instance.buildings[id].buildingType) {
                                                case Map::Buildings::BT_GATEHOUSELARGE:
                                                case Map::Buildings::BT_GATEHOUSESMALL:
                                                case Map::Buildings::BT_WOODGATE1:
                                                case Map::Buildings::BT_WOODGATE2:
                                                case Map::Buildings::BT_TOWER1:
                                                case Map::Buildings::BT_TOWER2:
                                                case Map::Buildings::BT_TOWER3:
                                                case Map::Buildings::BT_TOWER4:
                                                case Map::Buildings::BT_TOWER5:
                                                    goto buildingRangeGateOrTower;
                                                }
                                                break;
                                            case Map::Units::UT_A_FIRETHROWER:
                                                attackRange = 121;
                                                switch (DAT_BuildingsState::instance.buildings[id].buildingType) {
                                                case Map::Buildings::BT_GATEHOUSELARGE:
                                                case Map::Buildings::BT_GATEHOUSESMALL:
                                                case Map::Buildings::BT_WOODGATE1:
                                                case Map::Buildings::BT_WOODGATE2:
                                                case Map::Buildings::BT_TOWER1:
                                                case Map::Buildings::BT_TOWER2:
                                                case Map::Buildings::BT_TOWER3:
                                                case Map::Buildings::BT_TOWER4:
                                                case Map::Buildings::BT_TOWER5:
                                                    goto buildingRangeGateOrTower;
                                                }
                                                break;
                                            case Map::Units::UT_S_FBALLISTA:
                                                attackRange = 2916;
                                                switch (DAT_BuildingsState::instance.buildings[id].buildingType) {
                                                case Map::Buildings::BT_GATEHOUSELARGE:
                                                case Map::Buildings::BT_GATEHOUSESMALL:
                                                case Map::Buildings::BT_WOODGATE1:
                                                case Map::Buildings::BT_WOODGATE2:
                                                case Map::Buildings::BT_TOWER1:
                                                case Map::Buildings::BT_TOWER2:
                                                case Map::Buildings::BT_TOWER3:
                                                case Map::Buildings::BT_TOWER4:
                                                case Map::Buildings::BT_TOWER5:
                                                    goto buildingRangeGateOrTowerBallista;
                                                }
                                            }
                                            if ((DAT_BuildingsState::instance.buildings[id].buildingType
                                                    == Map::Buildings::BT_PITCHDITCH)
                                                && (check = MACRO_CALL_MEMBER(
                                                        Map::Units::UnitsState_Func::selectionHasArchers,
                                                        DAT_UnitsState::ptr)(),
                                                    !check)) {
                                                attackRange = -1;
                                            }
                                            if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
                                                && DAT_GameSynchronyState::instance.currentGameMode
                                                    != Game::GM_SKIRMISH_SINGLE_PLAYER
                                                && DAT_GameSynchronyState::instance.currentGameMode
                                                    != Game::GM_SOLITARY) {
                                                attackRange = -1;
                                            }
                                            dy = (int)(short)DAT_BuildingsState::instance.buildings[id].y
                                                - (int)DAT_UnitsState::instance.units[combatUnitID].y;
                                            id = (int)(short)DAT_BuildingsState::instance.buildings[id].x
                                                - (int)DAT_UnitsState::instance.units[combatUnitID].x;
                                            if (attackRange < id * id + dy * dy) {
                                                if (attackGround)
                                                    goto groundAttackRange;
                                            } else {
                                                lordMayAct = 1;
                                                DAT_TileMapState::instance.pendingUnitCommand = 1;
                                                DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                                DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                                                cursorState = 2;
                                                DAT_TileMapState::instance.cursorOverlayGmID = 107;
                                            }
                                        }
                                    }
                                }
                            } else {
                                targetArea
                                    = (short)DAT_TileMapState::instance
                                          .PathConnectionLayer[DAT_UnitsState::instance.units[targetUnitID].tile];
                                id = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                                selectionArea = (short)DAT_TileMapState::instance
                                                    .PathConnectionLayer[DAT_UnitsState::instance.units[id].tile];
                                check = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                                    DAT_UnitsState::ptr)(targetUnitID);
                                if (check) {
                                    id = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                               calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                        (dword)targetArea, (dword)selectionArea, 1);
                                    if (!id)
                                        goto moveToTile;
                                    DAT_TileMapState::instance.pendingUnitCommand = 3;
                                    DAT_TileMapState::instance.cursorOverlayImageBase = -3;
                                    DAT_UnitsState::instance.units[targetUnitID].field_0x6c = 2;
                                    DAT_TileMapState::instance.instructionTargetUnitID = targetUnitID;
                                    cursorState = -1;
                                    goto checkLordCursor;
                                }
                                attackRange = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasShieldOrSiegeMobileUnits,
                                    DAT_UnitsState::ptr)();
                                if (attackRange)
                                    goto moveToTile;
                                switch (DAT_UnitsState::instance.units[id].unitType) {
                                case Map::Units::UT_E_ARCHER:
                                case Map::Units::UT_E_XBOW:
                                case Map::Units::UT_A_ARCHER:
                                case Map::Units::UT_A_HARCHER:
                                case Map::Units::UT_S_FBALLISTA:
                                    attackRange = 2916;
                                    break;
                                default:
                                    attackRange = 100000000;
                                    dy = MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
                                    dy = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                               calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[id].owner,
                                        (dword)targetArea, (dword)selectionArea, dy);
                                    if (!dy
                                        && (check = MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins,
                                                DAT_UnitsState::ptr)(),
                                            !check
                                                || (check = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                                  calculateCanReachUsingCachedAreaLogic,
                                                        DAT_PathFindingState::ptr)(
                                                        DAT_UnitsState::instance.units[targetUnitID].tile,
                                                        DAT_UnitsState::instance.units[id].tile),
                                                    !check))) {
                                        attackRange
                                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasNoRangedUnits,
                                                DAT_UnitsState::ptr)();
                                        // -1 when no selected unit has a ranged attack, else 2916, as a mask: as a
                                        // conditional it loses the match
                                        attackRange = (-(uint)(attackRange) & 0xfffff49b) + 2916;
                                    }
                                    break;
                                case Map::Units::UT_S_CATAPULT:
                                    attackRange = 5625;
                                    break;
                                case Map::Units::UT_S_TREBUCHET:
                                case Map::Units::UT_S_BALLISTA:
                                    attackRange = 7225;
                                    break;
                                case Map::Units::UT_S_MANGONEL:
                                    attackRange = 4900;
                                    break;
                                case Map::Units::UT_A_SLINGER:
                                    attackRange = 484;
                                    break;
                                case Map::Units::UT_A_FIRETHROWER:
                                    attackRange = 121;
                                }
                                dy = (int)DAT_UnitsState::instance.units[id].y
                                    - (int)DAT_UnitsState::instance.units[targetUnitID].y;
                                dx = (int)DAT_UnitsState::instance.units[id].x
                                    - (int)DAT_UnitsState::instance.units[targetUnitID].x;
                                if (attackRange < dx * dx + dy * dy)
                                    goto moveToTile;
                                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                                        DAT_UnitsState::ptr)()) {
                                    DAT_TileMapState::instance.pendingUnitCommand = 11;
                                } else {
                                    lordMayAct = 1;
                                    DAT_TileMapState::instance.pendingUnitCommand = 10;
                                }
                                DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                                DAT_TileMapState::instance.cursorOverlayGmID = 107;
                                DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                DAT_TileMapState::instance.uiSelectedUnitIDUnk = targetUnitID;
                                DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated
                                    = DAT_UnitsState::instance.units[targetUnitID].uid;
                                cursorState = 2;
                                goto checkLordCursor;
                            }
                            if (!buildingTarget)
                                goto hitBoxLoopDone;
                        } while (cursorState == -2);
                        if (cursorState == -1) {
                            if (!moatCommand)
                                goto checkLordCursor;
                        wallTarget:
                            if (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                                && (DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                            .viewportState.mouseAtomRefFloorTile]
                                    & 0x10000300U)
                                && (check
                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                        DAT_UnitsState::ptr)(),
                                    !check
                                        && (!(DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                                      .viewportState.mouseAtomRefFloorTile]
                                            & 2)))) {
                                targetArea = (short)DAT_TileMapState::instance
                                                 .PathConnectionLayer[DAT_ViewportRenderState::instance.viewportState
                                                         .mouseAtomRefFloorTile];
                                combatUnitID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                                selectionArea
                                    = (short)DAT_TileMapState::instance
                                          .PathConnectionLayer[DAT_UnitsState::instance.units[combatUnitID].tile];
                                targetUnitID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::getFirstSelectedLadderUnitID, DAT_UnitsState::ptr)();
                                if (!targetUnitID) {
                                    if (DAT_UnitsState::instance.units[combatUnitID].unitType
                                        != Map::Units::UT_S_TOWER) {
                                        id = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::checkAnySelectedUnitCannotClimb,
                                            DAT_UnitsState::ptr)();
                                        if (!id) {
                                            unitType = DAT_UnitsState::instance.units[combatUnitID].unitType;
                                            if ((((unitType == Map::Units::UT_S_BATTERINGRAM)
                                                     || (unitType == Map::Units::UT_S_CATAPULT))
                                                    || ((unitType == Map::Units::UT_S_TREBUCHET
                                                        || (((unitType == Map::Units::UT_E_KNIGHT
                                                                 || (unitType == Map::Units::UT_S_TOWER))
                                                            || (id = MACRO_CALL_MEMBER(
                                                                    Map::Navigation::PathFindingState_Func::
                                                                        calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                                    DAT_PathFindingState::ptr)(
                                                                    DAT_GameSynchronyState::instance
                                                                        .currentPlayerSlotID,
                                                                    (dword)targetArea, (dword)selectionArea, 0),
                                                                id == 0))))))
                                                && (id = MACRO_CALL_MEMBER(
                                                        Map::Units::UnitsState_Func::selectionContainsShieldmenOnly,
                                                        DAT_UnitsState::ptr)(),
                                                    id == 0
                                                        && ((DAT_TileMapState::instance
                                                                    .WallOwnerLayer[DAT_ViewportRenderState::instance
                                                                            .viewportState.mouseAtomRefFloorTile]
                                                                & 7)
                                                                + 1
                                                            != DAT_GameSynchronyState::instance.currentPlayerSlotID))) {
                                                unitType = DAT_UnitsState::instance.units[combatUnitID].unitType;
                                                switch (unitType) {
                                                case Map::Units::UT_E_ARCHER:
                                                case Map::Units::UT_E_XBOW:
                                                case Map::Units::UT_A_ARCHER:
                                                case Map::Units::UT_A_SLINGER:
                                                case Map::Units::UT_A_HARCHER:
                                                case Map::Units::UT_A_FIRETHROWER:
                                                    id = -1;
                                                    if (DAT_UnitsState::instance.unitControlsRelated == 5)
                                                        goto wallRangeDefault;
                                                    break;
                                                default:
                                                wallRangeDefault:
                                                    if (DAT_GameSynchronyState::instance.currentGameMode
                                                            == Game::GM_SOLITARY
                                                        || DAT_GameState::instance.mapAndTime.skirmishStrongWalls == 0
                                                        || unitType == Map::Units::UT_S_BATTERINGRAM)
                                                        goto wallRangeReach;
                                                    id = -1;
                                                    siegeUnitSelectedUnk = TRUE;
                                                    break;
                                                case Map::Units::UT_S_CATAPULT:
                                                    id = 5625;
                                                    break;
                                                case Map::Units::UT_S_TREBUCHET:
                                                    id = 7225;
                                                    break;
                                                case Map::Units::UT_S_MANGONEL:
                                                    id = 4900;
                                                    break;
                                                case Map::Units::UT_S_TOWER:
                                                wallRangeReach:
                                                    id = 100000000;
                                                    attackRange = MACRO_CALL_MEMBER(
                                                        Map::Buildings::BuildingsState_Func::canUnitReachAdjacentTile,
                                                        DAT_BuildingsState::ptr)(
                                                        DAT_ViewportRenderState::instance.viewportState
                                                            .mouseAtomRefFloorTile,
                                                        combatUnitID);
                                                    if (!attackRange) {
                                                        id = MACRO_CALL_MEMBER(
                                                            Map::Units::UnitsState_Func::selectionHasNoRangedUnits,
                                                            DAT_UnitsState::ptr)();
                                                        id = (-(uint)(id) & 0xfffff49b) + 2916;
                                                    }
                                                    break;
                                                case Map::Units::UT_S_BALLISTA:
                                                case Map::Units::UT_S_FBALLISTA:
                                                    id = -1;
                                                }
                                                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
                                                    && DAT_GameSynchronyState::instance.currentGameMode
                                                        != Game::GM_SKIRMISH_SINGLE_PLAYER
                                                    && DAT_GameSynchronyState::instance.currentGameMode
                                                        != Game::GM_SOLITARY) {
                                                    id = -1;
                                                }
                                                dy = (DAT_ViewportRenderState::instance.viewportState
                                                             .mouseAtomRefFloorTile
                                                         - DAT_ViewportRenderState::instance
                                                             .translationMatrix[DAT_ViewportRenderState::instance
                                                                     .tileTranslationMatrix_YComponent
                                                                         [DAT_ViewportRenderState::instance
                                                                                 .viewportState.mouseAtomRefFloorTile]]
                                                             .addXgetTile)
                                                    - (int)DAT_UnitsState::instance.units[combatUnitID].x;
                                                attackRange
                                                    = (int)DAT_ViewportRenderState::instance
                                                          .tileTranslationMatrix_YComponent[DAT_ViewportRenderState::
                                                                  instance.viewportState.mouseAtomRefFloorTile]
                                                    - (int)DAT_UnitsState::instance.units[combatUnitID].y;
                                                if (attackRange * attackRange + dy * dy <= id) {
                                                    lordMayAct = 1;
                                                    DAT_TileMapState::instance.pendingUnitCommand = 6;
                                                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                                                    DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                                    cursorState = 2;
                                                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                                                    goto checkLordCursor;
                                                }
                                            }
                                        } else {
                                            id = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                       calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                DAT_PathFindingState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID, (dword)targetArea,
                                                (dword)selectionArea, 1);
                                            if (!id
                                                && (DAT_TileMapState::instance
                                                           .WallOwnerLayer[DAT_ViewportRenderState::instance
                                                                   .viewportState.mouseAtomRefFloorTile]
                                                       & 7)
                                                        + 1
                                                    != DAT_GameSynchronyState::instance.currentPlayerSlotID)
                                                goto wallAttackRange;
                                        }
                                        goto moveToTile;
                                    }
                                    targetUnitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::findFreeTileNearby,
                                        DAT_UnitsState::ptr)(combatUnitID,
                                        (uint)(DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile));
                                    if (targetUnitID) {
                                        DAT_TileMapState::instance.pendingUnitCommand = 6;
                                        DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                                        DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                        cursorState = 2;
                                        DAT_TileMapState::instance.cursorOverlayGmID = 107;
                                        goto checkLordCursor;
                                    }
                                    goto noEntryCursor;
                                }
                                if ((DAT_TileMapState::instance.WallOwnerLayer[DAT_ViewportRenderState::instance
                                             .viewportState.mouseAtomRefFloorTile]
                                        & 7)
                                        + 1
                                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                                    DAT_TileMapState::instance.pendingUnitCommand = 5;
                                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                                    cursorState = 2;
                                    DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                    goto checkLordCursor;
                                }
                            }
                        }
                    }
                }
            moveToTile:
                if ((cursorState != -2) || (DAT_MouseState::instance.selectionBoxMode))
                    goto checkLordCursor;
                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                targetUnitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(5);
                if (targetUnitID) {
                    if (DAT_UnitsState::instance.units[targetUnitID].isSelected == 0) {
                        cursorState = 0;
                        goto checkLordCursor;
                    }
                    if (targetUnitID == DAT_UnitsState::instance.someSelectedUnitID
                        && (clickTime = timeGetTime(),
                            clickTime - DAT_UnitsState::instance.timePreviousDoubleClick < 500)
                        && DAT_MouseState::instance.leftClickStart) {
                        DAT_00b98424::instance = 0;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectAllUnitsOfTypeForPlayer,
                            DAT_UnitsState::ptr)((int)DAT_UnitsState::instance.units[targetUnitID].owner,
                            (int)((short)DAT_UnitsState::instance.units[targetUnitID].unitType));
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::createTribeFromSelectedUnits, DAT_UnitsState::ptr)();
                        DAT_UnitsState::instance.someSelectedUnitID = 0;
                        return;
                    }
                }
                if (!DAT_ViewportRenderState::instance.viewportState.cursorTile)
                    goto noEntryCursor;
                secondPass = 0;
                // at most two passes: the second moves the cursor to the campground, when a lord is selected,
                // nothing can reach the cursor tile and that tile is a manor house
                while (true) {
                    int const blocked = DAT_TileMapState::instance
                                            .LogicLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile]
                        & 0x10000100;
                    targetArea = (short)DAT_TileMapState::instance
                                     .PathConnectionLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile];
                    canReach = 0;
                    canMove = 1;
                    id = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    if (0 < id) {
                        attackRange = DAT_UnitsState::instance.units[id].tile;
                        toArea = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer[attackRange];
                        if ((DAT_TileMapState::instance.LogicLayer[attackRange] & 0x40000000U)) {
                            toArea = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[id].owner,
                                (dword)targetArea, (uint)(DAT_UnitsState::instance.units[id].x),
                                (uint)(DAT_UnitsState::instance.units[id].y));
                        }
                        attackRange
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
                        if (MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                (dword)targetArea, (dword)((int)(toArea)), attackRange)) {
                            canReach = 1;
                        }
                    }
                    if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::isTowerTileOvercrowdedByCurrentPlayer,
                            DAT_UnitsState::ptr)(DAT_ViewportRenderState::instance.viewportState.cursorTile)) {
                        canReach = 0;
                        canMove = 0;
                    }
                    if (!MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionHasMovableNonSiegeUnit, DAT_UnitsState::ptr)()) {
                        canReach = 0;
                        canMove = 0;
                    }
                    if (MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionHasMixedAssaultAndInfantry, DAT_UnitsState::ptr)()) {
                        int const mouseTileY = DAT_ViewportRenderState::instance
                                                   .tileTranslationMatrix_YComponent[DAT_ViewportRenderState::instance
                                                           .viewportState.mouseAtomRefFloorTile];
                        int const mouseTileX = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                            - DAT_ViewportRenderState::instance.translationMatrix[mouseTileY].addXgetTile;
                        if (blocked
                            || !MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
                                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[id].x,
                                (int)(DAT_UnitsState::instance.units[id].y), mouseTileX, mouseTileY, 100000)) {
                            canReach = 0;
                        }
                    }
                    if (!MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)()
                        || canReach || lordMayAct || secondPass)
                        break;
                    secondPass = 1;
                    if ((DAT_TileMapState::instance
                                .BuildingLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile]
                            == 0)
                        || (DAT_BuildingsState::instance
                                .buildings[DAT_TileMapState::instance
                                        .BuildingLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile]]
                                .buildingType
                            != Map::Buildings::BT_MANORHOUSE))
                        break;
                    DAT_ViewportRenderState::instance.viewportState.cursorTile
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                              .tileEntry;
                    DAT_ViewportRenderState::instance.viewportState.mouseX
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                              .xEntry;
                    DAT_ViewportRenderState::instance.viewportState.mouseY
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                              .yEntry;
                }
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)()
                    && MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculateCanReachUsingCachedAreaLogic,
                        DAT_PathFindingState::ptr)(DAT_ViewportRenderState::instance.viewportState.cursorTile,
                        DAT_UnitsState::instance.units[id].tile)) {
                    canReach = 1;
                }
                if (canReach) {
                    if (DAT_ViewportRenderState::instance.viewportState.field_0x6c == 1) {
                        DAT_TileMapState::instance.pendingUnitCommand = -1;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 181;
                        DAT_TileMapState::instance.cursorOverlayGmID = 172;
                        DAT_TileMapState::instance.flagAnimationDivisor = 16;
                        // MoveTo-Icon under mouse
                        DAT_TileMapState::instance.DAT_SelectionIconType = 1;
                        cursorState = 4;
                    } else {
                        cursorState = 2;
                    }
                } else if (canMove
                    && (DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[id].tile] & 0x10000100U)
                    && MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::someBinaryAlgFunctionPathFinding,
                        DAT_PathFindingState::ptr)(id)
                    && MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findCrossAreaBridgeTileToTarget,
                        DAT_PathFindingState::ptr)(id, (uint)(DAT_ViewportRenderState::instance.viewportState.mouseX),
                        (uint)(DAT_ViewportRenderState::instance.viewportState.mouseY))) {
                    cursorState = 2;
                    goto handleMouseButtons;
                } else {
                    DAT_TileMapState::instance.pendingUnitCommand = -10;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 65;
                    DAT_TileMapState::instance.flagAnimationDivisor = 16;
                    DAT_TileMapState::instance.cursorOverlayGmID = 172;
                    // NoEntry-Icon under mouse
                    DAT_TileMapState::instance.DAT_SelectionIconType = 17;
                    cursorState = 4;
                }
                targetUnitID = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                if (!targetUnitID || !canReach || lordMayAct
                    || (id = (int)DAT_TileMapState::instance
                            .BuildingLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile],
                        id == 0
                            || (buildingType = DAT_BuildingsState::instance.buildings[id].buildingType,
                                (short)buildingType < 40)))
                    goto checkLordCursor;
                if ((short)buildingType < 45) {
                    if ((int)DAT_BuildingsState::instance.buildings[id].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        lordMayAct = 1;
                    }
                    goto checkLordCursor;
                }
                if (buildingType != Map::Buildings::BT_CAMPGROUND || !secondPass
                    || (int)DAT_BuildingsState::instance.buildings[id].owner
                        != DAT_GameSynchronyState::instance.currentPlayerSlotID
                    || (lordMayAct = true, !DAT_MouseState::instance.leftClickStart))
                    goto checkLordCursor;
            } else {
                if (DAT_UnitsState::instance.unitControlsRelated == 20) {
                    targetUnitID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource, DAT_UnitsState::ptr)();
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                    DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                    DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated = 0;
                    cursorState = -1;
                    MACRO_CALL_MEMBER(
                        Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                        DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[targetUnitID].x,
                        (int)(DAT_UnitsState::instance.units[targetUnitID].y),
                        DAT_ViewportRenderState::instance.viewportState.mouseX,
                        DAT_ViewportRenderState::instance.viewportState.mouseY);
                    if (DAT_DirectionAlgorithmState::instance.orientation == 15
                        || (!DAT_ViewportRenderState::instance.viewportState.mouseX
                            && (!DAT_ViewportRenderState::instance.viewportState.mouseY))) {
                        DAT_TileMapState::instance.pendingUnitCommand = -1;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 65;
                        DAT_TileMapState::instance.flagAnimationDivisor = 16;
                        DAT_TileMapState::instance.cursorOverlayGmID = 172;
                        cursorState = 4;
                    } else {
                        carryingEngineerID = (int)((DAT_DirectionAlgorithmState::instance.orientation
                                                       - DAT_TileMapState::instance.mapOrientation)
                                                 + 12)
                            % 8;
                        DAT_UnitsState::instance.units[targetUnitID].field_0x6e = (short)carryingEngineerID + 1;
                    }
                    goto checkLordCursor;
                }
                if (DAT_UnitsState::instance.unitControlsRelated != 5) {
                    if (DAT_UnitsState::instance.unitControlsRelated == 22) {
                        DAT_TileMapState::instance.pendingUnitCommand = -1;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 65;
                        DAT_TileMapState::instance.flagAnimationDivisor = 16;
                        DAT_TileMapState::instance.cursorOverlayGmID = 172;
                        DAT_TileMapState::instance.DAT_SelectionIconType = 17;
                        cursorState = 4;
                        id = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                        switch (DAT_UnitsState::instance.units[id].unitType) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_HARCHER:
                        case Map::Units::UT_S_FBALLISTA:
                            attackRange = 2916;
                            break;
                        default:
                            attackRange = 0;
                            break;
                        case Map::Units::UT_S_CATAPULT:
                            attackRange = 5625;
                            break;
                        case Map::Units::UT_S_TREBUCHET:
                        case Map::Units::UT_S_BALLISTA:
                            attackRange = 7225;
                            break;
                        case Map::Units::UT_S_MANGONEL:
                            attackRange = 4900;
                            break;
                        case Map::Units::UT_A_SLINGER:
                            attackRange = 484;
                            break;
                        case Map::Units::UT_A_FIRETHROWER:
                            attackRange = 121;
                        }
                        dy = DAT_ViewportRenderState::instance.viewportState.mouseX
                            - DAT_UnitsState::instance.units[id].x;
                        id = DAT_ViewportRenderState::instance.viewportState.mouseY
                            - DAT_UnitsState::instance.units[id].y;
                        if (attackRange < id * id + dy * dy)
                            goto checkLordCursor;
                    }
                groundAttackCursor:
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                    DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                    DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                    DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated = 0;
                    cursorState = 2;
                    goto checkLordCursor;
                }
                attackGround = 1;
                combatUnitID = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                id = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
                if (!DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID) {
                    if (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                        && (DAT_TileMapState::instance
                                .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                            & 0x10000300U)
                        && (check = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)(),
                            !check
                                && (!(DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                              .viewportState.mouseAtomRefFloorTile]
                                    & 2)))) {
                    wallAttackRange:
                        unitType = DAT_UnitsState::instance.units[combatUnitID].unitType;
                        switch (unitType) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_SLINGER:
                        case Map::Units::UT_A_HARCHER:
                            id = -1;
                            if (DAT_UnitsState::instance.unitControlsRelated == 5)
                                goto groundWallRangeDefault;
                            break;
                        default:
                        groundWallRangeDefault:
                            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                                || !DAT_GameState::instance.mapAndTime.skirmishStrongWalls
                                || unitType == Map::Units::UT_S_BATTERINGRAM)
                                goto groundWallRangeReach;
                            id = -1;
                            siegeUnitSelectedUnk = TRUE;
                            break;
                        case Map::Units::UT_S_CATAPULT:
                            id = 5625;
                            break;
                        case Map::Units::UT_S_TREBUCHET:
                            id = 7225;
                            break;
                        case Map::Units::UT_S_MANGONEL:
                            id = 4900;
                            break;
                        case Map::Units::UT_S_TOWER:
                        groundWallRangeReach:
                            id = 100000000;
                            attackRange = MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::canUnitReachAdjacentTile, DAT_BuildingsState::ptr)(
                                DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile, combatUnitID);
                            if (!attackRange) {
                                id = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasNoRangedUnits, DAT_UnitsState::ptr)();
                                id = (-(uint)(id) & 0xfffff49b) + 2916;
                            }
                            break;
                        case Map::Units::UT_S_BALLISTA:
                        case Map::Units::UT_A_FIRETHROWER:
                        case Map::Units::UT_S_FBALLISTA:
                            id = -1;
                        }
                        if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
                            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            id = -1;
                        }
                        dy = (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                                 - DAT_ViewportRenderState::instance
                                     .translationMatrix[DAT_ViewportRenderState::instance
                                             .tileTranslationMatrix_YComponent[DAT_ViewportRenderState::instance
                                                     .viewportState.mouseAtomRefFloorTile]]
                                     .addXgetTile)
                            - (int)DAT_UnitsState::instance.units[combatUnitID].x;
                        attackRange = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                          [DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                            - (int)DAT_UnitsState::instance.units[combatUnitID].y;
                        if (attackRange * attackRange + dy * dy <= id) {
                            lordMayAct = 1;
                            DAT_TileMapState::instance.pendingUnitCommand = 6;
                            DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                            DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                            cursorState = 2;
                            DAT_TileMapState::instance.cursorOverlayGmID = 107;
                            goto checkLordCursor;
                        }
                        if (!attackGround)
                            goto moveToTile;
                    }
                } else {
                    targetUnitID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getFirstSelectedSiegeEngineID, DAT_UnitsState::ptr)();
                    if (!targetUnitID) {
                        check = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                            DAT_BuildingsState::ptr)(id, DAT_UnitsState::instance.units[combatUnitID].tile);
                        if (!check
                            && (check
                                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                                    DAT_BuildingsState::ptr)(id, DAT_UnitsState::instance.units[combatUnitID].tile),
                                !check
                                    || (attackRange = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::selectionHasMixedAssaultAndInfantry,
                                            DAT_UnitsState::ptr)(),
                                        attackRange == 0)))
                            goto groundAttackRange;
                    }
                    if (DAT_BuildingsState::instance.buildings[id].buildingType != Map::Buildings::BT_KILLINGPIT
                        && (attackRange = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionHasShieldOrSiegeTower, DAT_UnitsState::ptr)(),
                            attackRange == 0
                                && (check
                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                        DAT_UnitsState::ptr)(),
                                    !check)))
                        goto buildingAttackRange;
                }
            groundAttackRange:
                switch (DAT_UnitsState::instance.units[combatUnitID].unitType) {
                case Map::Units::UT_E_ARCHER:
                case Map::Units::UT_E_XBOW:
                case Map::Units::UT_A_ARCHER:
                case Map::Units::UT_A_HARCHER:
                case Map::Units::UT_S_FBALLISTA:
                    attackRange2 = 2916;
                    break;
                default:
                    attackRange2 = 0;
                    break;
                case Map::Units::UT_S_CATAPULT:
                    attackRange2 = 5625;
                    break;
                case Map::Units::UT_S_TREBUCHET:
                case Map::Units::UT_S_BALLISTA:
                    attackRange2 = 7225;
                    break;
                case Map::Units::UT_S_MANGONEL:
                    attackRange2 = 4900;
                    break;
                case Map::Units::UT_A_SLINGER:
                    attackRange2 = 484;
                    break;
                case Map::Units::UT_A_FIRETHROWER:
                    attackRange2 = 121;
                }
                attackRange = DAT_ViewportRenderState::instance.viewportState.mouseX
                    - DAT_UnitsState::instance.units[combatUnitID].x;
                id = DAT_ViewportRenderState::instance.viewportState.mouseY
                    - DAT_UnitsState::instance.units[combatUnitID].y;
                if (id * id + attackRange * attackRange <= attackRange2)
                    goto groundAttackCursor;
            noEntryCursor:
                DAT_TileMapState::instance.pendingUnitCommand = -1;
                DAT_TileMapState::instance.cursorOverlayImageBase = 65;
                DAT_TileMapState::instance.flagAnimationDivisor = 16;
                DAT_TileMapState::instance.cursorOverlayGmID = 172;
                DAT_TileMapState::instance.DAT_SelectionIconType = 17;
                cursorState = 4;
            checkLordCursor:
                targetUnitID = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                if ((targetUnitID) && (!lordMayAct)) {
                    DAT_TileMapState::instance.pendingUnitCommand = -1;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 65;
                    DAT_TileMapState::instance.flagAnimationDivisor = 16;
                    DAT_TileMapState::instance.cursorOverlayGmID = 172;
                    DAT_TileMapState::instance.DAT_SelectionIconType = 17;
                    cursorState = 4;
                }
            handleMouseButtons:
                if (DAT_MouseState::instance.leftClickStart) {
                    DAT_00b98424::instance = 1;
                    if (((!cursorState)
                            || (((cursorState == 2 && (!DAT_TileMapState::instance.cursorOverlayImageBase))
                                && (DAT_UnitsState::instance.unitControlsRelated != 5))))
                        && DAT_TileMapState::instance.pendingUnitCommand != 3
                        && DAT_TileMapState::instance.pendingUnitCommand != 4) {
                        MACRO_CALL_MEMBER(Input::MouseState_Func::beginPointSelectionBox, DAT_MouseState::ptr)();
                        targetUnitID
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(5);
                        if (targetUnitID) {
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectFirstUnitInDragBoxAnyPlayer, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(Input::MouseState_Func::beginPointSelectionBox, DAT_MouseState::ptr)();
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectFirstUnitInDragBoxAnyPlayer, DAT_UnitsState::ptr)();
                            DAT_UnitsState::instance.someSelectedUnitID = -1;
                            if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                                DAT_UnitsState::instance.someSelectedUnitID = 0;
                            }
                            DAT_MouseState::instance.selectionBoxState = 1;
                            MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)();
                            DAT_UnitsState::instance.pendingUnitControlMode = 1;
                            DAT_UnitsState::instance.unitControlsRelated = 1;
                            DAT_TileMapState::instance.pendingUnitCommand = 0;
                            DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                            DAT_TileMapState::instance.cursorOverlayGmID = 107;
                            DAT_TileMapState::instance.shiftRelated0or3 = 0;
                        }
                    }
                    DAT_TileMapState::instance.field_0x554a00 = DAT_ViewportRenderState::instance.viewportState.mouseX;
                    DAT_TileMapState::instance.instructionTargetX
                        = DAT_ViewportRenderState::instance.viewportState.mouseX;
                    DAT_TileMapState::instance.field_0x554a04 = DAT_ViewportRenderState::instance.viewportState.mouseY;
                    DAT_TileMapState::instance.instructionTargetY
                        = DAT_ViewportRenderState::instance.viewportState.mouseY;
                    goto setMouseCursorState;
                }
                if ((DAT_MouseState::instance.leftClickState) && (DAT_00b98424::instance)) {
                    MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                    if ((!DAT_MouseState::instance.selectionBoxMode)
                        || (MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)(),
                            DAT_MouseState::instance.selectionBoxState == 0))
                        goto setMouseCursorState;
                    if (!DAT_ModifierKeyState::instance.shift) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    }
                    DAT_TileMapState::instance.shiftRelated0or3 = DAT_ModifierKeyState::instance.shift ? 3 : 0;
                    DAT_UnitsState::instance.pendingUnitControlMode = 1;
                    DAT_UnitsState::instance.unitControlsRelated = 1;
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    DAT_GameCore::instance.menuSwitchDelay = -1;
                    if (0 < DAT_UnitsState::instance.totalUnitsInSelection
                        && DAT_MouseState::instance.leftClickStartMoment != -1
                        && (int)(now - DAT_MouseState::instance.leftClickStartMoment) <= 200)
                        goto setMouseCursorState;
                    if (DAT_TileMapState::instance.shiftRelated0or3 != 3) {
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::applyDragBoxSelectionByPriority, DAT_UnitsState::ptr)();
                        goto setMouseCursorState;
                    }
                    goto selectDragBoxUnits;
                }
                if ((!DAT_MouseState::instance.draggingStopped)
                    || (attackGround = DAT_00b98424::instance == 0, DAT_00b98424::instance = 0, attackGround))
                    goto setMouseCursorState;
                targetUnitID = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                if ((targetUnitID) && (!lordMayAct)) {
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                    goto setMouseCursorState;
                }
            }
            setRallying = 0;
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
            switch (DAT_UnitsState::instance.unitControlsRelated) {
            case 1:
                if (DAT_TileMapState::instance.pendingUnitCommand == -10) {
                    if (siegeUnitSelectedUnk) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 257, 0, 0, 105, 2000);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                        goto setMouseCursorState;
                    }
                } else {
                    if (DAT_TileMapState::instance.pendingUnitCommand == 11) {
                        DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                        goto engineerTileCommand;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 10) {
                        if ((DAT_TileMapState::instance.uiSelectedUnitIDUnk)
                            && (DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated
                                == DAT_UnitsState::instance.units[DAT_TileMapState::instance.uiSelectedUnitIDUnk]
                                    .uid)) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                                DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                Map::Units::UIT_UNIT_ATTACK_UNIT, DAT_TileMapState::instance.uiSelectedUnitIDUnk,
                                DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated, 0);
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitCombatSpeechForTarget,
                                DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                (int)(DAT_TileMapState::instance.uiSelectedUnitIDUnk));
                        }
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                        DAT_TileMapState::instance.cursorOverlayGmID = 107;
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                        goto setMouseCursorState;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 12) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            Map::Units::UIT_LIGHT_PITCH,
                            (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.somePitchDitchID)),
                            (undefined4)((int)(DAT_TileMapState::instance
                                    .pitchDitches[DAT_ViewportRenderState::instance.viewportState.somePitchDitchID]
                                    .uid)));
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playArcherCommandSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                        goto setMouseCursorState;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 1) {
                        commandType = 9;
                        goto buildingCommand;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 2) {
                        int const buildingID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, buildingID,
                            DAT_BuildingsState::instance.buildings[buildingID].uid);
                        if ((DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                != Map::Buildings::BT_OILSMELTER)
                            || (targetUnitID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)(),
                                targetUnitID == 0))
                            break;
                        if (DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount == 0) {
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(28);
                        } else {
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(29);
                        }
                    } else if (DAT_TileMapState::instance.pendingUnitCommand == 3) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            Map::Units::UIT_MAN_SIEGE_EQUIPMENT, DAT_TileMapState::instance.instructionTargetUnitID,
                            (undefined4)((
                                int)(DAT_UnitsState::instance.units[DAT_TileMapState::instance.instructionTargetUnitID]
                                    .uid)));
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(20);
                    } else if (DAT_TileMapState::instance.pendingUnitCommand == 4) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, DAT_TileMapState::instance.instructionTargetUnitID,
                            (undefined4)((
                                int)(DAT_UnitsState::instance.units[DAT_TileMapState::instance.instructionTargetUnitID]
                                    .uid)),
                            0);
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(22);
                    } else {
                        if (DAT_TileMapState::instance.pendingUnitCommand == 5) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand3Params,
                                DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 24,
                                (undefined4)((
                                    int)(DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile)));
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playWorkCommandSpeech,
                                DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                            goto setMouseCursorState;
                        }
                        if (DAT_TileMapState::instance.pendingUnitCommand == 6) {
                            commandType = 23;
                            goto tileCommand;
                        }
                        if ((DAT_ViewportRenderState::instance.viewportState.field_0x38)
                            && (id = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                                id != 0)) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                                DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                Map::Units::UIT_FILL_MOAT,
                                (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseX)),
                                (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseY)), 1000);
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitSelectSpeech, DAT_TribesState::ptr)(
                                DAT_TribesState::instance.DAT_CurrentTribeID);
                            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                            goto setMouseCursorState;
                        }
                        if ((DAT_ViewportRenderState::instance.viewportState.field_0x40)
                            && (id = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                                id != 0)) {
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                                DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                Map::Units::UIT_DIG_MOAT,
                                (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseX)),
                                (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseY)), 1000);
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitSelectSpeech, DAT_TribesState::ptr)(
                                DAT_TribesState::instance.DAT_CurrentTribeID);
                            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                            goto setMouseCursorState;
                        }
                        if (DAT_ModifierKeyState::instance.shift) {
                            // rallying with the shift key
                            if (DAT_TribesState::instance.patrolButtonPressed) {
                                setRallying = 1;
                                if (DAT_TribesState::instance.rallyCount < 10) {
                                    if (DAT_TribesState::instance.rallyCount == 1) {
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand,
                                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                            DAT_ViewportRenderState::instance.viewportState.mouseX,
                                            DAT_ViewportRenderState::instance.viewportState.mouseY,
                                            (int)(DAT_TribesState::instance.patrolButtonPressed), 1);
                                        ++DAT_TribesState::instance.rallyCount;
                                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                                        goto setMouseCursorState;
                                    }
                                } else {
                                rallyCountCapped:
                                    DAT_TribesState::instance.rallyCount = 9;
                                }
                            } else {
                                if (9 < DAT_TribesState::instance.rallyCount)
                                    goto rallyCountCapped;
                                if (DAT_TribesState::instance.rallyCount == 1) {
                                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand,
                                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                        DAT_ViewportRenderState::instance.viewportState.mouseX,
                                        DAT_ViewportRenderState::instance.viewportState.mouseY, -1, 1);
                                    ++DAT_TribesState::instance.rallyCount;
                                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                                    goto setMouseCursorState;
                                }
                            }
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::extendRallyPoint, DAT_UnitsState::ptr)(
                                DAT_TribesState::instance.DAT_CurrentTribeID,
                                DAT_ViewportRenderState::instance.viewportState.mouseX,
                                DAT_ViewportRenderState::instance.viewportState.mouseY,
                                (int)(DAT_TribesState::instance.rallyCount));
                            ++DAT_TribesState::instance.rallyCount;
                            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                            goto setMouseCursorState;
                        }
                        now = timeGetTime();
                        moveFlags = 1;
                        if (DAT_00b98420::instance == DAT_ViewportRenderState::instance.viewportState.mouseX
                            && DAT_00b9841c::instance == DAT_ViewportRenderState::instance.viewportState.mouseY
                            && (moveFlags = 1, (int)(now - TIME_PreviousClick::instance) < 500)) {
                            moveFlags = 129;
                        }
                        DAT_00b98420::instance = DAT_ViewportRenderState::instance.viewportState.mouseX;
                        DAT_00b9841c::instance = DAT_ViewportRenderState::instance.viewportState.mouseY;
                        TIME_PreviousClick::instance = now;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand, DAT_UnitsState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID,
                            DAT_ViewportRenderState::instance.viewportState.mouseX,
                            DAT_ViewportRenderState::instance.viewportState.mouseY,
                            (int)(DAT_TribesState::instance.patrolButtonPressed), moveFlags);
                        DAT_TribesState::instance.rallyCount = 2;
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                        goto setMouseCursorState;
                    }
                }
                break;
            case 4:
                if (DAT_TileMapState::instance.uiSelectedUnitIDUnk) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                        Map::Units::UIT_UNIT_ATTACK_UNIT, DAT_TileMapState::instance.uiSelectedUnitIDUnk,
                        DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated, 0);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitCombatSpeechForTarget,
                        DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                        (int)(DAT_TileMapState::instance.uiSelectedUnitIDUnk));
                }
                DAT_UnitsState::instance.pendingUnitControlMode = 1;
                DAT_UnitsState::instance.unitControlsRelated = 1;
                DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                DAT_TileMapState::instance.cursorOverlayGmID = 107;
                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                goto setMouseCursorState;
            case 5:
                if (cursorState == 2) {
                    if (DAT_TileMapState::instance.pendingUnitCommand == 6) {
                        commandType = 35;
                    tileCommand:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitMoveSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand3Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            (undefined4)((int)(commandType)),
                            (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile)));
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                        goto setMouseCursorState;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 1) {
                        commandType = 36;
                    buildingCommand:
                        {
                            int const buildingID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                                DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                (Map::Units::UnitInstructionType)commandType, buildingID,
                                DAT_BuildingsState::instance.buildings[buildingID].uid);
                            if (buildingID
                                && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                                    == Map::Buildings::BT_PITCHDITCH) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playArcherCommandSpeech,
                                    DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                            } else {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playAttackCommandFeedback,
                                    DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                            }
                            goto setMouseCursorState;
                        }
                    }
                    DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand, DAT_UnitsState::ptr)(
                        DAT_TribesState::instance.DAT_CurrentTribeID,
                        DAT_ViewportRenderState::instance.viewportState.mouseX,
                        DAT_ViewportRenderState::instance.viewportState.mouseY, 0, 0);
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, Map::Units::UIT_ATTACK_LAND,
                        DAT_TileMapState::instance.instructionTargetX, DAT_TileMapState::instance.instructionTargetY,
                        DAT_TileMapState::instance.field_0x554a08);
                    DAT_UnitsState::instance.pendingUnitControlMode = 1;
                    DAT_UnitsState::instance.unitControlsRelated = 1;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitMoveSpeech, DAT_TribesState::ptr)(
                        DAT_TribesState::instance.DAT_CurrentTribeID);
                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
                    goto setMouseCursorState;
                }
                break;
            case 22:
                if (DAT_TileMapState::instance.pendingUnitCommand != -1) {
                    DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, Map::Units::UIT_THROW_COW,
                        DAT_TileMapState::instance.instructionTargetX, DAT_TileMapState::instance.instructionTargetY,
                        DAT_TileMapState::instance.field_0x554a08);
                    DAT_UnitsState::instance.pendingUnitControlMode = 1;
                    DAT_UnitsState::instance.unitControlsRelated = 1;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    id = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    if ((id)
                        && (DAT_UnitsState::instance.units[id]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 0)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(30);
                        break;
                    }
                }
                break;
            case 20:
                if (cursorState != 3) {
                    DAT_UnitsState::instance.pendingUnitControlMode = 20;
                    DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                engineerTileCommand:
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, Map::Units::UIT_THROW_OIL,
                        (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseX)),
                        (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseY)));
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 107;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(23);
                    break;
                }
                break;
            }
            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(setRallying);
        setMouseCursorState:
            switch (cursorState) {
            case -1:
                DAT_MouseState::instance.field_0x1dc = 0;
                break;
            case 0:
                DAT_MouseState::instance.field_0x1dc = 1;
                break;
            case 1:
                DAT_MouseState::instance.field_0x1dc = 2;
                break;
            case 2:
                DAT_MouseState::instance.field_0x1dc = 3;
                break;
            case 3:
                DAT_MouseState::instance.field_0x1dc = 4;
                break;
            case 4:
                DAT_MouseState::instance.field_0x1dc = 5;
                break;
            }
        }

    }
}
}
