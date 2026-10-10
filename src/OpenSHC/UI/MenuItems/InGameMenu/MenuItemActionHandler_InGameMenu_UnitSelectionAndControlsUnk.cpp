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

        using Commands::GameCommandType;
        using Commands::MappersEnum;
        using Game::GameMode;
        using Game::Player::PlayerData;
        using Map::Buildings::BuildingType;
        using Map::Buildings::BuildingTypeShort;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitType;
        using Map::Units::UnitTypeShort;
        using Map::Units::States::UnitState;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::BuildMenuTabType;
        using UI::Enums::DisplayElementID;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004348D0
        void InGameMenu::MenuItemActionHandler_InGameMenu_UnitSelectionAndControlsUnk(int param_1, ...)
        {
            ushort uVar1;
            ushort uVar2;
            int sVar3;
            UnitTypeShort UVar4;
            BuildingTypeShort BVar5;
            BOOLEnum BVar8;
            uint _clickHitEnemy;
            uint _otherUnitIDUnk;
            uint uVar9;
            short* psVar10;
            int _shooterID;
            int _yDifference;
            int _specificRange2;
            DWORD DVar11;
            BOOLEnum BVar12;
            undefined4 uVar13;
            int _xDifference2;
            int _xDifference;
            int extraout_ECX;
            dword toArea;
            int _specificRange;
            int iVar14;
            bool bVar15;
            bool bVar16;
            bool bVar17;
            bool bVar18;
            int local_20;
            int* local_18;
            int _playerID;
            TextMessageBLLookupStructUnion _noTextExtra;
            undefined4 _setRallying;
            uint flag1003;
            int _oneOr129;
            DWORD DVar7 = timeGetTime();
            local_20 = -2;
            bVar16 = false;
            bVar17 = false;
            bVar18 = false;
            bVar15 = false;
            bool bVar6 = false;
            if (DAT_GameCore::instance.gamePausedLogical) {}
            BVar8 = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
            if (BVar8) {}
            if (DAT_GameSynchronyState::instance.syncStatus) {
                if (!DAT_MouseState::instance.selectionBoxMode) {}
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
            }
            if (DAT_GameSynchronyState::instance.saveRelated) {}
            DAT_MouseState::instance.field68_0x1dc = -1;
            DAT_MouseState::instance.savedSelectionBoxState = DAT_MouseState::instance.selectionBoxState;
            DAT_TileMapState::instance.DAT_SelectionIconType = 0;
            if (0x46 < (int)(DVar7 - DAT_TileMapState::instance.cursorAnimationTime)) {
                DAT_TileMapState::instance.cursorOverlayAnimationFrame
                    = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 1;
                if (0x10 < DAT_TileMapState::instance.cursorOverlayAnimationFrame) {
                    DAT_TileMapState::instance.cursorOverlayAnimationFrame = 1;
                }
                DAT_TileMapState::instance.flagAnimationFrame = DAT_TileMapState::instance.flagAnimationFrame + 1;
                DAT_TileMapState::instance.cursorAnimationTime = DVar7;
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
                    DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                    DAT_UnitsState::instance.unitControlsRelated = TRUE;
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    DAT_TileMapState::instance.shiftRelated0or3 = 1;
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                } else {
                    if (((DAT_UnitsState::instance.totalUnitsInSelection < 1)
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
                        _shooterID = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::createUnitSelection, DAT_UnitsState::ptr)();
                        if (!_shooterID) {}
                        if ((!DAT_UnitsState::instance.field49_0x608)
                            && (DAT_UnitsState::instance.totalUnitsInSelection == 1)) {
                            DAT_UnitsState::instance.field49_0x608 = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                            DAT_UnitsState::instance.field48_0x604 = timeGetTime();
                        }
                        _otherUnitIDUnk
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer,
                                DAT_UnitsState::ptr)();
                        if (!_otherUnitIDUnk) {
                            if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    != UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                                && (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    != UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                                DAT_GameCore::instance.tabTypeSiegeSubset
                                    = DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab;
                            }
                            if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                                || (bVar18 = DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                        == UI::Enums::BASMTT_SIEGETENT_SHIELD,
                                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    = UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM,
                                    bVar18)) {
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                    = UI::Enums::BASMTT_SIEGETENT_SHIELD;
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
                        DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                        DAT_UnitsState::instance.unitControlsRelated = 1;
                        DAT_TileMapState::instance.shiftRelated0or3 = 1;
                        DAT_TileMapState::instance.pendingUnitCommand = 0;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                        DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    }
                }
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 1) {
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::recountUnitsInSelection, DAT_UnitsState::ptr)();
            }
            _shooterID = DAT_BuildingsState::instance.unitID;
            if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .lordKilledByPlayerID
                    != 0)
                && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)) {}
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {}
                if (DAT_GameState::instance.mapAndTime.gameOver
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {}
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 1
                && DAT_UnitsState::instance.unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    < 1
                && DAT_UnitsState::instance.totalUnitsInSelection < 1) {
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
            if ((DAT_BuildingsState::instance.siegeEngineCreationRelated01)
                && (DAT_BuildingsState::instance.siegeEngineCreationRelated01
                    = DAT_BuildingsState::instance.siegeEngineCreationRelated01 + -1,
                    DAT_BuildingsState::instance.siegeEngineCreationRelated01 == 0)) {
                DAT_GameCore::instance.tabTypeSiegeSubset = UI::Enums::BMTT_CASTLE;
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
                DAT_UnitsState::instance.units[_shooterID].isSelected = 1;
                DAT_TileMapState::instance.shiftRelated0or3 = 1;
                DAT_UnitsState::instance.totalUnitsInSelection = 1;
                DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::createUnitSelection, DAT_UnitsState::ptr)();
            }
            if ((!DAT_ViewportRenderState::instance.viewportState.field0_0x0)
                && (!DAT_MinimapViewState::instance.minimapClickEnabled)) {}
            if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_NULL) {}
            if (DAT_MouseState::instance.rightClickStart) {
                if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                    || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                    if (DAT_MinimapViewState::instance.minimapClickEnabled) {}
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                        = DAT_GameCore::instance.tabTypeSiegeSubset;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_BUILD_MENU, 0);
                } else if ((DAT_MinimapViewState::instance.minimapClickEnabled)
                    && (DAT_TileMapState::instance.shiftRelated0or3 == 1)) {
                }
                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                }
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                DAT_TileMapState::instance.shiftRelated0or3 = 0;
            }
            if (!DAT_MinimapViewState::instance.minimapClickEnabled) {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 5) {
                if ((!DAT_MouseState::instance.leftClickStart) && (!DAT_MouseState::instance.leftClickState)) {
                    DAT_TileMapState::instance.shiftRelated0or3 = 4;
                }
                goto LAB_0043782c;
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 == 4) {
                _shooterID = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                 [DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile];
                DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                _specificRange = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                    - DAT_ViewportRenderState::instance.translationMatrix[_shooterID].addXgetTile;
                local_20 = 2;
                DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                bVar18 = false;
                bVar17 = false;
                if (DAT_TileMapState::instance.activeTacticalPower == 6
                    && (DAT_TileMapState::instance
                            .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                        & 0x100U)) {
                LAB_00434f28:
                    bVar18 = true;
                } else {
                    switch (DAT_TileMapState::instance.activeTacticalPower) {
                    case 2:
                    case 3:
                    case 4:
                    case 6:
                    case 0xd:
                    case 0x10:
                        iVar14 = _shooterID
                            - DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .keep.yEntry;
                        _yDifference = _specificRange
                            - DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .keep.xEntry;
                        _yDifference = _yDifference * _yDifference + iVar14 * iVar14;
                        bVar17 = true;
                        if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                            bVar18 = (_yDifference < 0x3100);
                            iVar14 = -0x3100;
                            bVar15 = _yDifference == 0x3100;
                        } else {
                            bVar18 = (_yDifference < 0x9c4);
                            iVar14 = -0x9c4;
                            bVar15 = _yDifference == 0x9c4;
                        }
                        bVar16 = bVar18 == _yDifference + iVar14 < 0;
                        bVar18 = !bVar15 && bVar16;
                        if (!DAT_GameState::instance.mapAndTime.skirmishExtremeMode2) {
                        LAB_00434fbe:
                            if (bVar18)
                                break;
                        } else if (!bVar15 && bVar16) {
                            _yDifference = DAT_GameState::instance
                                               .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                               .lordID;
                            if ((!_yDifference)
                                || (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .lordUID
                                    != DAT_UnitsState::instance.units[_yDifference].uid))
                                goto LAB_00434fbe;
                            iVar14 = _specificRange - DAT_UnitsState::instance.units[_yDifference].x;
                            _yDifference = _shooterID - DAT_UnitsState::instance.units[_yDifference].y;
                            _yDifference = _yDifference * _yDifference + iVar14 * iVar14;
                            bVar18 = false;
                            if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                bVar16 = (_yDifference < 0x3100);
                                iVar14 = _yDifference + -0x3100;
                                bVar15 = _yDifference == 0x3100;
                            } else {
                                bVar16 = (_yDifference < 0x9c4);
                                iVar14 = _yDifference + -0x9c4;
                                bVar15 = iVar14 == 0;
                            }
                            if (!bVar15 && bVar16 == iVar14 < 0)
                                goto LAB_00434f28;
                        }
                        _playerID = 1;
                        do {
                            if (0 < DAT_GameState::instance.playerDataArray[_playerID].keep.id
                                && 0 < DAT_GameState::instance.playerDataArray[_playerID].campground.id
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[_playerID]
                                && (_yDifference
                                    = _shooterID - DAT_GameState::instance.playerDataArray[_playerID].keep.yEntry,
                                    iVar14
                                    = _specificRange - DAT_GameState::instance.playerDataArray[_playerID].keep.xEntry,
                                    iVar14 * iVar14 + _yDifference * _yDifference < 0x271)) {
                                if (!DAT_GameState::instance.mapAndTime.skirmishExtremeMode2)
                                    goto LAB_00434f28;
                                _yDifference = DAT_GameState::instance.playerDataArray[_playerID].lordID;
                                if ((_yDifference)
                                    && (DAT_GameState::instance.playerDataArray[_playerID].lordUID
                                        == DAT_UnitsState::instance.units[_yDifference].uid)) {
                                    iVar14 = _specificRange - DAT_UnitsState::instance.units[_yDifference].x;
                                    _yDifference = _shooterID - DAT_UnitsState::instance.units[_yDifference].y;
                                    _yDifference = _yDifference * _yDifference + iVar14 * iVar14;
                                    if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                        bVar16 = (_yDifference < 0x3100);
                                        iVar14 = -0x3100;
                                        bVar15 = _yDifference == 0x3100;
                                    } else {
                                        bVar16 = (_yDifference < 0x9c4);
                                        iVar14 = -0x9c4;
                                        bVar15 = _yDifference == 0x9c4;
                                    }
                                    if (!bVar15 && bVar16 == _yDifference + iVar14 < 0)
                                        goto LAB_00434f28;
                                }
                                if (bVar18)
                                    break;
                            }
                            if (0 < DAT_GameState::instance.playerDataArray[_playerID + 1].keep.id
                                && 0 < DAT_GameState::instance.playerDataArray[_playerID + 1].campground.id
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[_playerID + 1]
                                && (_yDifference
                                    = _shooterID - DAT_GameState::instance.playerDataArray[_playerID + 1].keep.yEntry,
                                    (_specificRange
                                        - DAT_GameState::instance.playerDataArray[_playerID + 1].keep.xEntry)
                                                * (_specificRange
                                                    - DAT_GameState::instance.playerDataArray[_playerID + 1]
                                                        .keep.xEntry)
                                            + _yDifference * _yDifference
                                        < 0x271)) {
                                if (!DAT_GameState::instance.mapAndTime.skirmishExtremeMode2)
                                    goto LAB_00434f28;
                                _yDifference = DAT_GameState::instance.playerDataArray[_playerID + 1].lordID;
                                if ((_yDifference)
                                    && (DAT_GameState::instance.playerDataArray[_playerID + 1].lordUID
                                        == DAT_UnitsState::instance.units[_yDifference].uid)) {
                                    iVar14 = _specificRange - DAT_UnitsState::instance.units[_yDifference].x;
                                    _yDifference = _shooterID - DAT_UnitsState::instance.units[_yDifference].y;
                                    _yDifference = _yDifference * _yDifference + iVar14 * iVar14;
                                    if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                        bVar16 = (_yDifference < 0x3100);
                                        iVar14 = -0x3100;
                                        bVar15 = _yDifference == 0x3100;
                                    } else {
                                        bVar16 = (_yDifference < 0x9c4);
                                        iVar14 = -0x9c4;
                                        bVar15 = _yDifference == 0x9c4;
                                    }
                                    if (!bVar15 && bVar16 == _yDifference + iVar14 < 0)
                                        goto LAB_00434f28;
                                }
                                if (bVar18)
                                    break;
                            }
                            if (0 < DAT_GameState::instance.playerDataArray[_playerID + 2].keep.id
                                && 0 < DAT_GameState::instance.playerDataArray[_playerID + 2].campground.id
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[_playerID + 2]
                                && (_yDifference = _specificRange
                                        - DAT_GameState::instance.playerDataArray[_playerID + 2].keep.xEntry,
                                    _yDifference * _yDifference
                                            + (_shooterID
                                                  - DAT_GameState::instance.playerDataArray[_playerID + 2].keep.yEntry)
                                                * (_shooterID
                                                    - DAT_GameState::instance.playerDataArray[_playerID + 2]
                                                        .keep.yEntry)
                                        < 0x271)) {
                                if (!DAT_GameState::instance.mapAndTime.skirmishExtremeMode2)
                                    goto LAB_00434f28;
                                _yDifference = DAT_GameState::instance.playerDataArray[_playerID + 2].lordID;
                                if ((_yDifference)
                                    && (DAT_GameState::instance.playerDataArray[_playerID + 2].lordUID
                                        == DAT_UnitsState::instance.units[_yDifference].uid)) {
                                    iVar14 = _specificRange - DAT_UnitsState::instance.units[_yDifference].x;
                                    _yDifference = _shooterID - DAT_UnitsState::instance.units[_yDifference].y;
                                    _yDifference = _yDifference * _yDifference + iVar14 * iVar14;
                                    if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                        bVar16 = (_yDifference < 0x3100);
                                        iVar14 = -0x3100;
                                        bVar15 = _yDifference == 0x3100;
                                    } else {
                                        bVar16 = (_yDifference < 0x9c4);
                                        iVar14 = -0x9c4;
                                        bVar15 = _yDifference == 0x9c4;
                                    }
                                    if (!bVar15 && bVar16 == _yDifference + iVar14 < 0)
                                        goto LAB_00434f28;
                                }
                                if (bVar18)
                                    break;
                            }
                            if (0 < DAT_GameState::instance.playerDataArray[_playerID + 3].keep.id
                                && 0 < DAT_GameState::instance.playerDataArray[_playerID + 3].campground.id
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[_playerID + 3]
                                && (_yDifference
                                    = _shooterID - DAT_GameState::instance.playerDataArray[_playerID + 3].keep.yEntry,
                                    iVar14 = _specificRange
                                        - DAT_GameState::instance.playerDataArray[_playerID + 3].keep.xEntry,
                                    iVar14 * iVar14 + _yDifference * _yDifference < 0x271)) {
                                if (!DAT_GameState::instance.mapAndTime.skirmishExtremeMode2)
                                    goto LAB_00434f28;
                                _yDifference = DAT_GameState::instance.playerDataArray[_playerID + 3].lordID;
                                if ((_yDifference)
                                    && (DAT_GameState::instance.playerDataArray[_playerID + 3].lordUID
                                        == DAT_UnitsState::instance.units[_yDifference].uid)) {
                                    iVar14 = _specificRange - DAT_UnitsState::instance.units[_yDifference].x;
                                    _yDifference = _shooterID - DAT_UnitsState::instance.units[_yDifference].y;
                                    _yDifference = _yDifference * _yDifference + iVar14 * iVar14;
                                    if (DAT_TileMapState::instance.activeTacticalPower == 3) {
                                        bVar16 = (_yDifference < 0x3100);
                                        iVar14 = -0x3100;
                                        bVar15 = _yDifference == 0x3100;
                                    } else {
                                        bVar16 = (_yDifference < 0x9c4);
                                        iVar14 = -0x9c4;
                                        bVar15 = _yDifference == 0x9c4;
                                    }
                                    if (!bVar15 && bVar16 == _yDifference + iVar14 < 0)
                                        goto LAB_00434f28;
                                }
                                if (bVar18)
                                    break;
                            }
                            _playerID = _playerID + 4;
                        } while (_playerID < 9);
                    }
                }
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordKilledByPlayerID
                        != 0
                    || bVar18
                    || (((DAT_TileMapState::instance
                                 .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                             & 0x40501481U)
                            || (DAT_TileMapState::instance.PathConnectionLayer[DAT_ViewportRenderState::instance
                                        .viewportState.mouseAtomRefFloorTile]
                                == 0))
                        && (bVar17))) {
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x41;
                    DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                    local_20 = 4;
                } else if (!DAT_MouseState::instance.leftClickStart) {
                    switch (DAT_TileMapState::instance.activeTacticalPower) {
                    case 2:
                    case 4:
                    case 6:
                    case 0xd:
                    case 0x10:
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile, DAT_TileMapState::ptr)(
                            _specificRange, _shooterID, (int)(10));
                        break;
                    case 3:
                    case 5:
                    case 7:
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile, DAT_TileMapState::ptr)(
                            _specificRange, _shooterID, (int)(14));
                        break;
                    default:
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile, DAT_TileMapState::ptr)(
                            _specificRange, _shooterID, (int)(12));
                    }
                } else {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.activeTacticalPower;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_ACTIVATE_TACTICAL_POWERS);
                    DAT_TileMapState::instance.shiftRelated0or3 = 0;
                }
                goto LAB_0043782c;
            }
            if (!DAT_TileMapState::instance.shiftRelated0or3 || DAT_TileMapState::instance.shiftRelated0or3 == 3
                || DAT_TileMapState::instance.shiftRelated0or3 == 2) {
                if (DAT_MouseState::instance.leftClickStart) {
                    BOOLEnum_00b98414::instance = FALSE;
                    DAT_UnitsState::instance.field49_0x608 = 0xffffffff;
                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                    if (extraout_ECX == 2) {
                        DAT_UnitsState::instance.lastSelectedUnitID = 0;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    }
                    if (DAT_UnitsState::instance.totalUnitsInSelection < 1) {
                        MACRO_CALL_MEMBER(Input::MouseState_Func::beginPointSelectionBox, DAT_MouseState::ptr)();
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectFirstUnitInDragBoxAnyPlayer, DAT_UnitsState::ptr)();
                        DAT_UnitsState::instance.lastSelectedUnitID
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(0);
                        if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                            DAT_UnitsState::instance.field49_0x608 = 0;
                            DAT_MouseState::instance.selectionBoxState = 1;
                            MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)();
                            BOOLEnum_00b98414::instance = TRUE;
                        }
                    }
                    goto LAB_0043782c;
                }
                if (!DAT_MouseState::instance.leftClickState) {
                    if (!DAT_MouseState::instance.draggingStopped) {
                        DAT_UnitsState::instance.totalUnitsInSelection = 0;
                        MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                        _otherUnitIDUnk
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(4);
                        if ((_otherUnitIDUnk) && (DAT_UnitsState::instance.units[_otherUnitIDUnk].isSelected == 0)) {
                            local_20 = 0;
                        }
                    }
                    goto LAB_0043782c;
                }
                if (!DAT_MouseState::instance.selectionBoxMode
                    || (MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)(),
                        DAT_MouseState::instance.selectionBoxState == 0)
                    || (DAT_GameCore::instance.menuSwitchDelay = -1,
                        0 < DAT_UnitsState::instance.totalUnitsInSelection
                            && ((DAT_MouseState::instance.leftClickStartMoment != -1
                                && ((int)(DVar7 - DAT_MouseState::instance.leftClickStartMoment) < 0xc9)))))
                    goto LAB_0043782c;
                if (DAT_TileMapState::instance.shiftRelated0or3 != 3) {
                    MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::applyDragBoxSelectionByPriority, DAT_UnitsState::ptr)();
                    goto LAB_0043782c;
                }
            LAB_004377dc:
                DAT_GameCore::instance.menuSwitchDelay = -1;
                MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::selectUnitsInDragBoxForCurrentPlayer, DAT_UnitsState::ptr)();
                goto LAB_0043782c;
            }
            if (DAT_TileMapState::instance.shiftRelated0or3 != 1)
                goto LAB_0043782c;
            /*
              WARNING: shiftRelated0or3 == 1 !
             */
            if (DAT_ModifierKeyState::instance.shift && !DAT_TribesState::instance.patrolButtonPressed
                && DAT_MouseState::instance.leftClickStart) {
                local_20 = 0;
                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                _clickHitEnemy
                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(5);
                if (_clickHitEnemy) {
                    if (DAT_UnitsState::instance.units[_clickHitEnemy].isSelected == 0) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getFirstSelectedUnitID, DAT_UnitsState::ptr)(
                            _clickHitEnemy);
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    } else {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(
                            _clickHitEnemy);
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = _clickHitEnemy;
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(Commands::GCT_UNIT_DESELECT);
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    }
                    goto LAB_0043782c;
                }
            }
            DAT_TileMapState::instance.field159_0x5549b8 = 1;
            if (DAT_UnitsState::instance.unitControlsRelated == 4)
                goto LAB_moveToTileUI;
            if (DAT_UnitsState::instance.unitControlsRelated == TRUE) {
                bVar16 = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY;
                DAT_TileMapState::instance.pendingUnitCommand = 0;
                DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                DAT_TileMapState::instance.DAT_SelectionIconType = 1;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getFirstSelectedSiegeEngineID, DAT_UnitsState::ptr)();
                if (((DAT_ViewportRenderState::instance.viewportState.field14_0x38)
                        && (_shooterID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                            _shooterID != 0))
                    || (DAT_ViewportRenderState::instance.viewportState.field16_0x40
                        && (_shooterID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                            _shooterID != 0))) {
                    bVar15 = true;
                    local_20 = 1;
                    DAT_TileMapState::instance.DAT_SelectionIconType = 0x19;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x10;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x5b;
                    DAT_TileMapState::instance.pendingUnitCommand = -1;
                }
                _shooterID = DAT_ViewportRenderState::instance.viewportState.somePitchDitchID;
                if (DAT_ViewportRenderState::instance.viewportState.somePitchDitchID
                    && DAT_GameState::instance.mapAndTime.playerTeams[DAT_TileMapState::instance
                               .pitchDitches[DAT_ViewportRenderState::instance.viewportState.somePitchDitchID]
                               .owner]
                        == DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    && (BVar8
                        = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasArchers, DAT_UnitsState::ptr)(),
                        BVar8)) {
                    _specificRange = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    _yDifference = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::isBrazierNearby,
                        DAT_EntityState::ptr)((int)DAT_UnitsState::instance.units[_specificRange].x,
                        (int)(DAT_UnitsState::instance.units[_specificRange].y),
                        (int)(DAT_UnitsState::instance.units[_specificRange].buildingHeight
                            + DAT_UnitsState::instance.units[_specificRange].terrainOrClimbHeight));
                    if ((_yDifference)
                        && (_yDifference = (int)DAT_TileMapState::instance.pitchDitches[_shooterID].y
                                - (int)DAT_UnitsState::instance.units[_specificRange].y,
                            _shooterID = (int)DAT_TileMapState::instance.pitchDitches[_shooterID].x
                                - (int)DAT_UnitsState::instance.units[_specificRange].x,
                            _shooterID * _shooterID + _yDifference * _yDifference < 0x962)) {
                        DAT_TileMapState::instance.pendingUnitCommand = 0xc;
                        DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                        local_20 = 2;
                        DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                        goto LAB_00436d33;
                    }
                }
                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                _otherUnitIDUnk
                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(1);
                if (!_otherUnitIDUnk
                    || (_shooterID = MACRO_CALL(UI::Helpers_Func::SomeUnitAndViewportCheck)(_otherUnitIDUnk),
                        !_shooterID)
                    || (BVar8 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)(),
                        BVar8
                            && (BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                                    DAT_UnitsState::ptr)(_otherUnitIDUnk),
                                !BVar8))) {
                    _otherUnitIDUnk
                        = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(2);
                    if (!_otherUnitIDUnk || DAT_MinimapViewState::instance.minimapClickEnabled
                        || (_shooterID = MACRO_CALL(UI::Helpers_Func::SomeUnitAndViewportCheck)(_otherUnitIDUnk),
                            !_shooterID)) {
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
                                bVar17 = true;
                                goto LAB_00435e83;
                            }
                        }
                        do {
                            _otherUnitIDUnk
                                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                                    DAT_UnitsState::ptr)();
                            if (!_otherUnitIDUnk) {
                                _specificRange = 0x1e;
                                _shooterID = 0x1e;
                            } else {
                                _specificRange = 0x32;
                                _shooterID = 0x32;
                            }
                            MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(
                                _shooterID, _specificRange);
                            _otherUnitIDUnk = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(1);
                            if (_otherUnitIDUnk
                                && (_shooterID
                                    = MACRO_CALL(UI::Helpers_Func::SomeUnitAndViewportCheck)(_otherUnitIDUnk),
                                    _shooterID)
                                && (BVar8
                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                        DAT_UnitsState::ptr)(),
                                    !BVar8
                                        || (BVar8 = MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                                                DAT_UnitsState::ptr)(_otherUnitIDUnk),
                                            BVar8))) {
                                uVar1 = DAT_TileMapState::instance
                                            .PathConnectionLayer[DAT_UnitsState::instance.units[_otherUnitIDUnk].tile];
                                _shooterID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                                uVar2 = DAT_TileMapState::instance
                                            .PathConnectionLayer[DAT_UnitsState::instance.units[_shooterID].tile];
                                BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                                    DAT_UnitsState::ptr)(_otherUnitIDUnk);
                                if (BVar8) {
                                    _shooterID = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                       calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                        (dword)((int)((short)uVar1)), (dword)((int)((short)uVar2)), 1);
                                    if (!_shooterID)
                                        goto LAB_moveToTileUI;
                                    DAT_TileMapState::instance.pendingUnitCommand = 3;
                                    DAT_TileMapState::instance.cursorOverlayImageBase = -3;
                                    DAT_UnitsState::instance.units[_otherUnitIDUnk].field45_0x6c = 2;
                                    local_20 = -1;
                                    DAT_TileMapState::instance.instructionTargetUnitID = _otherUnitIDUnk;
                                    goto LAB_00436d33;
                                }
                                _specificRange = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasShieldOrSiegeMobileUnits,
                                    DAT_UnitsState::ptr)();
                                if (_specificRange)
                                    goto LAB_moveToTileUI;
                                switch (DAT_UnitsState::instance.units[_shooterID].unitType) {
                                case Map::Units::UT_E_ARCHER:
                                case Map::Units::UT_E_XBOW:
                                case Map::Units::UT_A_ARCHER:
                                case Map::Units::UT_A_HARCHER:
                                case Map::Units::UT_S_FBALLISTA:
                                    _specificRange = 0xb64;
                                    break;
                                default:
                                    _specificRange = 100000000;
                                    _yDifference = MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
                                    _yDifference = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                         calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(
                                        (int)DAT_UnitsState::instance.units[_shooterID].owner,
                                        (dword)((int)((short)uVar1)), (dword)((int)((short)uVar2)), _yDifference);
                                    if (!_yDifference
                                        && (BVar8 = MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins,
                                                DAT_UnitsState::ptr)(),
                                            !BVar8
                                                || (BVar8 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                                  calculateCanReachUsingCachedAreaLogic,
                                                        DAT_PathFindingState::ptr)(
                                                        DAT_UnitsState::instance.units[_otherUnitIDUnk].tile,
                                                        DAT_UnitsState::instance.units[_shooterID].tile),
                                                    !BVar8))) {
                                        _specificRange
                                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasNoRangedUnits,
                                                DAT_UnitsState::ptr)();
                                        _specificRange = (-(uint)(_specificRange) & 0xfffff49b) + 0xb64;
                                    }
                                    break;
                                case Map::Units::UT_S_CATAPULT:
                                    _specificRange = 0x15f9;
                                    break;
                                case Map::Units::UT_S_TREBUCHET:
                                case Map::Units::UT_S_BALLISTA:
                                    _specificRange = 0x1c39;
                                    break;
                                case Map::Units::UT_S_MANGONEL:
                                    _specificRange = 0x1324;
                                    break;
                                case Map::Units::UT_A_SLINGER:
                                    _specificRange = 0x1e4;
                                    break;
                                case Map::Units::UT_A_FIRETHROWER:
                                    _specificRange = 0x79;
                                }
                                _yDifference = (int)DAT_UnitsState::instance.units[_shooterID].y
                                    - (int)DAT_UnitsState::instance.units[_otherUnitIDUnk].y;
                                _xDifference = (int)DAT_UnitsState::instance.units[_shooterID].x
                                    - (int)DAT_UnitsState::instance.units[_otherUnitIDUnk].x;
                                if (_specificRange < _xDifference * _xDifference + _yDifference * _yDifference)
                                    goto LAB_moveToTileUI;
                                uVar9 = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                                    DAT_UnitsState::ptr)();
                                if (!uVar9) {
                                    bVar16 = true;
                                    DAT_TileMapState::instance.pendingUnitCommand = 10;
                                } else {
                                    DAT_TileMapState::instance.pendingUnitCommand = 0xb;
                                }
                                DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated
                                    = DAT_UnitsState::instance.units[_otherUnitIDUnk].uid;
                                DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                                DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                                DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                local_20 = 2;
                                DAT_TileMapState::instance.uiSelectedUnitIDUnk = _otherUnitIDUnk;
                                goto LAB_00436d33;
                            }
                            if ((!DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID) || (bVar17)) {
                            LAB_00436245:
                                if (local_20 == -2)
                                    goto LAB_00436262;
                                break;
                            }
                        LAB_00435e83:
                            _shooterID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
                            local_18 = (int*)MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                            _otherUnitIDUnk = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::getFirstSelectedSiegeEngineID, DAT_UnitsState::ptr)();
                            if (!_otherUnitIDUnk) {
                                _otherUnitIDUnk = MACRO_CALL_MEMBER(
                                    Map::Buildings::BuildingsState_Func::isBuildingPathBlockerOrDamageable,
                                    DAT_BuildingsState::ptr)(
                                    _shooterID, DAT_UnitsState::instance.units[(int)local_18].tile);
                                if (_otherUnitIDUnk
                                    || (BVar8 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                                            DAT_BuildingsState::ptr)(
                                            _shooterID, DAT_UnitsState::instance.units[(int)local_18].tile),
                                        BVar8
                                            && (_specificRange = MACRO_CALL_MEMBER(
                                                    Map::Units::UnitsState_Func::selectionHasMixedAssaultAndInfantry,
                                                    DAT_UnitsState::ptr)(),
                                                _specificRange != 0)))
                                    goto LAB_00435eef;
                            } else {
                            LAB_00435eef:
                                if ((DAT_BuildingsState::instance.buildings[_shooterID].buildingType
                                        != Map::Buildings::BT_KILLINGPIT)
                                    && (_specificRange
                                        = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasShieldOrSiegeTower,
                                            DAT_UnitsState::ptr)(),
                                        _specificRange == 0)) {
                                    BVar8 = MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins,
                                        DAT_UnitsState::ptr)();
                                    if (BVar8) {
                                        switch (DAT_BuildingsState::instance.buildings[_shooterID].buildingType) {
                                        case Map::Buildings::BT_GATEHOUSELARGE:
                                        case Map::Buildings::BT_GATEHOUSESMALL:
                                        case Map::Buildings::BT_WOODGATE1:
                                        case Map::Buildings::BT_WOODGATE2:
                                        case Map::Buildings::BT_TOWER1:
                                        case Map::Buildings::BT_TOWER2:
                                        case Map::Buildings::BT_TOWER3:
                                        case Map::Buildings::BT_TOWER4:
                                        case Map::Buildings::BT_TOWER5:
                                            BVar8 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                          calculateCanReachUsingCachedAreaLogic,
                                                DAT_PathFindingState::ptr)(
                                                DAT_ViewportRenderState::instance.viewportState.cursorTile,
                                                DAT_UnitsState::instance.units[(int)local_18].tile);
                                            if (BVar8)
                                                goto LAB_moveToTileUI;
                                        }
                                    }
                                    if ((DAT_GameState::instance.mapAndTime
                                                .playerTeams[DAT_BuildingsState::instance.buildings[_shooterID].owner]
                                            == DAT_GameState::instance.mapAndTime
                                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])
                                        || (BVar8 = MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                                DAT_UnitsState::ptr)(),
                                            BVar8)) {
                                        BVar8 = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::selectionHasEngineers, DAT_UnitsState::ptr)();
                                        if (BVar8
                                            && (int)DAT_BuildingsState::instance.buildings[_shooterID].owner
                                                == DAT_GameSynchronyState::instance.currentPlayerSlotID
                                            && !DAT_MinimapViewState::instance.minimapClickEnabled
                                            && (BVar5 = DAT_BuildingsState::instance.buildings[_shooterID].buildingType,
                                                BVar5 == Map::Buildings::BT_CATAPULT
                                                    || (((((BVar5 == Map::Buildings::BT_FIREBALLISTA
                                                               || (BVar5 == Map::Buildings::BT_TREBUCHET))
                                                              || (BVar5 == Map::Buildings::BT_BATTERINGRAM))
                                                             || ((BVar5 == Map::Buildings::BT_SIEGETOWER
                                                                 || (BVar5 == Map::Buildings::BT_SHIELD))))
                                                        || (BVar5 == Map::Buildings::BT_OILSMELTER))))) {
                                            DAT_BuildingsState::instance.buildings[_shooterID].field68_0xc2 = 2;
                                            DAT_TileMapState::instance.pendingUnitCommand = 2;
                                            DAT_TileMapState::instance.cursorOverlayImageBase = -2;
                                            local_20 = -1;
                                        }
                                    } else {
                                    LAB_00435bb3:
                                        UVar4 = DAT_UnitsState::instance.units[(int)local_18].unitType;
                                        _specificRange = 0;
                                        switch (UVar4) {
                                        case Map::Units::UT_E_ARCHER:
                                        case Map::Units::UT_E_XBOW:
                                        case Map::Units::UT_A_ARCHER:
                                        case Map::Units::UT_A_HARCHER:
                                            _specificRange = 0xb64;
                                            switch (DAT_BuildingsState::instance.buildings[_shooterID].buildingType) {
                                            case Map::Buildings::BT_GATEHOUSELARGE:
                                            case Map::Buildings::BT_GATEHOUSESMALL:
                                            case Map::Buildings::BT_WOODGATE1:
                                            case Map::Buildings::BT_WOODGATE2:
                                            case Map::Buildings::BT_TOWER1:
                                            case Map::Buildings::BT_TOWER2:
                                            case Map::Buildings::BT_TOWER3:
                                            case Map::Buildings::BT_TOWER4:
                                            case Map::Buildings::BT_TOWER5:
                                            switchD_00435c7b_caseD_2d:
                                                _specificRange = -1;
                                                if (DAT_UnitsState::instance.unitControlsRelated == 5)
                                                    goto switchD_00435bd8_caseD_18;
                                            }
                                            break;
                                        default:
                                        switchD_00435bd8_caseD_18:
                                            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                                                || !DAT_GameState::instance.mapAndTime.skirmishStrongWalls
                                                || UVar4 == Map::Units::UT_S_BATTERINGRAM
                                                || 4 < (int)(short)DAT_BuildingsState::instance.buildings[_shooterID]
                                                            .buildingType
                                                        - 0x4aU) {
                                                if (_specificRange != -1) {
                                                    _specificRange = 100000000;
                                                    _yDifference
                                                        = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                                                canUnitReachBuildingPerimeter,
                                                            DAT_BuildingsState::ptr)(_shooterID, (int)(local_18));
                                                    if (!_yDifference) {
                                                        _specificRange = MACRO_CALL_MEMBER(
                                                            Map::Units::UnitsState_Func::selectionHasNoRangedUnits,
                                                            DAT_UnitsState::ptr)();
                                                        _specificRange = (-(uint)(_specificRange) & 0xfffff49b) + 0xb64;
                                                    }
                                                }
                                            } else {
                                                _specificRange = -1;
                                                bVar6 = true;
                                            }
                                            break;
                                        case Map::Units::UT_S_CATAPULT:
                                            _specificRange = 0x15f9;
                                            break;
                                        case Map::Units::UT_S_TREBUCHET:
                                            _specificRange = 0x1c39;
                                            break;
                                        case Map::Units::UT_S_MANGONEL:
                                            _specificRange = 0x1324;
                                            break;
                                        case Map::Units::UT_S_BALLISTA:
                                            _specificRange = 0x1c39;
                                            switch (DAT_BuildingsState::instance.buildings[_shooterID].buildingType) {
                                            case Map::Buildings::BT_GATEHOUSELARGE:
                                            case Map::Buildings::BT_GATEHOUSESMALL:
                                            case Map::Buildings::BT_WOODGATE1:
                                            case Map::Buildings::BT_WOODGATE2:
                                            case Map::Buildings::BT_TOWER1:
                                            case Map::Buildings::BT_TOWER2:
                                            case Map::Buildings::BT_TOWER3:
                                            case Map::Buildings::BT_TOWER4:
                                            case Map::Buildings::BT_TOWER5:
                                            switchD_00435ce1_caseD_2d:
                                                _specificRange = -1;
                                            }
                                            break;
                                        case Map::Units::UT_A_SLINGER:
                                            _specificRange = 0x1e4;
                                            switch (DAT_BuildingsState::instance.buildings[_shooterID].buildingType) {
                                            case Map::Buildings::BT_GATEHOUSELARGE:
                                            case Map::Buildings::BT_GATEHOUSESMALL:
                                            case Map::Buildings::BT_WOODGATE1:
                                            case Map::Buildings::BT_WOODGATE2:
                                            case Map::Buildings::BT_TOWER1:
                                            case Map::Buildings::BT_TOWER2:
                                            case Map::Buildings::BT_TOWER3:
                                            case Map::Buildings::BT_TOWER4:
                                            case Map::Buildings::BT_TOWER5:
                                                goto switchD_00435c7b_caseD_2d;
                                            }
                                            break;
                                        case Map::Units::UT_A_FIRETHROWER:
                                            _specificRange = 0x79;
                                            switch (DAT_BuildingsState::instance.buildings[_shooterID].buildingType) {
                                            case Map::Buildings::BT_GATEHOUSELARGE:
                                            case Map::Buildings::BT_GATEHOUSESMALL:
                                            case Map::Buildings::BT_WOODGATE1:
                                            case Map::Buildings::BT_WOODGATE2:
                                            case Map::Buildings::BT_TOWER1:
                                            case Map::Buildings::BT_TOWER2:
                                            case Map::Buildings::BT_TOWER3:
                                            case Map::Buildings::BT_TOWER4:
                                            case Map::Buildings::BT_TOWER5:
                                                goto switchD_00435c7b_caseD_2d;
                                            }
                                            break;
                                        case Map::Units::UT_S_FBALLISTA:
                                            _specificRange = 0xb64;
                                            switch (DAT_BuildingsState::instance.buildings[_shooterID].buildingType) {
                                            case Map::Buildings::BT_GATEHOUSELARGE:
                                            case Map::Buildings::BT_GATEHOUSESMALL:
                                            case Map::Buildings::BT_WOODGATE1:
                                            case Map::Buildings::BT_WOODGATE2:
                                            case Map::Buildings::BT_TOWER1:
                                            case Map::Buildings::BT_TOWER2:
                                            case Map::Buildings::BT_TOWER3:
                                            case Map::Buildings::BT_TOWER4:
                                            case Map::Buildings::BT_TOWER5:
                                                goto switchD_00435ce1_caseD_2d;
                                            }
                                        }
                                        if ((DAT_BuildingsState::instance.buildings[_shooterID].buildingType
                                                == Map::Buildings::BT_PITCHDITCH)
                                            && (BVar8
                                                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasArchers,
                                                    DAT_UnitsState::ptr)(),
                                                !BVar8)) {
                                            _specificRange = -1;
                                        }
                                        if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
                                            && DAT_GameSynchronyState::instance.currentGameMode
                                                != Game::GM_SKIRMISH_SINGLE_PLAYER
                                            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                                            _specificRange = -1;
                                        }
                                        _yDifference = (int)(short)DAT_BuildingsState::instance.buildings[_shooterID].y
                                            - (int)DAT_UnitsState::instance.units[(int)local_18].y;
                                        _shooterID = (int)(short)DAT_BuildingsState::instance.buildings[_shooterID].x
                                            - (int)DAT_UnitsState::instance.units[(int)local_18].x;
                                        if (_specificRange < _shooterID * _shooterID + _yDifference * _yDifference) {
                                            if (bVar18)
                                                goto LAB_0043674b;
                                        } else {
                                            bVar16 = true;
                                            DAT_TileMapState::instance.pendingUnitCommand = 1;
                                            DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                            DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                                            local_20 = 2;
                                            DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                                        }
                                    }
                                }
                            }
                            if (!bVar17)
                                goto LAB_00436245;
                        } while (local_20 == -2);
                        if (local_20 == -1) {
                            if (!bVar15)
                                goto LAB_00436d33;
                        LAB_00436262:
                            if (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                                && (DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                            .viewportState.mouseAtomRefFloorTile]
                                    & 0x10000300U)
                                && (BVar8
                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                        DAT_UnitsState::ptr)(),
                                    !BVar8
                                        && (!(DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                                      .viewportState.mouseAtomRefFloorTile]
                                            & 2)))) {
                                uVar1 = DAT_TileMapState::instance.PathConnectionLayer[DAT_ViewportRenderState::instance
                                        .viewportState.mouseAtomRefFloorTile];
                                local_18 = (int*)MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                                uVar2 = DAT_TileMapState::instance
                                            .PathConnectionLayer[DAT_UnitsState::instance.units[(int)local_18].tile];
                                _otherUnitIDUnk = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::getFirstSelectedLadderUnitID, DAT_UnitsState::ptr)();
                                if (!_otherUnitIDUnk) {
                                    if (DAT_UnitsState::instance.units[(int)local_18].unitType
                                        != Map::Units::UT_S_TOWER) {
                                        _shooterID = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::checkAnySelectedUnitCannotClimb,
                                            DAT_UnitsState::ptr)();
                                        if (!_shooterID) {
                                            UVar4 = DAT_UnitsState::instance.units[(int)local_18].unitType;
                                            if ((((UVar4 == Map::Units::UT_S_BATTERINGRAM)
                                                     || (UVar4 == Map::Units::UT_S_CATAPULT))
                                                    || ((UVar4 == Map::Units::UT_S_TREBUCHET
                                                        || (((UVar4 == Map::Units::UT_E_KNIGHT
                                                                 || (UVar4 == Map::Units::UT_S_TOWER))
                                                            || (_shooterID = MACRO_CALL_MEMBER(
                                                                    Map::Navigation::PathFindingState_Func::
                                                                        calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                                    DAT_PathFindingState::ptr)(
                                                                    DAT_GameSynchronyState::instance
                                                                        .currentPlayerSlotID,
                                                                    (dword)((int)((short)uVar1)),
                                                                    (dword)((int)((short)uVar2)), 0),
                                                                _shooterID == 0))))))
                                                && (_shooterID = MACRO_CALL_MEMBER(
                                                        Map::Units::UnitsState_Func::selectionContainsShieldmenOnly,
                                                        DAT_UnitsState::ptr)(),
                                                    _shooterID == 0
                                                        && ((DAT_TileMapState::instance
                                                                    .WallOwnerLayer[DAT_ViewportRenderState::instance
                                                                            .viewportState.mouseAtomRefFloorTile]
                                                                & 7)
                                                                + TRUE
                                                            != DAT_GameSynchronyState::instance.currentPlayerSlotID))) {
                                                UVar4 = DAT_UnitsState::instance.units[(int)local_18].unitType;
                                                switch (UVar4) {
                                                case Map::Units::UT_E_ARCHER:
                                                case Map::Units::UT_E_XBOW:
                                                case Map::Units::UT_A_ARCHER:
                                                case Map::Units::UT_A_SLINGER:
                                                case Map::Units::UT_A_HARCHER:
                                                case Map::Units::UT_A_FIRETHROWER:
                                                    _shooterID = -1;
                                                    if (DAT_UnitsState::instance.unitControlsRelated == 5)
                                                        goto switchD_004364b3_caseD_18;
                                                    break;
                                                default:
                                                switchD_004364b3_caseD_18:
                                                    if (((DAT_GameSynchronyState::instance.currentGameMode
                                                             == Game::GM_SOLITARY)
                                                            || (DAT_GameState::instance.mapAndTime.skirmishStrongWalls
                                                                == 0))
                                                        || (UVar4 == Map::Units::UT_S_BATTERINGRAM))
                                                        goto switchD_004364b3_caseD_3a;
                                                    _shooterID = -1;
                                                    bVar6 = true;
                                                    break;
                                                case Map::Units::UT_S_CATAPULT:
                                                    _shooterID = 0x15f9;
                                                    break;
                                                case Map::Units::UT_S_TREBUCHET:
                                                    _shooterID = 0x1c39;
                                                    break;
                                                case Map::Units::UT_S_MANGONEL:
                                                    _shooterID = 0x1324;
                                                    break;
                                                case Map::Units::UT_S_TOWER:
                                                switchD_004364b3_caseD_3a:
                                                    _shooterID = 100000000;
                                                    _specificRange = MACRO_CALL_MEMBER(
                                                        Map::Buildings::BuildingsState_Func::canUnitReachAdjacentTile,
                                                        DAT_BuildingsState::ptr)(
                                                        DAT_ViewportRenderState::instance.viewportState
                                                            .mouseAtomRefFloorTile,
                                                        (int)(local_18));
                                                    if (!_specificRange) {
                                                        _shooterID = MACRO_CALL_MEMBER(
                                                            Map::Units::UnitsState_Func::selectionHasNoRangedUnits,
                                                            DAT_UnitsState::ptr)();
                                                        _shooterID = (-(uint)(_shooterID) & 0xfffff49b) + 0xb64;
                                                    }
                                                    break;
                                                case Map::Units::UT_S_BALLISTA:
                                                case Map::Units::UT_S_FBALLISTA:
                                                    _shooterID = -1;
                                                }
                                                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
                                                    && DAT_GameSynchronyState::instance.currentGameMode
                                                        != Game::GM_SKIRMISH_SINGLE_PLAYER
                                                    && DAT_GameSynchronyState::instance.currentGameMode
                                                        != Game::GM_SOLITARY) {
                                                    _shooterID = -1;
                                                }
                                                _yDifference
                                                    = (DAT_ViewportRenderState::instance.viewportState
                                                              .mouseAtomRefFloorTile
                                                          - DAT_ViewportRenderState::instance
                                                              .translationMatrix[DAT_ViewportRenderState::instance
                                                                      .tileTranslationMatrix_YComponent
                                                                          [DAT_ViewportRenderState::instance
                                                                                  .viewportState.mouseAtomRefFloorTile]]
                                                              .addXgetTile)
                                                    - (int)DAT_UnitsState::instance.units[(int)local_18].x;
                                                _specificRange
                                                    = (int)DAT_ViewportRenderState::instance
                                                          .tileTranslationMatrix_YComponent[DAT_ViewportRenderState::
                                                                  instance.viewportState.mouseAtomRefFloorTile]
                                                    - (int)DAT_UnitsState::instance.units[(int)local_18].y;
                                                if (_specificRange * _specificRange + _yDifference * _yDifference
                                                    <= _shooterID) {
                                                    bVar16 = true;
                                                    DAT_TileMapState::instance.pendingUnitCommand = 6;
                                                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                                                    DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                                    local_20 = 2;
                                                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                                                    goto LAB_00436d33;
                                                }
                                            }
                                        } else {
                                            _shooterID
                                                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                        calculateCanPlayerUnitsNavigateToAreaFromArea,
                                                    DAT_PathFindingState::ptr)(
                                                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                                    (dword)((int)((short)uVar1)), (dword)((int)((short)uVar2)), 1);
                                            if (!_shooterID
                                                && (DAT_TileMapState::instance
                                                           .WallOwnerLayer[DAT_ViewportRenderState::instance
                                                                   .viewportState.mouseAtomRefFloorTile]
                                                       & 7)
                                                        + TRUE
                                                    != DAT_GameSynchronyState::instance.currentPlayerSlotID)
                                                goto LAB_00436607;
                                        }
                                        goto LAB_moveToTileUI;
                                    }
                                    _otherUnitIDUnk = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::findFreeTileNearby,
                                        DAT_UnitsState::ptr)((uint)local_18,
                                        (uint)(DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile));
                                    if (_otherUnitIDUnk) {
                                        DAT_TileMapState::instance.pendingUnitCommand = 6;
                                        DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                                        DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                        local_20 = 2;
                                        DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                                        goto LAB_00436d33;
                                    }
                                    goto LAB_00436953;
                                }
                                if ((DAT_TileMapState::instance.WallOwnerLayer[DAT_ViewportRenderState::instance
                                             .viewportState.mouseAtomRefFloorTile]
                                        & 7)
                                        + TRUE
                                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                                    DAT_TileMapState::instance.pendingUnitCommand = 5;
                                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                                    local_20 = 2;
                                    DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                    goto LAB_00436d33;
                                }
                            }
                        }
                    } else {
                        DAT_TileMapState::instance.instructionTargetUnitID = _otherUnitIDUnk;
                        _shooterID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                            DAT_UnitsState::ptr)(_otherUnitIDUnk);
                        if ((!_shooterID)
                            || (uVar9 = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)(),
                                uVar9 == 0)) {
                            sVar3 = DAT_UnitsState::instance.units[_otherUnitIDUnk]
                                        .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                            if ((sVar3) && (DAT_UnitsState::instance.units[_otherUnitIDUnk].isSelected != 0)) {
                                bVar18 = true;
                                if (0 < sVar3) {
                                    _shooterID
                                        = (int)DAT_UnitsState::instance.units[_otherUnitIDUnk]
                                              .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                                    psVar10 = DAT_UnitsState::instance.units[_otherUnitIDUnk].manningEngineerRef;
                                    do {
                                        if (DAT_UnitsState::instance.units[*psVar10].state.generic
                                            == Map::Units::States::US_JESTER_ROAM_TO) {
                                            bVar18 = false;
                                        }
                                        psVar10 = psVar10 + 1;
                                        _shooterID = _shooterID + -1;
                                    } while (_shooterID);
                                    if (!bVar18)
                                        goto LAB_moveToTileUI;
                                }
                                DAT_TileMapState::instance.pendingUnitCommand = 4;
                                DAT_TileMapState::instance.cursorOverlayImageBase = -4;
                                DAT_UnitsState::instance.units[_otherUnitIDUnk].field45_0x6c = 3;
                                local_20 = -1;
                                goto LAB_00436d33;
                            }
                        } else {
                            uVar1 = DAT_TileMapState::instance
                                        .PathConnectionLayer[DAT_UnitsState::instance.units[_otherUnitIDUnk].tile];
                            _shooterID = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                            _shooterID = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                                DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                (dword)((int)((short)uVar1)),
                                (dword)((int)((short)DAT_TileMapState::instance
                                        .PathConnectionLayer[DAT_UnitsState::instance.units[_shooterID].tile])),
                                1);
                            if (_shooterID) {
                                DAT_TileMapState::instance.pendingUnitCommand = 3;
                                DAT_TileMapState::instance.cursorOverlayImageBase = -3;
                                DAT_UnitsState::instance.units[_otherUnitIDUnk].field45_0x6c = 2;
                                local_20 = -1;
                                goto LAB_00436d33;
                            }
                        }
                    }
                } else {
                    uVar1 = DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[_otherUnitIDUnk].tile];
                    _shooterID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    uVar2 = DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[_shooterID].tile];
                    BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionHasUnmannedSiegeEngine,
                        DAT_UnitsState::ptr)(_otherUnitIDUnk);
                    if (!BVar8) {
                        _specificRange = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionHasShieldOrSiegeMobileUnits, DAT_UnitsState::ptr)();
                        if (!_specificRange) {
                            switch (DAT_UnitsState::instance.units[_shooterID].unitType) {
                            case Map::Units::UT_E_ARCHER:
                            case Map::Units::UT_E_XBOW:
                            case Map::Units::UT_A_ARCHER:
                            case Map::Units::UT_A_HARCHER:
                            case Map::Units::UT_S_FBALLISTA:
                                _specificRange = 0xb64;
                                break;
                            default:
                                _specificRange = 100000000;
                                _yDifference = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
                                _yDifference = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_shooterID].owner,
                                    (dword)((int)((short)uVar1)), (dword)((int)((short)uVar2)), _yDifference);
                                if (!_yDifference
                                    && (BVar8 = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins,
                                            DAT_UnitsState::ptr)(),
                                        !BVar8
                                            || (BVar8 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::
                                                                              calculateCanReachUsingCachedAreaLogic,
                                                    DAT_PathFindingState::ptr)(
                                                    DAT_UnitsState::instance.units[_otherUnitIDUnk].tile,
                                                    DAT_UnitsState::instance.units[_shooterID].tile),
                                                !BVar8))) {
                                    _specificRange = MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::selectionHasNoRangedUnits, DAT_UnitsState::ptr)();
                                    _specificRange = (-(uint)(_specificRange) & 0xfffff49b) + 0xb64;
                                }
                                break;
                            case Map::Units::UT_S_CATAPULT:
                                _specificRange = 0x15f9;
                                break;
                            case Map::Units::UT_S_TREBUCHET:
                            case Map::Units::UT_S_BALLISTA:
                                _specificRange = 0x1c39;
                                break;
                            case Map::Units::UT_S_MANGONEL:
                                _specificRange = 0x1324;
                                break;
                            case Map::Units::UT_A_SLINGER:
                                _specificRange = 0x1e4;
                                break;
                            case Map::Units::UT_A_FIRETHROWER:
                                _specificRange = 0x79;
                            }
                            _yDifference = (int)DAT_UnitsState::instance.units[_shooterID].y
                                - (int)DAT_UnitsState::instance.units[_otherUnitIDUnk].y;
                            _xDifference2 = (int)DAT_UnitsState::instance.units[_shooterID].x
                                - (int)DAT_UnitsState::instance.units[_otherUnitIDUnk].x;
                            /*
                              Check if unit under mouse is in range to be attacked
                             */
                            if (_xDifference2 * _xDifference2 + _yDifference * _yDifference <= _specificRange) {
                                uVar9 = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                                    DAT_UnitsState::ptr)();
                                if (!uVar9) {
                                    DAT_TileMapState::instance.pendingUnitCommand = 10;
                                } else {
                                    DAT_TileMapState::instance.pendingUnitCommand = 0xb;
                                }
                                bVar16 = uVar9 == 0 || bVar16;
                                DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated
                                    = DAT_UnitsState::instance.units[_otherUnitIDUnk].uid;
                                DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                                DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                                DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                                local_20 = 2;
                                DAT_TileMapState::instance.uiSelectedUnitIDUnk = _otherUnitIDUnk;
                                goto LAB_00436d33;
                            }
                        }
                    } else {
                        _shooterID = MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (dword)((int)((short)uVar1)), (dword)((int)((short)uVar2)), 1);
                        if (_shooterID) {
                            DAT_TileMapState::instance.pendingUnitCommand = 3;
                            DAT_TileMapState::instance.cursorOverlayImageBase = -3;
                            DAT_UnitsState::instance.units[_otherUnitIDUnk].field45_0x6c = 2;
                            local_20 = -1;
                            DAT_TileMapState::instance.instructionTargetUnitID = _otherUnitIDUnk;
                            goto LAB_00436d33;
                        }
                    }
                }
            LAB_moveToTileUI:
                if ((local_20 != -2) || (DAT_MouseState::instance.selectionBoxMode))
                    goto LAB_00436d33;
                MACRO_CALL_MEMBER(Input::MouseState_Func::setupHitBox, DAT_MouseState::ptr)(4, 4);
                _otherUnitIDUnk
                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(5);
                if (_otherUnitIDUnk) {
                    if (DAT_UnitsState::instance.units[_otherUnitIDUnk].isSelected == 0) {
                        local_20 = 0;
                        goto LAB_00436d33;
                    }
                    if (_otherUnitIDUnk == DAT_UnitsState::instance.field49_0x608
                        && (DVar11 = timeGetTime(), DVar11 - DAT_UnitsState::instance.field48_0x604 < 500)
                        && DAT_MouseState::instance.leftClickStart) {
                        DAT_00b98424::instance = 0;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectAllUnitsOfTypeForPlayer,
                            DAT_UnitsState::ptr)((int)DAT_UnitsState::instance.units[_otherUnitIDUnk].owner,
                            (int)((short)DAT_UnitsState::instance.units[_otherUnitIDUnk].unitType));
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::createTribeFromSelectedUnits, DAT_UnitsState::ptr)();
                        DAT_UnitsState::instance.field49_0x608 = 0;
                    }
                }
                if (!DAT_ViewportRenderState::instance.viewportState.cursorTile)
                    goto LAB_00436953;
                bVar18 = false;
                while (true) {
                    bVar17 = false;
                    flag1003 = DAT_TileMapState::instance
                                   .LogicLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile];
                    uVar1 = DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile];
                    /*
                      returns a unit id if it fulfills some criteria? being selected !?
                     */
                    _shooterID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    if (0 < _shooterID) {
                        _specificRange = DAT_UnitsState::instance.units[_shooterID].tile;
                        toArea = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer[_specificRange];
                        if ((DAT_TileMapState::instance.LogicLayer[_specificRange] & 0x40000000U)) {
                            toArea = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::canNavigateFunctionReturnsArea,
                                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_shooterID].owner,
                                (dword)((int)((short)uVar1)), (uint)(DAT_UnitsState::instance.units[_shooterID].x),
                                (uint)(DAT_UnitsState::instance.units[_shooterID].y));
                        }
                        _specificRange
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
                        _specificRange = MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (dword)((int)((short)uVar1)), (dword)((int)(toArea)), _specificRange);
                        bVar17 = _specificRange != 0;
                    }
                    BVar8 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::isTowerTileOvercrowdedByCurrentPlayer,
                        DAT_UnitsState::ptr)(DAT_ViewportRenderState::instance.viewportState.cursorTile);
                    if (BVar8) {
                        bVar17 = false;
                    }
                    _specificRange = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionHasMovableNonSiegeUnit, DAT_UnitsState::ptr)();
                    if (!_specificRange) {
                        bVar17 = false;
                    }
                    _yDifference = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionHasMixedAssaultAndInfantry, DAT_UnitsState::ptr)();
                    if (_yDifference) {
                        if ((flag1003 & 0x10000100)
                            || (_yDifference = MACRO_CALL_MEMBER(
                                    Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
                                    DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_shooterID].x,
                                    (int)(DAT_UnitsState::instance.units[_shooterID].y),
                                    DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                                        - DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_ViewportRenderState::instance
                                                    .tileTranslationMatrix_YComponent[DAT_ViewportRenderState::instance
                                                            .viewportState.mouseAtomRefFloorTile]]
                                            .addXgetTile,
                                    (int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                            [DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]),
                                    100000),
                                _yDifference == 0)) {
                            bVar17 = false;
                        }
                    }
                    _otherUnitIDUnk = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                    if (!_otherUnitIDUnk || bVar17 || bVar16 || bVar18)
                        break;
                    bVar18 = true;
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
                              .campground.tileEntry;
                    DAT_ViewportRenderState::instance.viewportState.mouseX
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .campground.xEntry;
                    DAT_ViewportRenderState::instance.viewportState.mouseY
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .campground.yEntry;
                }
                BVar12 = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)();
                if ((!BVar12)
                    || (BVar12 = MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::calculateCanReachUsingCachedAreaLogic,
                            DAT_PathFindingState::ptr)(DAT_ViewportRenderState::instance.viewportState.cursorTile,
                            DAT_UnitsState::instance.units[_shooterID].tile),
                        !BVar12)) {
                    if (bVar17)
                        goto LAB_00436b8a;
                    if (!_specificRange || BVar8
                        || !(DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[_shooterID].tile]
                            & 0x10000100U)
                        || (_specificRange = MACRO_CALL_MEMBER(
                                Map::Navigation::PathFindingState_Func::someBinaryAlgFunctionPathFinding,
                                DAT_PathFindingState::ptr)(_shooterID),
                            _specificRange == 0)
                        || (_shooterID
                            = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findCrossAreaBridgeTileToTarget,
                                DAT_PathFindingState::ptr)(_shooterID,
                                (uint)(DAT_ViewportRenderState::instance.viewportState.mouseX),
                                (uint)(DAT_ViewportRenderState::instance.viewportState.mouseY)),
                            _shooterID == 0)) {
                        DAT_TileMapState::instance.pendingUnitCommand = -10;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0x41;
                        DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                        DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                        /*
                          NoEntry-Icon under mouse
                         */
                        DAT_TileMapState::instance.DAT_SelectionIconType = 0x11;
                        local_20 = 4;
                        goto LAB_00436c74;
                    }
                    local_20 = 2;
                    goto LAB_00436d8a;
                }
                bVar17 = true;
            LAB_00436b8a:
                if (DAT_ViewportRenderState::instance.viewportState.field27_0x6c == 1) {
                    DAT_TileMapState::instance.pendingUnitCommand = -1;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0xb5;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                    DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                    /*
                      MoveTo-Icon under mouse
                     */
                    DAT_TileMapState::instance.DAT_SelectionIconType = 1;
                    local_20 = 4;
                } else {
                    local_20 = 2;
                }
            LAB_00436c74:
                _otherUnitIDUnk = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                if (!_otherUnitIDUnk || !bVar17 || bVar16
                    || (_shooterID = (int)DAT_TileMapState::instance
                            .BuildingLayer[DAT_ViewportRenderState::instance.viewportState.cursorTile],
                        _shooterID == 0
                            || (BVar5 = DAT_BuildingsState::instance.buildings[_shooterID].buildingType,
                                (short)BVar5 < 0x28)))
                    goto LAB_00436d33;
                if ((short)BVar5 < 0x2d) {
                    if ((int)DAT_BuildingsState::instance.buildings[_shooterID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        bVar16 = true;
                    }
                    goto LAB_00436d33;
                }
                if (BVar5 != Map::Buildings::BT_CAMPGROUND || !bVar18
                    || (int)DAT_BuildingsState::instance.buildings[_shooterID].owner
                        != DAT_GameSynchronyState::instance.currentPlayerSlotID
                    || (bVar16 = true, !DAT_MouseState::instance.leftClickStart))
                    goto LAB_00436d33;
            } else {
                if (DAT_UnitsState::instance.unitControlsRelated == 0x14) {
                    _otherUnitIDUnk = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource, DAT_UnitsState::ptr)();
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                    DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                    DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated = 0;
                    local_20 = -1;
                    MACRO_CALL_MEMBER(
                        Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                        DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_otherUnitIDUnk].x,
                        (int)(DAT_UnitsState::instance.units[_otherUnitIDUnk].y),
                        DAT_ViewportRenderState::instance.viewportState.mouseX,
                        DAT_ViewportRenderState::instance.viewportState.mouseY);
                    if (DAT_DirectionAlgorithmState::instance.orientation == 0xf
                        || (!DAT_ViewportRenderState::instance.viewportState.mouseX
                            && (!DAT_ViewportRenderState::instance.viewportState.mouseY))) {
                        DAT_TileMapState::instance.pendingUnitCommand = -1;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0x41;
                        DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                        DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                        local_20 = 4;
                    } else {
                        uVar9 = (DAT_DirectionAlgorithmState::instance.orientation
                                    - DAT_TileMapState::instance.mapOrientation)
                                + 0xcU
                            & 0x80000007;
                        if ((int)uVar9 < 0) {
                            uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_UnitsState::instance.units[_otherUnitIDUnk].field46_0x6e = (short)uVar9 + 1;
                    }
                    goto LAB_00436d33;
                }
                if (DAT_UnitsState::instance.unitControlsRelated != 5) {
                    if (DAT_UnitsState::instance.unitControlsRelated == 0x16) {
                        DAT_TileMapState::instance.pendingUnitCommand = -1;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0x41;
                        DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                        DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                        DAT_TileMapState::instance.DAT_SelectionIconType = 0x11;
                        local_20 = 4;
                        _shooterID = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                        /*
                          interesting: mouse ranges for ranged units
                         */
                        switch (DAT_UnitsState::instance.units[_shooterID].unitType) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_HARCHER:
                        case Map::Units::UT_S_FBALLISTA:
                            _specificRange = 0xb64;
                            break;
                        default:
                            _specificRange = 0;
                            break;
                        case Map::Units::UT_S_CATAPULT:
                            _specificRange = 0x15f9;
                            break;
                        case Map::Units::UT_S_TREBUCHET:
                        case Map::Units::UT_S_BALLISTA:
                            _specificRange = 0x1c39;
                            break;
                        case Map::Units::UT_S_MANGONEL:
                            _specificRange = 0x1324;
                            break;
                        case Map::Units::UT_A_SLINGER:
                            _specificRange = 0x1e4;
                            break;
                        case Map::Units::UT_A_FIRETHROWER:
                            _specificRange = 0x79;
                        }
                        _yDifference = DAT_ViewportRenderState::instance.viewportState.mouseX
                            - DAT_UnitsState::instance.units[_shooterID].x;
                        _shooterID = DAT_ViewportRenderState::instance.viewportState.mouseY
                            - DAT_UnitsState::instance.units[_shooterID].y;
                        if (_specificRange < _shooterID * _shooterID + _yDifference * _yDifference)
                            goto LAB_00436d33;
                    }
                LAB_004367d0:
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                    DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                    DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                    DAT_TileMapState::instance.DAT_SomeUNitUIDUIRelated = 0;
                    local_20 = 2;
                    goto LAB_00436d33;
                }
                bVar18 = true;
                local_18 = (int*)MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                _shooterID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
                if (!DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID) {
                    if (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                        && (DAT_TileMapState::instance
                                .LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                            & 0x10000300U)
                        && (BVar8 = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)(),
                            !BVar8
                                && (!(DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance
                                              .viewportState.mouseAtomRefFloorTile]
                                    & 2)))) {
                    LAB_00436607:
                        UVar4 = DAT_UnitsState::instance.units[(int)local_18].unitType;
                        switch (UVar4) {
                        case Map::Units::UT_E_ARCHER:
                        case Map::Units::UT_E_XBOW:
                        case Map::Units::UT_A_ARCHER:
                        case Map::Units::UT_A_SLINGER:
                        case Map::Units::UT_A_HARCHER:
                            _shooterID = -1;
                            if (DAT_UnitsState::instance.unitControlsRelated == 5)
                                goto switchD_0043662c_caseD_18;
                            break;
                        default:
                        switchD_0043662c_caseD_18:
                            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                                || !DAT_GameState::instance.mapAndTime.skirmishStrongWalls
                                || UVar4 == Map::Units::UT_S_BATTERINGRAM)
                                goto switchD_0043662c_caseD_3a;
                            _shooterID = -1;
                            bVar6 = true;
                            break;
                        case Map::Units::UT_S_CATAPULT:
                            _shooterID = 0x15f9;
                            break;
                        case Map::Units::UT_S_TREBUCHET:
                            _shooterID = 0x1c39;
                            break;
                        case Map::Units::UT_S_MANGONEL:
                            _shooterID = 0x1324;
                            break;
                        case Map::Units::UT_S_TOWER:
                        switchD_0043662c_caseD_3a:
                            _shooterID = 100000000;
                            _specificRange = MACRO_CALL_MEMBER(
                                Map::Buildings::BuildingsState_Func::canUnitReachAdjacentTile, DAT_BuildingsState::ptr)(
                                DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile, (int)(local_18));
                            if (!_specificRange) {
                                _shooterID = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::selectionHasNoRangedUnits, DAT_UnitsState::ptr)();
                                _shooterID = (-(uint)(_shooterID) & 0xfffff49b) + 0xb64;
                            }
                            break;
                        case Map::Units::UT_S_BALLISTA:
                        case Map::Units::UT_A_FIRETHROWER:
                        case Map::Units::UT_S_FBALLISTA:
                            _shooterID = -1;
                        }
                        if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks
                            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                            _shooterID = -1;
                        }
                        _yDifference
                            = (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile
                                  - DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_ViewportRenderState::instance
                                              .tileTranslationMatrix_YComponent[DAT_ViewportRenderState::instance
                                                      .viewportState.mouseAtomRefFloorTile]]
                                      .addXgetTile)
                            - (int)DAT_UnitsState::instance.units[(int)local_18].x;
                        _specificRange = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                             [DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                            - (int)DAT_UnitsState::instance.units[(int)local_18].y;
                        if (_specificRange * _specificRange + _yDifference * _yDifference <= _shooterID) {
                            bVar16 = true;
                            DAT_TileMapState::instance.pendingUnitCommand = 6;
                            DAT_TileMapState::instance.cursorOverlayImageBase = 0x20;
                            DAT_TileMapState::instance.DAT_SelectionIconType = 9;
                            local_20 = 2;
                            DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                            goto LAB_00436d33;
                        }
                        if (!bVar18)
                            goto LAB_moveToTileUI;
                    }
                } else {
                    _otherUnitIDUnk = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getFirstSelectedSiegeEngineID, DAT_UnitsState::ptr)();
                    if (!_otherUnitIDUnk) {
                        BVar8 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                            DAT_BuildingsState::ptr)(_shooterID, DAT_UnitsState::instance.units[(int)local_18].tile);
                        if (!BVar8
                            && (BVar8
                                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                                    DAT_BuildingsState::ptr)(
                                    _shooterID, DAT_UnitsState::instance.units[(int)local_18].tile),
                                !BVar8
                                    || (_specificRange = MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::selectionHasMixedAssaultAndInfantry,
                                            DAT_UnitsState::ptr)(),
                                        _specificRange == 0)))
                            goto LAB_0043674b;
                    }
                    if (DAT_BuildingsState::instance.buildings[_shooterID].buildingType != Map::Buildings::BT_KILLINGPIT
                        && (_specificRange = MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectionHasShieldOrSiegeTower, DAT_UnitsState::ptr)(),
                            _specificRange == 0
                                && (BVar8
                                    = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsEngineersOnly,
                                        DAT_UnitsState::ptr)(),
                                    !BVar8)))
                        goto LAB_00435bb3;
                }
            LAB_0043674b:
                switch (DAT_UnitsState::instance.units[(int)local_18].unitType) {
                case Map::Units::UT_E_ARCHER:
                case Map::Units::UT_E_XBOW:
                case Map::Units::UT_A_ARCHER:
                case Map::Units::UT_A_HARCHER:
                case Map::Units::UT_S_FBALLISTA:
                    _specificRange2 = 2916;
                    break;
                default:
                    _specificRange2 = 0;
                    break;
                case Map::Units::UT_S_CATAPULT:
                    _specificRange2 = 0x15f9;
                    break;
                case Map::Units::UT_S_TREBUCHET:
                case Map::Units::UT_S_BALLISTA:
                    _specificRange2 = 0x1c39;
                    break;
                case Map::Units::UT_S_MANGONEL:
                    _specificRange2 = 0x1324;
                    break;
                case Map::Units::UT_A_SLINGER:
                    _specificRange2 = 0x1e4;
                    break;
                case Map::Units::UT_A_FIRETHROWER:
                    _specificRange2 = 0x79;
                }
                _specificRange = DAT_ViewportRenderState::instance.viewportState.mouseX
                    - DAT_UnitsState::instance.units[(int)local_18].x;
                _shooterID = DAT_ViewportRenderState::instance.viewportState.mouseY
                    - DAT_UnitsState::instance.units[(int)local_18].y;
                if (_shooterID * _shooterID + _specificRange * _specificRange <= _specificRange2)
                    goto LAB_004367d0;
            LAB_00436953:
                DAT_TileMapState::instance.pendingUnitCommand = -1;
                DAT_TileMapState::instance.cursorOverlayImageBase = 0x41;
                DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                DAT_TileMapState::instance.DAT_SelectionIconType = 0x11;
                local_20 = 4;
            LAB_00436d33:
                _otherUnitIDUnk = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                if ((_otherUnitIDUnk) && (!bVar16)) {
                    DAT_TileMapState::instance.pendingUnitCommand = -1;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0x41;
                    DAT_TileMapState::instance.flagAnimationDivisor = 0x10;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0xac;
                    DAT_TileMapState::instance.DAT_SelectionIconType = 0x11;
                    local_20 = 4;
                }
            LAB_00436d8a:
                if (DAT_MouseState::instance.leftClickStart) {
                    DAT_00b98424::instance = 1;
                    if (((!local_20)
                            || (((local_20 == 2 && (!DAT_TileMapState::instance.cursorOverlayImageBase))
                                && (DAT_UnitsState::instance.unitControlsRelated != 5))))
                        && DAT_TileMapState::instance.pendingUnitCommand != 3
                        && DAT_TileMapState::instance.pendingUnitCommand != 4) {
                        MACRO_CALL_MEMBER(Input::MouseState_Func::beginPointSelectionBox, DAT_MouseState::ptr)();
                        _otherUnitIDUnk
                            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getUnitInHitBox, DAT_UnitsState::ptr)(5);
                        if (_otherUnitIDUnk) {
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectFirstUnitInDragBoxAnyPlayer, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(Input::MouseState_Func::beginPointSelectionBox, DAT_MouseState::ptr)();
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::selectFirstUnitInDragBoxAnyPlayer, DAT_UnitsState::ptr)();
                            DAT_UnitsState::instance.field49_0x608 = 0xffffffff;
                            if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                                DAT_UnitsState::instance.field49_0x608 = 0;
                            }
                            DAT_MouseState::instance.selectionBoxState = 1;
                            MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)();
                            DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                            DAT_UnitsState::instance.unitControlsRelated = TRUE;
                            DAT_TileMapState::instance.pendingUnitCommand = 0;
                            DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                            DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                            DAT_TileMapState::instance.shiftRelated0or3 = 0;
                        }
                    }
                    DAT_TileMapState::instance.field183_0x554a00
                        = DAT_ViewportRenderState::instance.viewportState.mouseX;
                    DAT_TileMapState::instance.instructionTargetX
                        = DAT_ViewportRenderState::instance.viewportState.mouseX;
                    DAT_TileMapState::instance.field184_0x554a04
                        = DAT_ViewportRenderState::instance.viewportState.mouseY;
                    DAT_TileMapState::instance.instructionTargetY
                        = DAT_ViewportRenderState::instance.viewportState.mouseY;
                    goto LAB_0043782c;
                }
                if ((DAT_MouseState::instance.leftClickState) && (DAT_00b98424::instance)) {
                    MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                    if ((!DAT_MouseState::instance.selectionBoxMode)
                        || (MACRO_CALL_MEMBER(Input::MouseState_Func::extendSelectionBoxToMouse, DAT_MouseState::ptr)(),
                            DAT_MouseState::instance.selectionBoxState == 0))
                        goto LAB_0043782c;
                    if (!DAT_ModifierKeyState::instance.shift) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                    }
                    DAT_TileMapState::instance.shiftRelated0or3 = -(uint)(DAT_ModifierKeyState::instance.shift) & 3;
                    DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                    DAT_UnitsState::instance.unitControlsRelated = TRUE;
                    DAT_TileMapState::instance.pendingUnitCommand = 0;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    DAT_GameCore::instance.menuSwitchDelay = -1;
                    if (0 < DAT_UnitsState::instance.totalUnitsInSelection
                        && DAT_MouseState::instance.leftClickStartMoment != -1
                        && (int)(DVar7 - DAT_MouseState::instance.leftClickStartMoment) < 0xc9)
                        goto LAB_0043782c;
                    if (DAT_TileMapState::instance.shiftRelated0or3 != 3) {
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::applyDragBoxSelectionByPriority, DAT_UnitsState::ptr)();
                        goto LAB_0043782c;
                    }
                    goto LAB_004377dc;
                }
                if ((!DAT_MouseState::instance.draggingStopped)
                    || (bVar18 = DAT_00b98424::instance == 0, DAT_00b98424::instance = 0, bVar18))
                    goto LAB_0043782c;
                _otherUnitIDUnk = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getSelectedLordIDIfOwnedByCurrentPlayer, DAT_UnitsState::ptr)();
                if ((_otherUnitIDUnk) && (!bVar16)) {
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                    goto LAB_0043782c;
                }
            }
            _setRallying = 0;
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
            _shooterID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
            switch (DAT_UnitsState::instance.unitControlsRelated) {
            case TRUE:
                if (DAT_TileMapState::instance.pendingUnitCommand == -10) {
                    if (bVar6) {
                        _noTextExtra.buildingType = (Commands::MappersEnum)0;
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 0x101, 0, _noTextExtra, 0x69, 2000);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                        goto LAB_0043782c;
                    }
                } else {
                    if (DAT_TileMapState::instance.pendingUnitCommand == 0xb)
                        goto LAB_00437671;
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
                        DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                        goto LAB_0043782c;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 0xc) {
                        /*
                          queueCommand: DISBAND/ATTACK UNITS
                         */
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0x22,
                            (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.somePitchDitchID)),
                            (undefined4)((int)(DAT_TileMapState::instance
                                    .pitchDitches[DAT_ViewportRenderState::instance.viewportState.somePitchDitchID]
                                    .uid)));
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playArcherCommandSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                        goto LAB_0043782c;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 1) {
                        uVar13 = 9;
                        goto LAB_004374dc;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand == 2) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0xf,
                            (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID)),
                            (undefined4)((int)(DAT_BuildingsState::instance
                                    .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                                    .uid)));
                        if ((DAT_BuildingsState::instance.buildings[_shooterID].buildingType
                                != Map::Buildings::BT_OILSMELTER)
                            || (_otherUnitIDUnk = MACRO_CALL_MEMBER(
                                    Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)(),
                                _otherUnitIDUnk == 0))
                            break;
                        if (DAT_BuildingsState::instance.buildings[_shooterID].currentEmployeeCount == 0) {
                            _otherUnitIDUnk = 0x1c;
                        } else {
                            _otherUnitIDUnk = 0x1d;
                        }
                    } else if (DAT_TileMapState::instance.pendingUnitCommand == 3) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0x10,
                            DAT_TileMapState::instance.instructionTargetUnitID,
                            (undefined4)((
                                int)(DAT_UnitsState::instance.units[DAT_TileMapState::instance.instructionTargetUnitID]
                                    .uid)));
                        _otherUnitIDUnk = 0x14;
                    } else {
                        if (DAT_TileMapState::instance.pendingUnitCommand != 4) {
                            if (DAT_TileMapState::instance.pendingUnitCommand == 5) {
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand3Params,
                                    DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0x18,
                                    (undefined4)((
                                        int)(DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile)));
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playWorkCommandSpeech,
                                    DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                                goto LAB_0043782c;
                            }
                            if (DAT_TileMapState::instance.pendingUnitCommand == 6) {
                                uVar13 = 0x17;
                                goto LAB_00437494;
                            }
                            if ((DAT_ViewportRenderState::instance.viewportState.field14_0x38)
                                && (_shooterID = MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                                    _shooterID != 0)) {
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                                    DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                    Map::Units::UIT_FILL_MOAT,
                                    (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseX)),
                                    (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseY)), 1000);
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitSelectSpeech,
                                    DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                                goto LAB_0043782c;
                            }
                            if ((DAT_ViewportRenderState::instance.viewportState.field16_0x40)
                                && (_shooterID = MACRO_CALL_MEMBER(
                                        Map::Units::UnitsState_Func::selectionHasFootSoldiers, DAT_UnitsState::ptr)(),
                                    _shooterID != 0)) {
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                                    DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                    Map::Units::UIT_DIG_MOAT,
                                    (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseX)),
                                    (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseY)), 1000);
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitSelectSpeech,
                                    DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                                goto LAB_0043782c;
                            }
                            if (!DAT_ModifierKeyState::instance.shift) {
                                DVar7 = timeGetTime();
                                _oneOr129 = 1;
                                if (DAT_00b98420::instance == DAT_ViewportRenderState::instance.viewportState.mouseX
                                    && DAT_00b9841c::instance == DAT_ViewportRenderState::instance.viewportState.mouseY
                                    && (_oneOr129 = 1, (int)(DVar7 - TIME_PreviousClick::instance) < 500)) {
                                    _oneOr129 = 129;
                                }
                                DAT_00b98420::instance = DAT_ViewportRenderState::instance.viewportState.mouseX;
                                DAT_00b9841c::instance = DAT_ViewportRenderState::instance.viewportState.mouseY;
                                TIME_PreviousClick::instance = DVar7;
                                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand, DAT_UnitsState::ptr)(
                                    DAT_TribesState::instance.DAT_CurrentTribeID,
                                    DAT_ViewportRenderState::instance.viewportState.mouseX,
                                    DAT_ViewportRenderState::instance.viewportState.mouseY,
                                    (int)(DAT_TribesState::instance.patrolButtonPressed), _oneOr129);
                                DAT_TribesState::instance.rallyCount = 2;
                                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                                goto LAB_0043782c;
                            }
                            /*
                              rallying shift == 1
                             */
                            if (!DAT_TribesState::instance.patrolButtonPressed) {
                                if (9 < DAT_TribesState::instance.rallyCount)
                                    goto LAB_00437357;
                                if (DAT_TribesState::instance.rallyCount == 1) {
                                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand,
                                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                        DAT_ViewportRenderState::instance.viewportState.mouseX,
                                        DAT_ViewportRenderState::instance.viewportState.mouseY, -1, 1);
                                    DAT_TribesState::instance.rallyCount = DAT_TribesState::instance.rallyCount + 1;
                                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                                    goto LAB_0043782c;
                                }
                            } else {
                                _setRallying = 1;
                                /*
                                  Do rally point clicking?
                                 */
                                if (DAT_TribesState::instance.rallyCount < 10) {
                                    /*
                                      fixme: rallyCount is never set back to 1 if the unit group keeps being   selected
                                     */
                                    if (DAT_TribesState::instance.rallyCount == 1) {
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand,
                                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                                            DAT_ViewportRenderState::instance.viewportState.mouseX,
                                            DAT_ViewportRenderState::instance.viewportState.mouseY,
                                            (int)(DAT_TribesState::instance.patrolButtonPressed), 1);
                                        DAT_TribesState::instance.rallyCount = DAT_TribesState::instance.rallyCount + 1;
                                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(1);
                                        goto LAB_0043782c;
                                    }
                                } else {
                                LAB_00437357:
                                    DAT_TribesState::instance.rallyCount = 9;
                                }
                            }
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::extendRallyPoint, DAT_UnitsState::ptr)(
                                DAT_TribesState::instance.DAT_CurrentTribeID,
                                DAT_ViewportRenderState::instance.viewportState.mouseX,
                                DAT_ViewportRenderState::instance.viewportState.mouseY,
                                (int)(DAT_TribesState::instance.rallyCount));
                            DAT_TribesState::instance.rallyCount = DAT_TribesState::instance.rallyCount + 1;
                            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(_setRallying);
                            goto LAB_0043782c;
                        }
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, DAT_TileMapState::instance.instructionTargetUnitID,
                            (undefined4)((
                                int)(DAT_UnitsState::instance.units[DAT_TileMapState::instance.instructionTargetUnitID]
                                    .uid)),
                            0);
                        _otherUnitIDUnk = 0x16;
                    }
                LAB_004376a4:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                        _otherUnitIDUnk);
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
                DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                DAT_UnitsState::instance.unitControlsRelated = TRUE;
                DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                goto LAB_0043782c;
            case 5:
                if (local_20 == 2) {
                    if (DAT_TileMapState::instance.pendingUnitCommand == 6) {
                        uVar13 = 0x23;
                    LAB_00437494:
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitMoveSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand3Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            (undefined4)((int)(uVar13)),
                            (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile)));
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                        goto LAB_0043782c;
                    }
                    if (DAT_TileMapState::instance.pendingUnitCommand != 1) {
                        DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::giveMoveCommand, DAT_UnitsState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID,
                            DAT_ViewportRenderState::instance.viewportState.mouseX,
                            DAT_ViewportRenderState::instance.viewportState.mouseY, 0, 0);
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID,
                            Map::Units::UIT_ATTACK_LAND, DAT_TileMapState::instance.instructionTargetX,
                            DAT_TileMapState::instance.instructionTargetY,
                            DAT_TileMapState::instance.field185_0x554a08);
                        DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                        DAT_UnitsState::instance.unitControlsRelated = TRUE;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                        DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playUnitMoveSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                        goto LAB_0043782c;
                    }
                    uVar13 = 0x24;
                LAB_004374dc:
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, (undefined4)((int)(uVar13)),
                        (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID)),
                        (undefined4)((int)(DAT_BuildingsState::instance
                                .buildings[DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID]
                                .uid)));
                    if ((!_shooterID)
                        || (DAT_BuildingsState::instance.buildings[_shooterID].buildingType
                            != Map::Buildings::BT_PITCHDITCH)) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playAttackCommandFeedback,
                            DAT_TribesState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                    } else {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playArcherCommandSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                    }
                    goto LAB_0043782c;
                }
                break;
            case 0x14:
                if (local_20 != 3) {
                    DAT_UnitsState::instance.pendingUnitControlMode = 0x14;
                LAB_00437671:
                    DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 0x14,
                        (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseX)),
                        (undefined4)((int)(DAT_ViewportRenderState::instance.viewportState.mouseY)));
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    _otherUnitIDUnk = 0x17;
                    goto LAB_004376a4;
                }
                break;
            case 0x16:
                if (DAT_TileMapState::instance.pendingUnitCommand != -1) {
                    DAT_UnitsState::instance.unitControlsRelated = DAT_UnitsState::instance.pendingUnitControlMode;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand5Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, Map::Units::UIT_THROW_COW,
                        DAT_TileMapState::instance.instructionTargetX, DAT_TileMapState::instance.instructionTargetY,
                        DAT_TileMapState::instance.field185_0x554a08);
                    DAT_UnitsState::instance.pendingUnitControlMode = TRUE;
                    DAT_UnitsState::instance.unitControlsRelated = TRUE;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = 0x6b;
                    _shooterID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
                    if ((_shooterID)
                        && (DAT_UnitsState::instance.units[_shooterID]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            != 0)) {
                        _otherUnitIDUnk = 0x1e;
                        goto LAB_004376a4;
                    }
                }
            }
            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
        LAB_0043782c:
            switch (local_20) {
            case 0:
                DAT_MouseState::instance.field68_0x1dc = 1;
                return;
            case 1:
                DAT_MouseState::instance.field68_0x1dc = 2;
                return;
            case 2:
                DAT_MouseState::instance.field68_0x1dc = 3;
                return;
            case 3:
                DAT_MouseState::instance.field68_0x1dc = 4;
                return;
            case 4:
                DAT_MouseState::instance.field68_0x1dc = 5;
                break;
            case -1:
                DAT_MouseState::instance.field68_0x1dc = 0;
            }
        }

    }
}
}
