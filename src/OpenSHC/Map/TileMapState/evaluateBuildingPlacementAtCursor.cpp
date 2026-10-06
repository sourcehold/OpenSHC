
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00504A30
    void TileMapState::evaluateBuildingPlacementAtCursor(int playerID, uint x, uint y)
    {
        uint anchorX = x;
        int moatTile = 0;
        if (y > 399 || x > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            this->buildingPlacementFail = TRUE;
            return;
        }
        this->buildingPlacementFail = FALSE;
        if (DAT_ViewportRenderState::instance.viewportState.field15_0x3c != 0) {
            moatTile = DAT_ViewportRenderState::instance.viewportState.field24_0x60;
            this->field153_0x5549a0 = DAT_ViewportRenderState::instance.viewportState.field24_0x60;
        }

        /* the flat view has no ray hit, so the tile under the mouse is used directly */
        uint buildingID;
        int wallTile = DAT_ViewportRenderState::instance.viewportState.field21_0x54;
        if (this->flatViewToggleValue1 == 0) {
            buildingID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
        } else {
            buildingID = this->BuildingLayer[DAT_ViewportRenderState::instance.viewportState.mouseTile];
            wallTile = 0;
            if ((DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseTile] & L_WALL_OR_GATEHOUSE) != 0
                && ((DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseTile] & L_STOCKPILEUnk) == 0 || buildingID == 0)) {
                DAT_ViewportRenderState::instance.viewportState.field21_0x54 = DAT_ViewportRenderState::instance.viewportState.mouseTile;
                wallTile = DAT_ViewportRenderState::instance.viewportState.mouseTile;
            }
        }
        if (buildingID != 0) {
            anchorX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            y = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
        }

        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk, DAT_PathFindingState::ptr)(playerID, anchorX, y,
                   (-(uint)(DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) & 0xfffffff1) + 0x1e)
                != FALSE) {
            this->field194_0x554a20 = 1;
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x14;
            if (buildingID != 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].owner == playerID || playerID == 0) {
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x14;
            this->field194_0x554a20 = 1;
                    return;
                }
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                return;
            }
            if (wallTile > 0) {
                if ((this->LogicLayer[wallTile] & L_WALL_OR_GATEHOUSE) == 0
                    || (this->WallOwnerLayer[wallTile] & 7) + 1 == playerID) {
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x14;
            this->field194_0x554a20 = 1;
                    return;
                }
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                return;
            }
            if (moatTile > 0 && (this->LogicLayer[moatTile] & L_MOAT) != 0) {
                int moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(moatTile);
                if (moatID == 0) {
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    return;
                }
            }
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
            return;
        }

        if (DAT_ViewportRenderState::instance.viewportState.somePitchDitchID != 0) {
            if (this->pitchDitches[DAT_ViewportRenderState::instance.viewportState.somePitchDitchID].owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                this->buildingPlacementFail = TRUE;
                return;
            }
            this->field131_0x554954 = -DAT_ViewportRenderState::instance.viewportState.somePitchDitchID;
            return;
        }

        if ((int)buildingID < 1
            || (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID && playerID != 0)) {
            this->buildingPlacementFail = TRUE;
        }

        bool checkMoat = true;
        if (wallTile > 0) {
            /* a stockpile tile carries the wall flag too, but nothing may be built on it */
            if ((this->LogicLayer[wallTile] & L_WALL_OR_GATEHOUSE) != 0
                && (this->LogicLayer[wallTile] & L_STOCKPILEUnk) != 0) {
                this->buildingPlacementFail = TRUE;
                return;
            }
            if ((this->LogicLayer[wallTile] & L_WALL_OR_GATEHOUSE) != 0 && this->BuildingLayer[wallTile] == 0
                && this->field152_0x55499c == 0) {
                if ((this->WallOwnerLayer[wallTile] & 7) + 1 != playerID) {
                    return;
                }
                this->buildingPlacementFail = FALSE;
                this->field151_0x554998 = 1;
                if ((this->MiscDisplayLayer[wallTile] & 0x400) != 0) {
                    this->buildingPlacementFail = TRUE;
                }
                checkMoat = false;
            }
        }
        if (checkMoat) {
            if (moatTile < 1 || (this->LogicLayer[moatTile] & L_MOAT) == 0 || buildingID != 0) {
                if (this->field151_0x554998 != 0 || this->field152_0x55499c != 0) {
                    this->buildingPlacementFail = TRUE;
                }
            } else if (this->field151_0x554998 == 0) {
                int moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(moatTile);
                if (moatID == 0) {
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    return;
                }
                this->field152_0x55499c = 1;
                this->buildingPlacementFail = (BOOLEnum)((this->MiscDisplayLayer[moatTile] & 0x400) != 0);
                wallTile = moatTile;
            } else {
                this->buildingPlacementFail = TRUE;
            }
        }

        if (wallTile > 0 && this->UnitLayer[wallTile] != 0) {
            this->buildingPlacementFail = TRUE;
        }
        if (buildingID != 0) {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST) {
                        this->buildingPlacementFail = TRUE;
                    }
                } else {
                    switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                    case OpenSHC::Map::Buildings::BT_UNKNOWN1:
                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    case OpenSHC::Map::Buildings::BT_SIGNPOST:
                    case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                    case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
                    case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
                    case OpenSHC::Map::Buildings::BT_KEEPDOOR:
                    case OpenSHC::Map::Buildings::BT_POND:
                        this->buildingPlacementFail = TRUE;
                    }
                }
            }
            if ((int)buildingID < 0) {
                this->field131_0x554954 = buildingID;
                return;
            }
        }

        if ((this->LogicLayer[DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted]
                & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE))
                == 0
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_WOODGATE1
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_WOODGATE2
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KEEPDOOR
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_DRAWBRIDGE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT
            && this->field151_0x554998 == 0 && this->field152_0x55499c == 0) {
            this->buildingPlacementFail = TRUE;
        }
        this->field131_0x554954 = buildingID;
    }

}
}
