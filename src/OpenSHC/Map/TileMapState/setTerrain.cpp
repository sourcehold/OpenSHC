#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

// mask for the handwritten neighbour-flag macro; MASM has no "|", so this must be a literal
#define NEIGHBOUR_FLAGS_MASK_L2_BEACH 0x20 // L2_BEACH

#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L2_MOAT_UNDUG;
    using OpenSHC::Map::LogicHelpers::L2_NONE;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_SCRUB;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_NONE;
    using OpenSHC::Map::LogicHelpers::L_OIL;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_UNNAMED_0x40;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00512940
    void TileMapState::setTerrain(int playerID, int tile, uint yParam, uint brushType, Logic1 flags1, Logic2 flags2)
    {
        // Holds one expansion of the handwritten neighbour-flag macro (see NeighbourFlagsGlobalAsm.hpp),
        // so the original was built without optimisation and the pragma above is needed to reproduce
        // its frame-pointer, reload-per-access shape. The locals are declared together because at
        // /Od the stack slots are observable and MSVC assigns them per function, not per scope.
        // MSVC lays them out by a hash of their NAME (16 buckets, walked in order; inside one bucket
        // the later declaration gets the higher slot), so these names and this order put them where
        // the original has them (baseY at ebp-4 down to baseTile at ebp-0x1c).
        //
        // L_UNNAMED_0x40 is the one Logic1 bit the generated enum has no name for; the original both
        // tests flags1 against it and sets it on the tile.
        uint x;
        int numTiles;
        uint baseY;
        int index;
        int moatEnemyDistance;
        int moatOpponentRange;
        int baseTile;

        numTiles = DAT_TerrainDefinedData::instance.BrushSizeArray[brushType];
        baseTile = tile;
        baseY = yParam;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            moatEnemyDistance = 15;
            moatOpponentRange = 7;
        } else {
            moatEnemyDistance = 30;
            moatOpponentRange = 30;
        }

        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR && flags1 != L_MOAT
            && (flags2 == L2_EARTH_AND_STONES || flags2 == L2_OASIS_GRASS || flags2 == L2_BEACH
                || flags2 == L2_STONES_OR_DRIVEN_SANDUnk || flags2 == L2_SCRUB || flags2 == L2_THICK_SCRUB)) {
            // this functions processes all oasis tiles
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setLand, this)(tile, yParam, brushType);
        }
        if (flags1 == L_MOAT) {
            numTiles = 9;
        }

        for (index = 0; index < numTiles; index++) {
            if (flags1 == L_MOAT) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    0, index, &tile, (int*)&yParam, baseTile, baseY);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&yParam, baseTile, baseY);
            }
            if ((this->LogicLayer[tile] & L_BORDER) != 0) {
                continue;
            }

            if (flags1 == L_SEA) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_PEBBLES;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
                this->HeightLayer[tile] = 0;
                this->DefaultHeightLayer[tile] = 0;
                this->forceUpdateLogicalAndMiscDisplayLayers = 1;
            } else if (flags1 == L_RIVER || flags1 == L_FORD) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if (flags2 != L2_NONE && (this->LogicLayer[tile] & L_RIVER) == 0) {
                    continue;
                }
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                if (flags1 == L_RIVER) {
                    this->LogicLayer[tile] &= ~L_FORD;
                } else {
                    this->LogicLayer[tile] &= ~L_RIVER;
                }
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_PEBBLES;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                if (flags2 != L2_BEACH) {
                    this->WallGFXLayer[tile] = this->RandomLayer[tile] & 7;
                }
                if (flags2 == L2_OASIS_GRASS) {
                    this->Logic2Layer[tile] = L2_OASIS_GRASS;
                }
                if (flags2 == L2_BEACH) {
                    this->Logic2Layer[tile] = L2_BEACH;
                    this->WallGFXLayer[tile] = (DAT_GameCore::instance.mapTimeInTicks & 8)
                        + this->WallGFXLayer[tile] * 32 + (this->RandomLayer[tile] & 7) * 1024;
                }
                this->LogicLayer[tile] |= flags1;
                if (this->HeightLayer[tile] >= 8) {
                    this->HeightLayer[tile] = this->DefaultHeightLayer[tile] - 8;
                    this->forceUpdateLogicalAndMiscDisplayLayers = 1;
                }
            } else if (flags1 == L_ROCKY) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_SEA) != 0) {
                    this->HeightLayer[tile] = 0;
                    this->DefaultHeightLayer[tile] = 0;
                } else if (this->HeightLayer[tile] < 8) {
                    this->HeightLayer[tile] = 8;
                    this->DefaultHeightLayer[tile] = 8;
                }
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_PEBBLES;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
            } else if (flags1 == L_IRON) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_SEA) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_PEBBLES;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
            } else if (flags1 == L_PEBBLES) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_SEA) != 0) {
                    this->HeightLayer[tile] = 0;
                    this->DefaultHeightLayer[tile] = 0;
                } else if (this->HeightLayer[tile] < 8) {
                    this->HeightLayer[tile] = 8;
                    this->DefaultHeightLayer[tile] = 8;
                }
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
            } else if (flags1 == L_MARSH) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                this->HeightLayer[tile] = 8;
                this->DefaultHeightLayer[tile] = 8;
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
            } else if (flags1 == L_OIL) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_MARSH) == 0) {
                    continue;
                }
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
            } else if (flags1 == L_MOAT) {
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_SEA) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_FORD) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_ROCKY) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_BOULDERS) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_IRON) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_MARSH) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_PLAIN1_AND_FARM) != 0) {
                    continue;
                }
                x = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                    &DAT_ViewportRenderState::instance)(tile, yParam);
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                           &DAT_PathFindingState::instance)(playerID, x, yParam, moatEnemyDistance)
                        != FALSE) {
                    continue;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                            &DAT_PathFindingState::instance)(playerID, x, yParam, moatOpponentRange, -1, -1,
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)()
                                + 5)
                        != 0) {
                        continue;
                    }
                }
                if ((this->LogicLayer[tile] & L_MOAT) != 0 && flags2 != L2_MOAT_UNDUG) {
                    continue;
                }
                if (this->HeightLayer[tile] > 12) {
                    continue;
                }
                if (flags2 == L2_NONE) {
                    if ((this->LogicLayer[tile] & L_MOAT_DUG_OR_PLANNED) == 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                               playerID, x, yParam, 0)
                            != 0) {
                        this->LogicLayer[tile] |= L_MOAT_DUG_OR_PLANNED;
                    }
                } else if (flags2 == L2_SCRUB) {
                    if ((this->LogicLayer[tile] & L_MOAT_DUG_OR_PLANNED) != 0) {
                        this->LogicLayer[tile] &= ~L_MOAT_DUG_OR_PLANNED;
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(x, yParam);
                    }
                } else {
                    this->HeightLayer[tile] = 8;
                    this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                    this->Logic2Layer[tile] = 0;
                    if (flags2 == L2_EARTH_AND_STONES) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(
                                playerID, x, yParam, 1)
                            != 0) {
                            this->LogicLayer[tile] &= ~L_MOAT_DUG_OR_PLANNED;
                            this->LogicLayer[tile] |= L_MOAT;
                            this->HeightLayer[tile] = 0;
                        }
                    } else if (flags2 == L2_MOAT_UNDUG) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(x, yParam);
                        this->HeightLayer[tile] = 8;
                        this->LogicLayer[tile] &= ~L_MOAT_DUG_OR_PLANNED;
                        this->LogicLayer[tile] &= ~L_MOAT;
                    }
                }
            } else if (flags2 == L2_EARTH_AND_STONES || flags2 == L2_OASIS_GRASS || flags2 == L2_BEACH
                || flags2 == L2_STONES_OR_DRIVEN_SANDUnk || flags2 == L2_SCRUB || flags2 == L2_THICK_SCRUB) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & (L_SEA | L_RIVER | L_FORD | L_MARSH | L_MOAT)) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if (flags2 == L2_EARTH_AND_STONES) {
                    if ((this->LogicLayer[tile] & L_IRON) != 0) {
                        continue;
                    }
                    if ((this->LogicLayer[tile] & L_BOULDERS) != 0) {
                        continue;
                    }
                    if ((this->Logic2Layer[tile] & L2_BEACH) != 0) {
                        continue;
                    }
                    MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(1, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                    if (this->bitFlag != 0) {
                        continue;
                    }
                }

                this->MiscDisplayLayer[tile] = (short)this->MiscDisplayLayer[tile] & ~0x20;
                // the original tests each kept terrain on its own and leaves the height alone for it
                if (flags2 == L2_STONES_OR_DRIVEN_SANDUnk) {
                } else if (flags2 == L2_SCRUB) {
                } else if (flags2 == L2_THICK_SCRUB) {
                } else if (flags2 == L2_EARTH_AND_STONES) {
                } else if (flags2 == L2_OASIS_GRASS) {
                } else if (flags2 == L2_BEACH) {
                    this->HeightLayer[tile] = 0;
                    this->DefaultHeightLayer[tile] = 0;
                } else {
                    this->HeightLayer[tile] = 8;
                    this->DefaultHeightLayer[tile] = 8;
                }
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_BOULDERS;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                if (flags2 != L2_EARTH_AND_STONES) {
                    this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                }
                this->Logic2Layer[tile] = (byte)flags2;
            } else if (flags1 == L_BOULDERS) {
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_SEA) != 0) {
                    this->HeightLayer[tile] = 0;
                    this->DefaultHeightLayer[tile] = 0;
                } else if (this->HeightLayer[tile] < 8) {
                    this->HeightLayer[tile] = 8;
                    this->DefaultHeightLayer[tile] = 8;
                }
                this->LogicLayer[tile] &= ~L_SEA;
                this->LogicLayer[tile] &= ~L_UNNAMED_0x40;
                this->LogicLayer[tile] &= ~L_RIVER;
                this->LogicLayer[tile] &= ~L_FORD;
                this->LogicLayer[tile] &= ~L_ROCKY;
                this->LogicLayer[tile] &= ~L_PEBBLES;
                this->LogicLayer[tile] &= ~L_IRON;
                this->LogicLayer[tile] &= ~L_MARSH;
                this->LogicLayer[tile] &= ~L_OIL;
                this->LogicLayer[tile] &= ~L_MOAT;
                this->LogicLayer[tile] &= ~L_PLAIN2_AND_PITCH;
                this->Logic2Layer[tile] = 0;
                this->LogicLayer[tile] |= flags1;
            } else if (flags1 == L_UNNAMED_0x40) {
                if ((this->LogicLayer[tile] & L_SEA) == 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    continue;
                }
                if (this->BuildingLayer[tile] != 0) {
                    continue;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    continue;
                }
                if (this->OrganismLayer[tile] != 0) {
                    continue;
                }
                this->LogicLayer[tile] |= flags1;
            }

            if (flags1 != L_NONE) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    &DAT_PathFindingState::instance)(yParam, tile);
            }
        }
    }

}
}

#pragma optimize("", on)
