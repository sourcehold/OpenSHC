#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F7A80
    void TileMapState::computeTileLuminescence(int tile, int y)
    {
        uint logic = this->LogicLayer[tile];
        int shade = 2;
        int alongShade = 2;
        int acrossShade = 2;
        int diagonal = 0;
        int opposite = 0;
        uint along = 0;
        uint across = 0;
        if ((logic & (L_BORDER | L_BORDER_EDGE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            return;
        }

        /* the light comes from one corner of the screen, so the rays turn with the map */
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

        uint ownHeight = this->HeightLayer[tile];
        if ((logic & L_TREE) != 0) {
            int stage = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage, DAT_LandscapeState::ptr)(
                this->OrganismLayer[tile]);
            if (stage > 2) {
                shade = stage;
            }
        } else if ((logic & L_TREE_VARIATION) != 0) {
            shade = 5;
        }

        /* first ray: along the light's diagonal, shading hardest close to the tile */
        uint height = 0;
        int rayTile = tile;
        int rayY = y;
        uint step = 6;
        do {
            rayTile = rayTile + this->directionTranslationMatrix[rayY][diagonal];
            rayY = rayY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
            if ((this->LogicLayer[rayTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[rayTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                height = this->HeightLayer[rayTile];
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                           this->BuildingLayer[rayTile])
                == 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                        this->BuildingLayer[rayTile])
                    < 0x10) {
                    height = this->HeightLayer[rayTile] + 0x10;
                } else {
                    height = (uint)this->HeightLayer[rayTile]
                        + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                              this->BuildingLayer[rayTile]);
                }
            }
            if ((this->LogicLayer[rayTile] & L_TREE) != 0) {
                height = height
                    + MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage, DAT_LandscapeState::ptr)(
                          this->OrganismLayer[rayTile])
                        * 7;
            } else if ((this->LogicLayer[rayTile] & L_TREE_VARIATION) != 0) {
                height = height + 0x28;
            }
            int rise = height - ownHeight;
            uint lit;
            if (rise < 1) {
                lit = 2;
            } else if (rise > 0x12) {
                lit = step + 1;
            } else if (rise < 3) {
                lit = 0;
            } else if (rise < 7) {
                lit = step + -3;
            } else if (rise < 0xb) {
                lit = step + -2;
            } else if (rise < 0xf) {
                lit = step + -1;
            } else {
                lit = step;
            }
            if (shade < (int)lit) {
                shade = lit;
            }
            step = step - 1;
        } while ((int)step > 1);

        /* second ray: one cardinal step off the diagonal */
        rayTile = this->directionTranslationMatrix[y][along] + tile;
        rayY = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[along].int_.yOffset + y;
        along = 4;
        uint sampled = height;
        do {
            if ((this->LogicLayer[rayTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[rayTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                sampled = this->HeightLayer[rayTile];
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                           this->BuildingLayer[rayTile])
                == 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                        this->BuildingLayer[rayTile])
                    < 0x10) {
                    sampled = this->HeightLayer[rayTile] + 0x10;
                } else {
                    sampled = (uint)this->HeightLayer[rayTile]
                        + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                              this->BuildingLayer[rayTile]);
                }
            }
            if ((this->LogicLayer[rayTile] & L_TREE) != 0) {
                sampled = sampled
                    + MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage, DAT_LandscapeState::ptr)(
                          this->OrganismLayer[rayTile])
                        * 7;
            } else if ((this->LogicLayer[rayTile] & L_TREE_VARIATION) != 0) {
                sampled = sampled + 0x28;
            }
            int rise = sampled - ownHeight;
            if (rise < 1) {
                height = 2;
            } else if (rise > 0x12) {
                height = along + 1;
            } else if (rise < 7) {
                height = 0;
            } else if (rise < 0xd) {
                height = along - 1;
            } else {
                height = along;
            }
            if (alongShade < (int)height) {
                alongShade = height;
            }
            rayTile = rayTile + this->directionTranslationMatrix[rayY][diagonal];
            along = along - 1;
            rayY = rayY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
        } while (along < 0x80000000);

        /* third ray: the same, one cardinal step the other way */
        rayTile = this->directionTranslationMatrix[y][across] + tile;
        rayY = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[across].int_.yOffset + y;
        across = 4;
        do {
            if ((this->LogicLayer[rayTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[rayTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                sampled = this->HeightLayer[rayTile];
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                           this->BuildingLayer[rayTile])
                == 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                        this->BuildingLayer[rayTile])
                    < 0x10) {
                    sampled = this->HeightLayer[rayTile] + 0x10;
                } else {
                    sampled = (uint)this->HeightLayer[rayTile]
                        + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                              this->BuildingLayer[rayTile]);
                }
            }
            if ((this->LogicLayer[rayTile] & L_TREE) != 0) {
                sampled = sampled
                    + MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage, DAT_LandscapeState::ptr)(
                          this->OrganismLayer[rayTile])
                        * 7;
            } else if ((this->LogicLayer[rayTile] & L_TREE_VARIATION) != 0) {
                sampled = sampled + 0x28;
            }
            int rise = sampled - ownHeight;
            if (rise < 1) {
                height = 2;
            } else if (rise > 0x12) {
                height = across + 1;
            } else if (rise < 7) {
                height = 0;
            } else if (rise < 0xd) {
                height = across - 1;
            } else {
                height = across;
            }
            if (acrossShade < (int)height) {
                acrossShade = height;
            }
            rayTile = rayTile + this->directionTranslationMatrix[rayY][diagonal];
            across = across - 1;
            rayY = rayY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
        } while (across < 0x80000000);

        if (shade + -2 < (int)((acrossShade - 4) + alongShade)) {
            shade = (acrossShade - 2) + alongShade;
            if (shade > 6) {
                shade = 7;
            }
        } else if (shade == 2) {
            /* nothing casts onto the tile, so shade it by the slope it sits on */
            int diagonalTile = this->directionTranslationMatrix[y][diagonal] + tile;
            uint lightSide = ownHeight;
            if ((this->LogicLayer[diagonalTile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                if ((this->LogicLayer[diagonalTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                    lightSide = this->HeightLayer[diagonalTile];
                } else {
                    lightSide = sampled;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                            this->BuildingLayer[diagonalTile])
                        == 0) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                                this->BuildingLayer[diagonalTile])
                            < 0x10) {
                            lightSide = this->HeightLayer[diagonalTile] + 0x10;
                        } else {
                            lightSide = (uint)this->HeightLayer[diagonalTile]
                                + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(this->BuildingLayer[diagonalTile]);
                        }
                    }
                }
            }
            int oppositeTile = this->directionTranslationMatrix[y][opposite] + tile;
            uint darkSide = ownHeight;
            if ((this->LogicLayer[oppositeTile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                darkSide = this->HeightLayer[oppositeTile];
            }
            char slope = (int)lightSide < (int)(ownHeight - 4);
            if (ownHeight + 4 < darkSide) {
                slope = slope + '\x01';
            }
            if ((this->LogicLayer[tile] & L_MOAT) == 0) {
                if (slope == '\x01') {
                    shade = 1;
                } else if (slope == '\x02') {
                    shade = 0;
                }
            }
        }
        this->LuminesenceLayer[tile] = (uchar)shade;
    }

}
}
