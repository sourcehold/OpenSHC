#include "../TileMapState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
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
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x00502F30
    void TileMapState::placeWalls(
        int playerID, uint x1, uint y1, uint x2, uint y2, MappersEnum wallType, int tileCountUnk)
    {
        int budget = 0;
        int wallCount = 0;
        int placed = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateWallBuildPath, this)(
            playerID, x1, y1, x2, y2, wallType);
        if (this->illegalBuild != FALSE) {
            return;
        }

        this->constructionTileCount = MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(playerID, 4);
        int overshoot = 2;
        if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
            budget = this->maxWallHeightInPath;
        }
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::WallAndPitchState_Func::resetWallPlacementInfo, DAT_WallAndPitchState::ptr)();
        }

        int upY = y1 - y2;
        int leftX = x1 - x2;
        int downY = y2 - y1;
        int rightX = x2 - x1;
        uint x = x1;
        uint y = y1;
        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        while (true) {
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR && budget < 24) {
                break;
            }
            if (placed >= tileCountUnk || wallCount > (int)this->constructionTileCount) {
                break;
            }
            placed++;
            int const tile = *translation + x;
            BOOLEnum towerNeighbours = FALSE;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR
                && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                break;
            }
            BOOLEnum applyWall = FALSE;
            // a wall dragged over a crenel replaces it without counting against the tally
            BOOLEnum overCrenel = FALSE;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_WALL && (this->LogicLayer[tile] & L_CRENEL) != 0) {
                overCrenel = TRUE;
            }
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0 || this->DamageLayer[tile] != 0 || overCrenel) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::addWallPlacementInfoForTile,
                        DAT_WallAndPitchState::ptr)(tile);
                }
                if (!overCrenel) {
                    applyWall = TRUE;
                }
                if (this->DamageLayer[tile] != 0 || overCrenel) {
                    this->DamageLayer[tile] = 0;
                    this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                    if (overCrenel) {
                        this->LogicLayer[tile]
                            = this->LogicLayer[tile] & ~(L_CRENEL | L_CRENEL_VARIATIONUnk) | L_WALL_OR_GATEHOUSE;
                    }
                }

                if ((short)wallType == OpenSHC::Commands::M_MAPPER_WALL) {
                    this->HeightLayer[tile] += 90;
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL) {
                    this->HeightLayer[tile] += 60;
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_CRENAL) {
                    this->LogicLayer[tile] |= L_CRENEL;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::hasOnlyTowerNeighborsNoWalls, this)(
                            tile, y)) {
                        this->HeightLayer[tile] += 68;
                        towerNeighbours = TRUE;
                    } else {
                        this->HeightLayer[tile] += 98;
                    }
                    // a crenel on an odd tile of one axis carries the alternate variation
                    if ((x & 1) != 0 && (y & 1) == 0) {
                        this->LogicLayer[tile] |= L_CRENEL_VARIATIONUnk;
                    } else if ((x & 1) == 0 && (y & 1) != 0) {
                        this->LogicLayer[tile] |= L_CRENEL_VARIATIONUnk;
                    }
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
                    int const steps = budget - this->HeightLayer[tile] - 16;
                    if (steps > 0) {
                        this->LogicLayer[tile] |= L_STAIRS;
                        this->HeightLayer[tile] += (char)steps;
                    } else {
                        applyWall = FALSE;
                    }
                }

                if (applyWall || overCrenel) {
                    if (applyWall && !overCrenel) {
                        wallCount++;
                        this->LogicLayer[tile]
                            = this->LogicLayer[tile] & ~(L_UNKNOWN_WALL_RELATED | L_BOULDERS | L_PEBBLES | L_IRON)
                            | L_WALL_OR_GATEHOUSE;
                        ushort const unit = this->UnitLayer[tile];
                        if (unit != 0
                            && DAT_UnitsState::instance.units[(short)unit].unitType
                                == OpenSHC::Map::Units::UT_CHICKEN) {
                            DAT_UnitsState::instance.units[(short)unit].state.generic
                                = OpenSHC::Map::Units::States::US_DISAPPEAR;
                            DAT_UnitsState::instance.units[(short)unit].updateTickTracker = 0;
                            DAT_UnitsState::instance.units[(short)unit].disappearFadeAlphaCountdown = 0;
                        }
                        if ((this->LogicLayer[tile] & L_PLAIN2_AND_PITCH) != 0) {
                            this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                            this->HeightLayer[tile] += 4;
                        }
                        if ((this->LogicLayer[tile] & L_TREE) != 0) {
                            int const organism = this->OrganismLayer[tile];
                            if (organism < 2000) {
                                // scrub is flattened by the wall, a real tree is left standing
                                switch (DAT_LandscapeState::instance.trees[organism].treeType) {
                                case OpenSHC::Map::Trees::TT_UNKNOWN_5:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_6:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_7:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_8:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_9:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_10:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_11:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_12:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_13:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_14:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_16:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_17:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_18:
                                case OpenSHC::Map::Trees::TT_UNKNOWN_19:
                                    DAT_LandscapeState::instance.trees[organism].state = 3;
                                }
                            }
                        }
                        if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL || towerNeighbours) {
                            this->LogicLayer[tile] |= L_UNKNOWN_WALL_RELATED;
                        }
                        this->WallOwnerLayer[tile] = (this->WallOwnerLayer[tile] & 0xf8) | (playerID - 1);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(y, tile);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoat, this)(tile);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                        DAT_PathFindingState::ptr)(7, x, y);
                }
            }

            int const stepX = (int)x >= (int)x2 ? leftX : rightX;
            int const stepY = (int)y >= (int)y2 ? upY : downY;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
                if (stepX > stepY) {
                    if ((int)x >= (int)x2) {
                        leftX -= 1;
                        x -= 1;
                        rightX += 1;
                    } else {
                        leftX += 1;
                        x += 1;
                        rightX -= 1;
                    }
                } else if (stepY > 0) {
                    if ((int)y >= (int)y2) {
                        y -= 1;
                        translation -= 3;
                        upY -= 1;
                        downY += 1;
                    } else {
                        y += 1;
                        translation += 3;
                        upY += 1;
                        downY -= 1;
                    }
                } else {
                    overshoot -= 1;
                }
            } else {
                if (stepX != 0) {
                    if ((int)x >= (int)x2) {
                        leftX -= 1;
                        x -= 1;
                        rightX += 1;
                    } else {
                        leftX += 1;
                        x += 1;
                        rightX -= 1;
                    }
                }
                if (stepY != 0) {
                    if ((int)y >= (int)y2) {
                        y -= 1;
                        translation -= 3;
                        upY -= 1;
                        downY += 1;
                    } else {
                        y += 1;
                        translation += 3;
                        upY += 1;
                        downY -= 1;
                    }
                }
                if (x == x2 && y == y2) {
                    overshoot -= 1;
                }
            }
            if (budget >= 16) {
                budget -= 16;
            }
            if (x == x2 && y == y2 && overshoot == 0) {
                break;
            }
        }

        // a stair aborts with wallType still M_MAPPER_STAIR, so it always charges stone
        if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
                DAT_BuildingsState::ptr)(playerID, 0, wallCount, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
                DAT_BuildingsState::ptr)(playerID, wallCount, 0, 0);
        }
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        DAT_TileMapState::instance.field_0x554a30 = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
