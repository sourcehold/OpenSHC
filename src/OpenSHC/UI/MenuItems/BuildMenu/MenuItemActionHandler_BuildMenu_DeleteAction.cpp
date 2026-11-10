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
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

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
        namespace BuildMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x004387D0
            void MenuItemActionHandler_BuildMenu_DeleteAction(int param_1, ...)
            {
                if (DAT_GameSynchronyState::instance.syncStatus != 0
                    || DAT_GameSynchronyState::instance.saveRelated != 0
                    || DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_DELETE) {
                    return;
                }
                DAT_TileMapState::instance.demolishBlocked = 0;
                if (!DAT_ViewportRenderState::instance.viewportState.field_0x0) {
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                int const tileX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                int const tileY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                DAT_TileMapState::instance.DAT_ClickedTileX = tileX;
                DAT_TileMapState::instance.DAT_ClickedTileY = tileY;
                if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT) {
                    // The cursor shows the delete as blocked with an enemy within 30 (15 outside a solitary game).
                    // The distance is set before the call (in the call: quick_diff 0.9679 -> 0.9116)
                    int requiredDistance;
                    if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                        requiredDistance = 15;
                    } else {
                        requiredDistance = 30;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                            DAT_PathFindingState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, tileX, tileY, requiredDistance)) {
                        DAT_TileMapState::instance.demolishBlocked = 1;
                    }
                }
                // Without a new click, deleting goes on only while the button is held over a wall or moat; otherwise
                // both flags are cleared and nothing is deleted.
                if (!DAT_MouseState::instance.leftClickStart
                    && ((!DAT_TileMapState::instance.placementOnWall && !DAT_TileMapState::instance.placementOnMoat)
                        || !DAT_MouseState::instance.leftClickState)) {
                    DAT_TileMapState::instance.placementOnWall = 0;
                    DAT_TileMapState::instance.placementOnMoat = 0;
                    return;
                }
                if (DAT_GameCore::instance.solitaryAltUDungeon
                    && DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID != 0) {
                    int const unitID = DAT_ViewportRenderState::instance.viewportState.mouseRayUnitID;
                    if (DAT_UnitsState::instance.units[unitID].health != 0
                        && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_LORD
                        && !DAT_UnitsState::instance.units[unitID].dying
                        && DAT_UnitsState::instance.units[unitID].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        // Two sums terrain first, the binary's load order (the draft's order: reccmp 100.0% -> 97.6%)
                        if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                            && DAT_UnitsState::instance.units[unitID].resourceToDeposit != 0) {
                            MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(
                                DAT_UnitsState::instance.units[unitID].owner,
                                DAT_UnitsState::instance.units[unitID].microXPosition,
                                DAT_UnitsState::instance.units[unitID].microYPosition,
                                DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                                    + DAT_UnitsState::instance.units[unitID].buildingHeight - 8,
                                5);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                                DAT_EntityState::ptr)(0, DAT_UnitsState::instance.units[unitID].owner, 0,
                                DAT_UnitsState::instance.units[unitID].microXPosition,
                                DAT_UnitsState::instance.units[unitID].microYPosition,
                                DAT_UnitsState::instance.units[unitID].buildingHeight
                                    + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight,
                                0, 0, 0, OpenSHC::Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                        }
                        DAT_UnitsState::instance.units[unitID].dying = 1;
                        DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging = 1;
                        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                        // EntityType has no constant for 30.
                        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                            DAT_EntityState::ptr)(0, 0, 0, DAT_UnitsState::instance.units[unitID].microXPosition,
                            DAT_UnitsState::instance.units[unitID].microYPosition,
                            DAT_UnitsState::instance.units[unitID].buildingHeight
                                + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight,
                            DAT_UnitsState::instance.units[unitID].microXPosition + 1,
                            DAT_UnitsState::instance.units[unitID].microYPosition + 1,
                            DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight
                                + DAT_UnitsState::instance.units[unitID].buildingHeight,
                            (OpenSHC::Map::Entities::EntityType)30, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                            OpenSHC::DE::SHCDE::FX_DEATH_CLUB2);
                        return;
                    }
                }
                DAT_TileMapState::instance.buildingPlacementFailReason
                    = Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::spreadFlagPlacementAlgorithm,
                        DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY)) {
                    DAT_WallAndPitchState::instance.countdown = 0;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                        = DAT_TileMapState::instance.DAT_ClickedTileX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_TileMapState::instance.DAT_ClickedTileY;
                    // GameCommandType has no constant for 97.
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)((OpenSHC::Commands::GameCommandType)97);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::evaluateBuildingPlacementAtCursor,
                    DAT_TileMapState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    DAT_TileMapState::instance.DAT_ClickedTileX, DAT_TileMapState::instance.DAT_ClickedTileY);
                if (DAT_TileMapState::instance.buildingPlacementFail != 0) {
                    // BuildingFailReasonEnum has no constant for 1000.
                    if (DAT_TileMapState::instance.buildingPlacementFailReason == 1000) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_MISC2, 2, 0, 100, 6000);
                    } else if (DAT_TileMapState::instance.buildingPlacementFailReason
                        != Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                            DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_PANEL_FEEDBACK,
                            DAT_TileMapState::instance.buildingPlacementFailReason, 0, 100, 6000);
                    }
                    return;
                }
                DAT_WallAndPitchState::instance.countdown = 0;
                int tile;
                if (DAT_TileMapState::instance.placementOnMoat) {
                    tile = DAT_TileMapState::instance.savedCursorTile;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = -1;
                } else {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 50;
                    if (!DAT_TileMapState::instance.placementOnWall) {
                        int const targetID = DAT_TileMapState::instance.cursorTargetID;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = targetID;
                        if (targetID < 0) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_TileMapState::instance.pitchDitches[-targetID].uid;
                        } else {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_BuildingsState::instance.buildings[targetID].uid;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_DESTROY_BUILDING);
                        return;
                    }
                    tile = DAT_ViewportRenderState::instance.viewportState.cursorWallTile;
                }
                DAT_TileMapState::instance.MiscDisplayLayer[tile] |= 1024;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = tile;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_DESTROY2Unk);
            }

        }
    }
}
}
