#include "../BuildMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_0053f088.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using Commands::MappersEnum;
        using DE::SHCDE::eSFX;
        using Game::GameMode;
        using Game::GameMode2;
        using Map::Buildings::BuildingFailReasonEnum;
        using Map::Entities::EntityType;
        using Map::Units::UnitType;
        using Map::Units::UnitTypeShort;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004387D0
        void BuildMenu::MenuItemActionHandler_BuildMenu_DeleteAction(int param_1, ...)
        {
            UI::TextMessageBLLookupStructUnion _noBlLookup;
            _noBlLookup.buildingType = (Commands::MappersEnum)0;
            int totalHeight;
            BOOLEnum BVar1;
            int _unitOwner;
            int iVar2;
            int microY;
            int microX;
            UnitTypeShort _unitType;
            if (!DAT_GameSynchronyState::instance.syncStatus && !DAT_GameSynchronyState::instance.saveRelated
                && DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_DELETE
                && (DAT_TileMapState::instance.demolishBlocked = 0,
                    DAT_ViewportRenderState::instance.viewportState.field0_0x0 != 0)) {
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                DAT_TileMapState::instance.DAT_ClickedTileX
                    = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.DAT_ClickedTileY
                    = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                    && (BVar1 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                            DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (uint)(DAT_ViewportRenderState::instance.viewportState.mouseTileX),
                            (uint)(DAT_ViewportRenderState::instance.viewportState.mouseTileY),
                            (int)((-(uint)(DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                                      & 0xfffffff1)
                                + 0x1e)),
                        BVar1)) {
                    DAT_TileMapState::instance.demolishBlocked = 1;
                }
                iVar2 = DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID;
                if (!DAT_MouseState::instance.leftClickStart
                    && ((!DAT_TileMapState::instance.placementOnWall && (!DAT_TileMapState::instance.placementOnMoat))
                        || (!DAT_MouseState::instance.leftClickState))) {
                    DAT_TileMapState::instance.placementOnWall = 0;
                    DAT_TileMapState::instance.placementOnMoat = 0;
                    return;
                }
                if (DAT_GameCore::instance.solitaryAltUDungeon
                    && DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID
                    && DAT_UnitsState::instance.units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                            .health
                        != 0
                    && (_unitType
                        = DAT_UnitsState::instance.units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                            .unitType,
                        _unitType != Map::Units::UT_LORD
                            && (DAT_UnitsState::instance
                                    .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                                    .dying
                                == 0))
                    && (_unitOwner = (int)DAT_UnitsState::instance
                            .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                            .owner,
                        _unitOwner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                            && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY))) {
                    if ((_unitType == Map::Units::UT_E_ENGINEER)
                        && (DAT_UnitsState::instance
                                .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                                .resourceToDeposit
                            != 0)) {
                        MACRO_CALL(Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(_unitOwner,
                            (int)(DAT_UnitsState::instance
                                    .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                                    .microXPosition),
                            (int)(DAT_UnitsState::instance
                                    .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                                    .microYPosition),
                            (int)(DAT_UnitsState::instance
                                      .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                                      .buildingHeight
                                + -8
                                + DAT_UnitsState::instance
                                    .units[DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID]
                                    .terrainOrClimbHeight),
                            5);
                        MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(
                            0, (undefined4)((int)(DAT_UnitsState::instance.units[iVar2].owner)), 0,
                            (int)(DAT_UnitsState::instance.units[iVar2].microXPosition),
                            (int)(DAT_UnitsState::instance.units[iVar2].microYPosition),
                            (int)(DAT_UnitsState::instance.units[iVar2].buildingHeight
                                + DAT_UnitsState::instance.units[iVar2].terrainOrClimbHeight),
                            0, 0, 0, (EntityType)((int)(26)), 0);
                    }
                    totalHeight = (int)DAT_UnitsState::instance.units[iVar2].buildingHeight
                        + (int)DAT_UnitsState::instance.units[iVar2].terrainOrClimbHeight;
                    microY = (int)DAT_UnitsState::instance.units[iVar2].microYPosition;
                    microX = (int)DAT_UnitsState::instance.units[iVar2].microXPosition;
                    DAT_UnitsState::instance.units[iVar2].dying = 1;
                    DAT_UnitsState::instance.units[iVar2].tunnelerFinishedDigging = 1;
                    DAT_UnitsState::instance.units[iVar2].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[iVar2].state.generic = Map::Units::States::US_STONE_DEATH_01;
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                        0, 0, microX, microY, totalHeight, microX + 1, microY + 1, totalHeight, ((EntityType)0x1e), 0);
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar2].x, (int)(DAT_UnitsState::instance.units[iVar2].y),
                        DE::SHCDE::FX_DEATH_CLUB2);
                    return;
                }
                DAT_TileMapState::instance.buildingPlacementFailReason
                    = Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                iVar2 = MACRO_CALL_MEMBER(Map::TileMapState_Func::spreadFlagPlacementAlgorithm, DAT_TileMapState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (uint)(DAT_TileMapState::instance.DAT_ClickedTileX),
                    (uint)(DAT_TileMapState::instance.DAT_ClickedTileY));
                if (iVar2) {
                    DAT_WallAndPitchState::instance.countdown = 0;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        ((GameCommandType)0x61));
                    return;
                }
                MACRO_CALL_MEMBER(Map::TileMapState_Func::evaluateBuildingPlacementAtCursor, DAT_TileMapState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (uint)(DAT_TileMapState::instance.DAT_ClickedTileX),
                    (uint)(DAT_TileMapState::instance.DAT_ClickedTileY));
                if (!DAT_TileMapState::instance.buildingPlacementFail) {
                    DAT_WallAndPitchState::instance.countdown = 0;
                    if (!DAT_TileMapState::instance.placementOnMoat) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 50;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_ViewportRenderState::instance.viewportState.cursorWallTile;
                        if (!DAT_TileMapState::instance.placementOnWall) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                                = DAT_TileMapState::instance.cursorTargetID;
                            if (-1 < DAT_TileMapState::instance.cursorTargetID) {
                                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                    = DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.cursorTargetID]
                                          .uid;
                                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                    DAT_GameSynchronyState::ptr)(Commands::GCT_DESTROY_BUILDING);
                                return;
                            }
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = *(int*)(DAT_0053f088::ptr + DAT_TileMapState::instance.cursorTargetID * -0x14
                                    + (int)DAT_TileMapState::instance.directionTranslationMatrix);
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_DESTROY_BUILDING);
                            return;
                        }
                    } else {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0xffffffff;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_TileMapState::instance.savedCursorTile;
                    }
                    DAT_TileMapState::instance.MiscDisplayLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        = DAT_TileMapState::instance
                              .MiscDisplayLayer[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        | 0x400;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_DESTROY2Unk);
                } else {
                    if (DAT_TileMapState::instance.buildingPlacementFailReason == (BuildingFailReasonEnum)1000) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 0x101, 2, _noBlLookup, 100, 6000);
                        return;
                    }
                    if (DAT_TileMapState::instance.buildingPlacementFailReason
                        != Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                        MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d,
                            (int)(DAT_TileMapState::instance.buildingPlacementFailReason), _noBlLookup, 100, 6000);
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
