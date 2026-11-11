#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_MEDIUM;
    using OpenSHC::Map::LogicHelpers::L2_SCRUB;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F70F0
    void TileMapState::updateLogicalTileMapRelatedSections()
    {
        if (this->forceUpdateLogicalAndMiscDisplayLayers == 0) {
            return;
        }
        this->forceUpdateLogicalAndMiscDisplayLayers = 0;
        int tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_PathFindingState::instance.mappingYRelated]
                       .firstTileOfRow;
        DAT_BuildingsState::instance.field_0x18e074 = 1;
        for (int row = DAT_PathFindingState::instance.mappingYRelated;
            row < 400 && row <= DAT_PathFindingState::instance.yLimit; row++) {
            int const columns = this->yArray1[row];
            for (int column = 0; column < columns; column++, tile++) {
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0 || this->ChangedLayer[tile] == 0) {
                    continue;
                }

                int height = this->HeightLayer[tile];
                int screenY = this->heightBasedScreenYOffset[height];
                this->ShowHiLayer[tile] = 0;
                this->MiscDisplayLayer[tile] &= 0xffef;
                /* whether the tile draws its own texture or the default earth */
                if (height == 0) {
                    if (((this->LogicLayer[tile] & L_RIVER) == 0 && (this->Logic2Layer[tile] & L2_BEACH) != 0)
                        || (this->LogicLayer[tile] & L_MOAT) != 0) {
                        this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                    } else {
                        this->LogicLayer[tile] &= ~L_DEFAULT_EARTH_OR_TEXTURE;
                    }
                } else if (height <= 8) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_PLATEAU_MEDIUM) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_PLATEAU_HIGH) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_EARTH_AND_STONES) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_OASIS_GRASS) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_SCRUB) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((char)this->Logic2Layer[tile] < 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_STONES_OR_DRIVEN_SANDUnk) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else {
                    this->LogicLayer[tile] &= ~L_DEFAULT_EARTH_OR_TEXTURE;
                }

                /* a tile level with all eight neighbours keeps its texture */
                for (int i = 0; i < 8; i++) {
                    int neighbour = this->directionTranslationMatrix[row][i] + tile;
                    int const neighbourHeight = this->HeightLayer[neighbour];
                    if ((height > 8 || neighbourHeight == 0) && height != neighbourHeight) {
                        if ((this->LogicLayer[neighbour] & (L_RIVER | L_MOAT)) == 0) {
                            this->LogicLayer[tile] &= ~L_DEFAULT_EARTH_OR_TEXTURE;
                        }
                        break;
                    }
                }
                int const building = (short)this->BuildingLayer[tile];
                if (building != 0
                    && DAT_BuildingsState::instance.buildings[building].buildingType
                        == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                    this->MiscDisplayLayer[tile] |= 0x10;
                }

                if (this->disableElevationRendering == 0) {
                    /* look up the light's diagonal for anything standing high enough to shadow us */
                    int walkTile = tile;
                    int* direction = this->directionTranslationMatrix[row] + this->screenSouthEastDirection;
                    for (int depth = 0; depth < 0x80; depth = depth + 0x10) {
                        walkTile += *direction;
                        if ((this->LogicLayer[walkTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                            break;
                        }
                        if (screenY <= (this->heightBasedScreenYOffset[this->HeightLayer[walkTile]] - depth) - 0x10) {
                            this->ShowHiLayer[tile] = 0xff;
                            break;
                        }
                        direction += this->orientedRowStep * 8;
                    }
                    if (height == 0) {
                        continue;
                    }
                    if (this->ShowHiLayer[tile] == 0xff) {
                        continue;
                    }
                } else {
                    this->ShowHiLayer[tile] = '\b';
                }

                int occluded;
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    occluded = 1;
                } else if ((this->LogicLayer[tile] & L_TREE_VARIATION) != 0) {
                    occluded = 1;
                } else if ((this->LogicLayer[tile] & L_FARM_FIELD_WHEAT) != 0) {
                    occluded = 1;
                } else if ((this->LogicLayer[tile] & L_FARM_FIELD_HOP) != 0) {
                    occluded = 1;
                } else if ((this->LogicLayer[tile] & L_CRENEL) != 0) {
                    occluded = 1;
                } else if ((this->LogicLayer[tile] & L_STAIRS) != 0) {
                    occluded = 1;
                } else {
                    this->MiscDisplayLayer[tile] |= 0x10;
                    occluded = 0;
                }
                for (int i = 0; i < 8; i++) {
                    int neighbour = this->directionTranslationMatrix[row][i] + tile;
                    if ((height > 8 && height != this->HeightLayer[neighbour])
                        || (this->LogicLayer[neighbour] & L_TREE_VARIATION) != 0) {
                        this->MiscDisplayLayer[tile] &= 0xffef;
                        break;
                    }
                    if ((this->LogicLayer[neighbour] & L_FARM_FIELD_WHEAT) != 0) {
                        occluded = 1;
                    }
                    if ((this->LogicLayer[neighbour] & L_FARM_FIELD_HOP) != 0) {
                        occluded = 1;
                    }
                }
                this->MiscDisplayLayer[tile] &= 0xfffc;

                int stepLeft = 0;
                int stepRight = 0;
                int shadowTile = this->directionTranslationMatrix[row][this->screenSouthEastDirection] + tile;
                int lowest = 0xfa;
                if (this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]] < 0xfa) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]];
                }
                int nearly = screenY + 2;
                if (this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]] > nearly) {
                    occluded = 1;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[shadowTile]].flag2 != 0) {
                        occluded = 1;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[shadowTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = 1;
                    }
                    if (DAT_BuildingsState::instance
                            .buildings[this->BuildingLayer[this->directionTranslationMatrix[this->orientedRowStep
                                                               + row][this->screenSouthEastDirection]
                                + shadowTile]]
                            .flag2
                        != 0) {
                        occluded = 1;
                    }
                } else {
                    if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[shadowTile])
                            != 0) {
                        occluded = 1;
                    }
                    int rightTile = this->directionTranslationMatrix[row][this->screenSouthDirection] + tile;
                    if (((this->LogicLayer[rightTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[rightTile])
                                != 0)
                        || ((this->LogicLayer[rightTile] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[rightTile] & L_STOCKPILEUnk) == 0)) {
                        occluded = 1;
                    }
                    int leftTile = this->directionTranslationMatrix[row][this->screenEastDirection] + tile;
                    if (((this->LogicLayer[leftTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[leftTile])
                                != 0)
                        || ((this->LogicLayer[leftTile] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[leftTile] & L_STOCKPILEUnk) == 0)) {
                        occluded = 1;
                    }
                    int rightTile2
                        = this->directionTranslationMatrix[this->orientedRowStep + row][this->screenSouthDirection]
                        + shadowTile;
                    if (((this->LogicLayer[rightTile2] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[rightTile2])
                                != 0)
                        || ((this->LogicLayer[rightTile2] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[rightTile2] & L_STOCKPILEUnk) == 0)) {
                        occluded = 1;
                    }
                    int leftTile2
                        = this->directionTranslationMatrix[this->orientedRowStep + row][this->screenEastDirection]
                        + shadowTile;
                    if (((this->LogicLayer[leftTile2] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[leftTile2])
                                != 0)
                        || ((this->LogicLayer[leftTile2] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[leftTile2] & L_STOCKPILEUnk) == 0)) {
                        occluded = 1;
                    }
                    shadowTile += this->directionTranslationMatrix[this->orientedRowStep + row]
                                                                  [this->screenSouthEastDirection];
                    if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[shadowTile])
                            != 0) {
                        occluded = 1;
                    }
                    int rightTile3
                        = this->directionTranslationMatrix[row + this->orientedRowStep * 2][this->screenSouthDirection]
                        + shadowTile;
                    if (((this->LogicLayer[rightTile3] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[rightTile3])
                                != 0)
                        || ((this->LogicLayer[rightTile3] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[rightTile3] & L_STOCKPILEUnk) == 0)) {
                        occluded = 1;
                    }
                    int leftTile3
                        = this->directionTranslationMatrix[row + this->orientedRowStep * 2][this->screenEastDirection]
                        + shadowTile;
                    if (((this->LogicLayer[leftTile3] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[leftTile3])
                                != 0)
                        || ((this->LogicLayer[leftTile3] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[leftTile3] & L_STOCKPILEUnk) == 0)) {
                        occluded = 1;
                    }
                    shadowTile += this->directionTranslationMatrix[row + this->orientedRowStep * 2]
                                                                  [this->screenSouthEastDirection];
                    if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[shadowTile])
                            != 0) {
                        occluded = 1;
                    }
                }

                int leftTile = this->directionTranslationMatrix[row][this->screenSouthDirection] + tile;
                if (this->heightBasedScreenYOffset[this->HeightLayer[leftTile]] < lowest) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[leftTile]];
                }
                if (this->heightBasedScreenYOffset[this->HeightLayer[leftTile]] >= screenY) {
                    stepLeft = 1;
                    if (this->heightBasedScreenYOffset[this->HeightLayer[leftTile]] > nearly) {
                        occluded = 1;
                    }
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[leftTile]].flag2 != 0) {
                        occluded = 1;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[leftTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = 1;
                    }
                } else {
                    if ((this->LogicLayer[leftTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[leftTile])
                            != 0) {
                        occluded = 1;
                    }
                }

                int rightTile = this->directionTranslationMatrix[row][this->screenEastDirection] + tile;
                if (this->heightBasedScreenYOffset[this->HeightLayer[rightTile]] < lowest) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[rightTile]];
                }
                if (this->heightBasedScreenYOffset[this->HeightLayer[rightTile]] >= screenY) {
                    stepRight = 1;
                    if (this->heightBasedScreenYOffset[this->HeightLayer[rightTile]] > nearly) {
                        occluded = 1;
                    }
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[rightTile]].flag2 != 0) {
                        occluded = 1;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[rightTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = 1;
                    }
                } else if ((this->LogicLayer[tile] & L_KEEP_NON_MANOR_HOUSE) == 0
                    && (this->LogicLayer[rightTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                           DAT_BuildingsState::ptr)(this->BuildingLayer[rightTile])
                        != 0) {
                    occluded = 1;
                }
                if (occluded != 0) {
                    this->MiscDisplayLayer[tile] &= 0xffef;
                } else {
                    this->MiscDisplayLayer[tile] |= 0x10;
                }

                if (screenY > lowest) {
                    if (this->disableElevationRendering == 0) {
                        this->ShowHiLayer[tile] = (char)screenY - (char)lowest;
                    }
                    if ((this->LogicLayer[tile] & L_SEA) == 0) {
                        if (stepLeft != 0) {
                            this->MiscDisplayLayer[tile] |= 1;
                        }
                        if (stepRight != 0) {
                            this->MiscDisplayLayer[tile] |= 2;
                        }
                    }
                }
            }
        }
    }

}
}
