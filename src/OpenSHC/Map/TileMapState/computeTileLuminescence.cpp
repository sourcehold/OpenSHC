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
    void TileMapState::computeTileLuminescence(int tileUnk, int y)
    {
        uint logic = this->LogicLayer[tileUnk];
        int shade = 2;
        int alongShade = 2;
        int acrossShade = 2;
        int diagonal = 0;
        int opposite = 0;
        int along = 0;
        int across = 0;
        uint high = 0;
        int slope = 0;
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

        uint ownHeight = this->HeightLayer[tileUnk];
        if ((logic & L_TREE) != 0) {
            int stage = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage, DAT_LandscapeState::ptr)(
                this->OrganismLayer[tileUnk]);
            if (stage > 2) {
                shade = stage;
            }
        } else if ((logic & L_TREE_VARIATION) != 0) {
            shade = 5;
        }

        /* first ray: along the light's diagonal, shading hardest close to the tileUnk */
        int rayTile = tileUnk;
        int rayY = y;
        uint step = 6;
        do {
            rayTile = rayTile + this->directionTranslationMatrix[rayY][diagonal];
            rayY = rayY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
            if ((this->LogicLayer[rayTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[rayTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                high = this->HeightLayer[rayTile];
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                           this->BuildingLayer[rayTile])
                == 0) {
                if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                        this->BuildingLayer[rayTile])
                    < 0x10) {
                    high = this->HeightLayer[rayTile] + 0x10;
                } else {
                    high = (uint)this->HeightLayer[rayTile]
                        + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
                              this->BuildingLayer[rayTile]);
                }
            }
            if ((this->LogicLayer[rayTile] & L_TREE) != 0) {
                high = high
                    + MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage, DAT_LandscapeState::ptr)(
                          this->OrganismLayer[rayTile])
                        * 7;
            } else if ((this->LogicLayer[rayTile] & L_TREE_VARIATION) != 0) {
                high = high + 0x28;
            }
            int rise = high - ownHeight;
            uint lit;
            if (rise <= 0) {
                lit = 2;
            } else if (rise > 0x12) {
                lit = step + 1;
            } else if (rise > 0xe) {
                lit = step;
            } else if (rise > 0xa) {
                lit = step + -1;
            } else if (rise > 6) {
                lit = step + -2;
            } else if (rise > 2) {
                lit = step + -3;
            } else {
                lit = 0;
            }
            if (shade < (int)lit) {
                shade = lit;
            }
            step = step - 1;
        } while ((int)step > 1);

        /* second ray: one cardinal step off the diagonal */
        rayTile = this->directionTranslationMatrix[y][along] + tileUnk;
        rayY = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[along].int_.yOffset + y;
        along = 4;
        uint sampled = high;
        do {
            if ((this->LogicLayer[rayTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                break;
            }
            if ((this->LogicLayer[rayTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                sampled = this->HeightLayer[rayTile];
            } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                           this->BuildingLayer[rayTile])
                == 0) {
                if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
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
            if (rise <= 0) {
                high = 2;
            } else if (rise > 0x12) {
                high = along + 1;
            } else if (rise > 0xc) {
                high = along;
            } else if (rise > 6) {
                high = along - 1;
            } else {
                high = 0;
            }
            if (alongShade < (int)high) {
                alongShade = high;
            }
            rayTile = rayTile + this->directionTranslationMatrix[rayY][diagonal];
            along = along - 1;
            rayY = rayY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
        } while (along > -1);

        /* third ray: the same, one cardinal step the other way */
        rayTile = this->directionTranslationMatrix[y][across] + tileUnk;
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
                if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
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
            if (rise <= 0) {
                high = 2;
            } else if (rise > 0x12) {
                high = across + 1;
            } else if (rise > 0xc) {
                high = across;
            } else if (rise > 6) {
                high = across - 1;
            } else {
                high = 0;
            }
            if (acrossShade < (int)high) {
                acrossShade = high;
            }
            rayTile = rayTile + this->directionTranslationMatrix[rayY][diagonal];
            across = across - 1;
            rayY = rayY + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[diagonal].int_.yOffset;
        } while (across > -1);

        if (shade + -2 < (int)((acrossShade - 4) + alongShade)) {
            shade = (acrossShade - 2) + alongShade;
            if (shade > 6) {
                shade = 7;
            }
        } else if (shade == 2) {
            /* nothing casts onto the tileUnk, so shade it by the slope it sits on */
            int diagonalTile = this->directionTranslationMatrix[y][diagonal] + tileUnk;
            uint lightSide = ownHeight;
            if ((this->LogicLayer[diagonalTile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                if ((this->LogicLayer[diagonalTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0) {
                    lightSide = this->HeightLayer[diagonalTile];
                } else {
                    lightSide = sampled;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(
                            this->BuildingLayer[diagonalTile])
                        == 0) {
                        if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(
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
            int oppositeTile = this->directionTranslationMatrix[y][opposite] + tileUnk;
            uint darkSide = ownHeight;
            if ((this->LogicLayer[oppositeTile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                darkSide = this->HeightLayer[oppositeTile];
            }
            if ((int)lightSide < (int)(ownHeight - 4)) {
                slope = 1;
            }
            if (ownHeight + 4 < darkSide) {
                slope = slope + 1;
            }
            if ((this->LogicLayer[tileUnk] & L_MOAT) == 0) {
                if (slope == 1) {
                    shade = 1;
                } else if (slope == 2) {
                    shade = 0;
                }
            }
        }
        this->LuminesenceLayer[tileUnk] = (uchar)shade;
    }

}
}
