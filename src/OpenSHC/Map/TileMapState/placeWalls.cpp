
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00502F30
    void TileMapState::placeWalls(
        int playerID, uint x1, uint y1, uint x2, uint y2, MappersEnum wallType, int tileCountUnk)
    {
        int budget = 0;
        int wallCount = 0;
        int placed = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateWallBuildPath, this)(playerID, x1, y1, x2, y2, wallType);
        if (this->illegalBuild != FALSE) {
            return;
        }

        this->constructionTileCount = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(
            playerID, 4);
        int overshoot = 2;
        if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
            budget = this->field119_0x554924;
        }
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::resetWallPlacementInfo, DAT_WallAndPitchState::ptr)();
        }

        int upY = y1 - y2;
        int downY = y2 - y1;
        int rightX = x2 - x1;
        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        uint x = x1;
        int leftX = x1 - x2;
        bool stairAborted = false;
        do {
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR && budget < 0x18) {
                stairAborted = true;
                break;
            }
            if (tileCountUnk <= placed || this->constructionTileCount < wallCount) {
                break;
            }
            placed++;
            int tile = *translation + x;
            bool towerNeighbours = false;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR
                && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                stairAborted = true;
                break;
            }
            /* a wall dragged over a crenel replaces it without counting against the tally */
            bool overCrenel = false;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_WALL && (this->LogicLayer[tile] & L_CRENEL) != 0) {
                overCrenel = true;
            }
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0 || this->DamageLayer[tile] != 0 || overCrenel) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::addWallPlacementInfoForTile, DAT_WallAndPitchState::ptr)(tile);
                }
                if (this->DamageLayer[tile] != 0 || overCrenel) {
                    this->DamageLayer[tile] = 0;
                    this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                    if (overCrenel) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_CRENEL | L_CRENEL_VARIATIONUnk)
                            | L_WALL_OR_GATEHOUSE;
                    }
                }

                bool applyWall = true;
                bool updateLinkages = true;
                if ((short)wallType == OpenSHC::Commands::M_MAPPER_WALL) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x5a;
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x3c;
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_CRENAL) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL;
                    BOOLEnum onlyTowers = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::hasOnlyTowerNeighborsNoWalls, this)(tile, y1);
                    if (onlyTowers == FALSE) {
                        this->HeightLayer[tile] = this->HeightLayer[tile] + 0x62;
                    } else {
                        this->HeightLayer[tile] = this->HeightLayer[tile] + 0x44;
                    }
                    towerNeighbours = onlyTowers != FALSE;
                    /* a crenel on an odd tile of one axis carries the alternate variation */
                    if (((x & 1) == 0) != ((y1 & 1) == 0)) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL_VARIATIONUnk;
                    }
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
                    int steps = (budget - (int)(uint)this->HeightLayer[tile]) + -0x10;
                    if (steps > 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_STAIRS;
                        this->HeightLayer[tile] = this->HeightLayer[tile] + (char)steps;
                    } else {
                        applyWall = false;
                        updateLinkages = overCrenel;
                    }
                }

                if (applyWall && !overCrenel) {
                    wallCount++;
                    this->LogicLayer[tile]
                        = this->LogicLayer[tile] & ~(L_UNKNOWN_WALL_RELATED | L_BOULDERS | L_PEBBLES | L_IRON)
                        | L_WALL_OR_GATEHOUSE;
                    if (this->UnitLayer[tile] != 0
                        && DAT_UnitsState::instance.units[(short)this->UnitLayer[tile]].unitType == OpenSHC::Map::Units::UT_CHICKEN) {
                        int unitID = (short)this->UnitLayer[tile];
                        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                        DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                        DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0;
                    }
                    if ((this->LogicLayer[tile] & L_PLAIN2_AND_PITCH) != 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_PLAIN2_AND_PITCH;
                        this->HeightLayer[tile] = this->HeightLayer[tile] + 4;
                    }
                    if ((this->LogicLayer[tile] & L_TREE) != 0 && this->OrganismLayer[tile] < 2000) {
                        /* scrub is flattened by the wall, a real tree is left standing */
                        switch (DAT_LandscapeState::instance.trees[this->OrganismLayer[tile]].treeType) {
                        case (TreeType)5:
                        case (TreeType)6:
                        case (TreeType)7:
                        case (TreeType)8:
                        case (TreeType)9:
                        case (TreeType)0xa:
                        case (TreeType)0xb:
                        case (TreeType)0xc:
                        case (TreeType)0xd:
                        case (TreeType)0xe:
                        case (TreeType)0x10:
                        case (TreeType)0x11:
                        case (TreeType)0x12:
                        case (TreeType)0x13:
                            DAT_LandscapeState::instance.trees[this->OrganismLayer[tile]].state = 3;
                        }
                    }
                    if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL || towerNeighbours) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_UNKNOWN_WALL_RELATED;
                    }
                    this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | (char)playerID - 1U;
                }
                if (updateLinkages) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(
                        y1, tile);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoat, this)(tile);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(7, x, y1);
                }
            }

            int stepX = leftX;
            if ((int)x < (int)x2) {
                stepX = rightX;
            }
            int stepY = upY;
            if ((int)y1 < (int)y2) {
                stepY = downY;
            }
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
                if (stepY < stepX) {
                    if ((int)x < (int)x2) {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    } else {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    }
                } else if (stepY < 1) {
                    overshoot = overshoot - 1;
                } else if ((int)y1 < (int)y2) {
                    y1 = y1 + 1;
                    translation = translation + 3;
                    upY = upY + 1;
                    downY = downY - 1;
                } else {
                    y1 = y1 - 1;
                    translation = translation - 3;
                    upY = upY - 1;
                    downY = downY + 1;
                }
            } else {
                if (stepX != 0) {
                    int advance = 1;
                    if ((int)x < (int)x2) {
                        leftX = leftX + 1;
                        rightX = rightX - 1;
                    } else {
                        leftX = leftX - 1;
                        advance = -1;
                        rightX = rightX + 1;
                    }
                    x = x + advance;
                }
                if (stepY != 0) {
                    if ((int)y1 < (int)y2) {
                        y1 = y1 + 1;
                        translation = translation + 3;
                        upY = upY + 1;
                        downY = downY - 1;
                    } else {
                        y1 = y1 - 1;
                        translation = translation - 3;
                        upY = upY - 1;
                        downY = downY + 1;
                    }
                }
                if (x == x2 && y1 == y2) {
                    overshoot = overshoot - 1;
                }
            }
            if (budget > 0xf) {
                budget = budget - 0x10;
            }
        } while (x != x2 || y1 != y2 || overshoot != 0);

        int woodCount;
        int stoneCount;
        if (!stairAborted && (short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL) {
            stoneCount = 0;
            woodCount = wallCount;
        } else {
            woodCount = 0;
            stoneCount = wallCount;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss, DAT_BuildingsState::ptr)(
            playerID, stoneCount, woodCount, 0);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        this->field204_0x554a30 = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
