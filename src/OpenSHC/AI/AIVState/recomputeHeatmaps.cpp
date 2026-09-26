#include "../AIVState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using namespace Map::LogicHelpers;

    // recomputes the 5x5 tile heat map cells the AI uses to place buildings
    // FUNCTION: STRONGHOLDCRUSADER 0x004F0E80
    void AIVState::recomputeHeatmaps(int initialize)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            return;
        }

        if (initialize) {
            // full reset
            MACRO_CALL_MEMBER(AIVState_Func::clearTheHeatmaps, this)();
            for (int y = 0; y < 80; ++y) {
                for (int x = 0; x < 80; ++x) {
                    this->heatMaps[x][y].oasisThickScrubCount = 250;
                    this->heatMaps[x][y].impassableCount = 1;
                }
            }
            this->mapExtraInfo.largestSeparateArea
                = MACRO_CALL_MEMBER(AIVState_Func::computeLargestSeparateArea, this)();
        } else {
            for (int y = 0; y < 80; ++y) {
                for (int x = 0; x < 80; ++x) {
                    this->heatMaps[x][y].treeCount = 0;
                    this->heatMaps[x][y].impassableCount = 0;
                    this->heatMaps[x][y].structureCount = 0;
                    this->heatMaps[x][y].tileOwnership = 0;
                    if ((char)this->heatMaps[x][y].woodRelatedCountdownTo0 > 0) {
                        --this->heatMaps[x][y].woodRelatedCountdownTo0;
                    }
                    if ((char)this->heatMaps[x][y].destructionBasedPlacementCooldown > 0) {
                        --this->heatMaps[x][y].destructionBasedPlacementCooldown;
                    }
                }
            }
        }

        this->mapExtraInfo.totalWoodAvailable = 0;
        if (this->mapExtraInfo.largestSeparateArea <= 0) {
            return;
        }

        if (initialize) {
            for (int tile = 0; tile < 80400; ++tile) {
                int const gridY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] / 5;
                int const gridX = (tile
                                      - DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_ViewportRenderState::instance
                                                  .tileTranslationMatrix_YComponent[tile]]
                                          .addXgetTile)
                    / 5;
                if (gridX >= 1 && gridX <= 78 && gridY >= 1 && gridY <= 78) {
                    this->heatMaps[gridX][gridY].isNotNearEdgeUnk = 0;
                }
                if ((short)DAT_TileMapState::instance.PathConnectionLayer[tile]
                    != this->mapExtraInfo.largestSeparateArea) {
                    ++this->heatMaps[gridX][gridY].tilesNotPartOfLargestAreaCount;
                }
                if (DAT_TileMapState::instance.LogicLayer[tile]
                    & (L_SEA | L_BORDER | L_BORDER_EDGE | L_RIVER | L_FORD)) {
                    continue;
                }

                int const height = DAT_TileMapState::instance.DefaultHeightLayer[tile];
                if (height < this->heatMaps[gridX][gridY].lowestTerrainHeight) {
                    this->heatMaps[gridX][gridY].lowestTerrainHeight = (byte)height;
                }
                if (height > this->heatMaps[gridX][gridY].highestTerrainHeight) {
                    this->heatMaps[gridX][gridY].highestTerrainHeight = (byte)height;
                }
                if (this->heatMaps[gridX][gridY].lowestTerrainHeight + 12
                    < (uint)this->heatMaps[gridX][gridY].highestTerrainHeight) {
                    this->heatMaps[gridX][gridY].terrainDiffHigherThan12 = 1;
                }

                int const logic = DAT_TileMapState::instance.LogicLayer[tile];
                if (logic & L_TREE) {
                    int const treeID = (short)DAT_TileMapState::instance.OrganismLayer[tile];
                    // tree types 1 to 4 give wood
                    if (treeID != 0
                        && (DAT_LandscapeState::instance.trees[treeID].treeType == 1
                            || DAT_LandscapeState::instance.trees[treeID].treeType == 2
                            || DAT_LandscapeState::instance.trees[treeID].treeType == 3
                            || DAT_LandscapeState::instance.trees[treeID].treeType == 4)
                        && DAT_LandscapeState::instance.trees[treeID].stage < 4
                        && DAT_LandscapeState::instance.trees[treeID].state == 2
                        && MACRO_CALL_MEMBER(Map::LandscapeState_Func::isTreeAdult, DAT_LandscapeState::ptr)(
                            treeID, DAT_LandscapeState::instance.trees[treeID].uid)) {
                        this->heatMaps[gridX][gridY].treeCount += 3;
                        this->mapExtraInfo.totalWoodAvailable += 3;
                    }
                    continue;
                }
                if (logic & L_BOULDERS) {
                    ++this->heatMaps[gridX][gridY].bouldersCount;
                } else if (logic & L_IRON) {
                    ++this->heatMaps[gridX][gridY].ironCount;
                } else if (logic & L_OIL) {
                    ++this->heatMaps[gridX][gridY].oilCount;
                } else if (logic & L_MARSH) {
                    ++this->heatMaps[gridX][gridY].marshCount;
                } else if (logic & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) {
                    ++this->heatMaps[gridX][gridY].structureCount;
                } else if (logic & L_WALL_OR_GATEHOUSE) {
                    ++this->heatMaps[gridX][gridY].structureCount;
                } else if (logic & L_ROCKY) {
                    ++this->heatMaps[gridX][gridY].impassableCount;
                }
                if (!(DAT_TileMapState::instance.LogicLayer[tile] & L_RIVER)) {
                    if (DAT_TileMapState::instance.Logic2Layer[tile] & (L2_SCRUB | L2_OASIS_GRASS | L2_THICK_SCRUB)) {
                        ++this->heatMaps[gridX][gridY].oasisScrubCount;
                    }
                    if (DAT_TileMapState::instance.Logic2Layer[tile] & (L2_OASIS_GRASS | L2_THICK_SCRUB)) {
                        ++this->heatMaps[gridX][gridY].oasisThickScrubCount;
                    }
                }
            }
            return;
        }

        // only update what can change during the game
        for (int tile = 0; tile < 80400; ++tile) {
            if (!(DAT_TileMapState::instance.LogicLayer[tile]
                    & (L_ROCKY | L_WALL_OR_GATEHOUSE | L_BUILDING | L_TREE | L_KEEP_NON_MANOR_HOUSE))) {
                continue;
            }
            if (DAT_TileMapState::instance.LogicLayer[tile] & L_ROCKY) {
                ++this->heatMaps[(tile
                                     - DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_ViewportRenderState::instance
                                                 .tileTranslationMatrix_YComponent[tile]]
                                         .addXgetTile)
                          / 5][DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] / 5]
                      .impassableCount;
            }
            if (DAT_TileMapState::instance.LogicLayer[tile] & L_TREE) {
                short const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int const gridX = (tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile) / 5;
                int const gridY = y / 5;
                int const treeID = (short)DAT_TileMapState::instance.OrganismLayer[tile];
                // tree types 1 to 4 give wood
                if (treeID != 0
                    && (DAT_LandscapeState::instance.trees[treeID].treeType == 1
                        || DAT_LandscapeState::instance.trees[treeID].treeType == 2
                        || DAT_LandscapeState::instance.trees[treeID].treeType == 3
                        || DAT_LandscapeState::instance.trees[treeID].treeType == 4)
                    && DAT_LandscapeState::instance.trees[treeID].stage < 4
                    && DAT_LandscapeState::instance.trees[treeID].state == 2
                    && MACRO_CALL_MEMBER(Map::LandscapeState_Func::isTreeAdult, DAT_LandscapeState::ptr)(
                        treeID, DAT_LandscapeState::instance.trees[treeID].uid)) {
                    this->heatMaps[gridX][gridY].treeCount += 3;
                    this->mapExtraInfo.totalWoodAvailable += 3;
                }
            } else if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                int const gridX = (tile
                                      - DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_ViewportRenderState::instance
                                                  .tileTranslationMatrix_YComponent[tile]]
                                          .addXgetTile)
                    / 5;
                int const gridY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] / 5;
                ++this->heatMaps[gridX][gridY].structureCount;
                this->heatMaps[gridX][gridY].tileOwnership
                    = (byte)DAT_BuildingsState::instance
                          .buildings[(short)DAT_TileMapState::instance.BuildingLayer[tile]]
                          .owner;
            } else if (DAT_TileMapState::instance.LogicLayer[tile] & L_WALL_OR_GATEHOUSE) {
                int const gridX = (tile
                                      - DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_ViewportRenderState::instance
                                                  .tileTranslationMatrix_YComponent[tile]]
                                          .addXgetTile)
                    / 5;
                int const gridY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] / 5;
                ++this->heatMaps[gridX][gridY].structureCount;
                this->heatMaps[gridX][gridY].tileOwnership = (DAT_TileMapState::instance.WallOwnerLayer[tile] & 7) + 1;
            }
        }
    }

}
}
