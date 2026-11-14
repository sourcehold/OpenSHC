#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

// the original takes the larger of the building height and 16 with a max macro, which calls the getter twice
#define MAX_OF(A, B) ((A) < (B) ? (B) : (A))

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F7A80
    void TileMapState::computeTileLuminescence(int tile, int y)
    {
        uint logic = this->LogicLayer[tile];
        int diagonal = 0;
        int opposite = 0;
        int slope = 0;
        int shade = 2;
        int alongShade = 2;
        int acrossShade = 2;
        int along = 0;
        int across = 0;
        int high = 0;
        if ((logic & (L_BORDER | L_BORDER_EDGE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            return;
        }

        // the light comes from one corner of the screen, so the rays turn with the map
        switch (this->mapOrientation) {
        case 0:
            diagonal = 5;
            opposite = 1;
            along = 4;
            across = 6;
            break;
        case 2:
            diagonal = 7;
            opposite = 3;
            along = 6;
            across = 0;
            break;
        case 4:
            diagonal = 1;
            opposite = 5;
            along = 0;
            across = 2;
            break;
        case 6:
            diagonal = 3;
            opposite = 7;
            along = 2;
            across = 4;
        }

        int ownHeight = this->HeightLayer[tile];
        int rayY = y;
        int stage = 0;
        if ((logic & L_TREE) != 0) {
            stage = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                &DAT_LandscapeState::instance)(this->OrganismLayer[tile]);
        } else if ((logic & L_TREE_VARIATION) != 0) {
            stage = 5;
        }
        if (stage > 2) {
            shade = stage;
        }

        // first ray: along the light's diagonal, shading hardest close to the tile
        int rayTile = tile;
        for (int i = 0; i < 5; i++) {
            rayTile += this->directionTranslationMatrix[rayY][diagonal];
            rayY += DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
            if ((this->LogicLayer[rayTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[rayTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                int building = this->BuildingLayer[rayTile];
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3,
                        &DAT_BuildingsState::instance)(building)
                    == 0) {
                    high = this->HeightLayer[rayTile]
                        + MAX_OF(MACRO_CALL_MEMBER(
                                     OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                     &DAT_BuildingsState::instance)(building),
                            16);
                }
            } else {
                high = this->HeightLayer[rayTile];
            }
            if ((this->LogicLayer[rayTile] & L_TREE) != 0) {
                high += MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                            &DAT_LandscapeState::instance)(this->OrganismLayer[rayTile])
                    * 7;
            } else if ((this->LogicLayer[rayTile] & L_TREE_VARIATION) != 0) {
                high += 40;
            }
            int rise = high - ownHeight;
            int lit;
            if (rise <= 0) {
                lit = 2;
            } else if (rise > 18) {
                lit = 7 - i;
            } else if (rise > 14) {
                lit = 6 - i;
            } else if (rise > 10) {
                lit = 5 - i;
            } else if (rise > 6) {
                lit = 4 - i;
            } else if (rise > 2) {
                lit = 3 - i;
            } else {
                lit = 0;
            }
            if (lit > shade) {
                shade = lit;
            }
        }

        // second ray: one cardinal step off the diagonal
        int alongTile = this->directionTranslationMatrix[y][along] + tile;
        int alongY = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[along].int_.yOffset + y;
        for (int reach = 4; reach > -1; reach--) {
            if ((this->LogicLayer[alongTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[alongTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                int building = this->BuildingLayer[alongTile];
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3,
                        &DAT_BuildingsState::instance)(building)
                    == 0) {
                    high = this->HeightLayer[alongTile]
                        + MAX_OF(MACRO_CALL_MEMBER(
                                     OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                     &DAT_BuildingsState::instance)(building),
                            16);
                }
            } else {
                high = this->HeightLayer[alongTile];
            }
            if ((this->LogicLayer[alongTile] & L_TREE) != 0) {
                high += MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                            &DAT_LandscapeState::instance)(this->OrganismLayer[alongTile])
                    * 7;
            } else if ((this->LogicLayer[alongTile] & L_TREE_VARIATION) != 0) {
                high += 40;
            }
            int rise = high - ownHeight;
            int lit;
            if (rise <= 0) {
                lit = 2;
            } else if (rise > 18) {
                lit = reach + 1;
            } else if (rise > 12) {
                lit = reach;
            } else if (rise > 6) {
                lit = reach - 1;
            } else {
                lit = 0;
            }
            if (lit > alongShade) {
                alongShade = lit;
            }
            alongTile += this->directionTranslationMatrix[alongY][diagonal];
            alongY += DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
        }

        // third ray: the same, one cardinal step the other way
        int acrossTile = this->directionTranslationMatrix[y][across] + tile;
        int acrossY = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[across].int_.yOffset + y;
        for (int reach = 4; reach > -1; reach--) {
            if ((this->LogicLayer[acrossTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[acrossTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                int building = this->BuildingLayer[acrossTile];
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3,
                        &DAT_BuildingsState::instance)(building)
                    == 0) {
                    high = this->HeightLayer[acrossTile]
                        + MAX_OF(MACRO_CALL_MEMBER(
                                     OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                     &DAT_BuildingsState::instance)(building),
                            16);
                }
            } else {
                high = this->HeightLayer[acrossTile];
            }
            if ((this->LogicLayer[acrossTile] & L_TREE) != 0) {
                high += MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                            &DAT_LandscapeState::instance)(this->OrganismLayer[acrossTile])
                    * 7;
            } else if ((this->LogicLayer[acrossTile] & L_TREE_VARIATION) != 0) {
                high += 40;
            }
            int rise = high - ownHeight;
            int lit;
            if (rise <= 0) {
                lit = 2;
            } else if (rise > 18) {
                lit = reach + 1;
            } else if (rise > 12) {
                lit = reach;
            } else if (rise > 6) {
                lit = reach - 1;
            } else {
                lit = 0;
            }
            if (lit > acrossShade) {
                acrossShade = lit;
            }
            acrossTile += this->directionTranslationMatrix[acrossY][diagonal];
            acrossY += DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
        }

        if (acrossShade + alongShade - 4 > shade - 2) {
            int sum = acrossShade + alongShade - 2;
            shade = sum < 7 ? sum : 7;
        }
        if (shade == 2) {
            // nothing casts onto the tile, so shade it by the slope it sits on
            int diagonalTile = this->directionTranslationMatrix[y][diagonal] + tile;
            if ((this->LogicLayer[diagonalTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                high = ownHeight;
            } else {
                if ((this->LogicLayer[diagonalTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    int building = this->BuildingLayer[diagonalTile];
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3,
                            &DAT_BuildingsState::instance)(building)
                        == 0) {
                        high = this->HeightLayer[diagonalTile]
                            + MAX_OF(MACRO_CALL_MEMBER(
                                         OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                         &DAT_BuildingsState::instance)(building),
                                16);
                    }
                } else {
                    high = this->HeightLayer[diagonalTile];
                }
            }
            int oppositeTile = this->directionTranslationMatrix[y][opposite] + tile;
            int darkSide;
            if ((this->LogicLayer[oppositeTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                darkSide = ownHeight;
            } else {
                darkSide = this->HeightLayer[oppositeTile];
            }
            if (high < ownHeight - 4) {
                slope = 1;
            }
            if (darkSide > ownHeight + 4) {
                slope += 1;
            }
            if ((this->LogicLayer[tile] & L_MOAT) == 0) {
                if (slope == 1) {
                    shade = 1;
                } else if (slope == 2) {
                    shade = 0;
                }
            }
        }
        this->LuminesenceLayer[tile] = shade;
    }

}
}
