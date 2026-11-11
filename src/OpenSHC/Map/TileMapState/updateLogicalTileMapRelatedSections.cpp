#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
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

                int const height = this->HeightLayer[tile];
                int const screenY = this->heightBasedScreenYOffset[height];
                this->ShowHiLayer[tile] = 0;
                this->MiscDisplayLayer[tile] &= 0xffef;
                // whether the tile draws its own texture or the default earth
                if (height == 0
                    && ((this->LogicLayer[tile] & L_RIVER) != 0 || (this->Logic2Layer[tile] & L2_BEACH) == 0)
                    && (this->LogicLayer[tile] & L_MOAT) == 0) {
                    this->LogicLayer[tile] &= ~L_DEFAULT_EARTH_OR_TEXTURE;
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
                } else if ((this->Logic2Layer[tile] & L2_THICK_SCRUB) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_STONES_OR_DRIVEN_SANDUnk) != 0) {
                    this->LogicLayer[tile] |= L_DEFAULT_EARTH_OR_TEXTURE;
                } else {
                    this->LogicLayer[tile] &= ~L_DEFAULT_EARTH_OR_TEXTURE;
                }

                // a tile level with all eight neighbours keeps its texture
                for (int i = 0; i < 8; i++) {
                    int const neighbour = this->directionTranslationMatrix[row][i] + tile;
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
                    // look up the light's diagonal for anything standing high enough to shadow us
                    int walkTile = tile;
                    int* direction = this->directionTranslationMatrix[row] + this->screenSouthEastDirection;
                    for (int depth = 0; depth < 128; depth += 16) {
                        walkTile += *direction;
                        if ((this->LogicLayer[walkTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                            break;
                        }
                        if (screenY <= this->heightBasedScreenYOffset[this->HeightLayer[walkTile]] - depth - 16) {
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
                    this->ShowHiLayer[tile] = 8;
                }

                BOOLEnum occluded;
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                    occluded = TRUE;
                } else if ((this->LogicLayer[tile] & L_TREE_VARIATION) != 0) {
                    occluded = TRUE;
                } else if ((this->LogicLayer[tile] & L_FARM_FIELD_WHEAT) != 0) {
                    occluded = TRUE;
                } else if ((this->LogicLayer[tile] & L_FARM_FIELD_HOP) != 0) {
                    occluded = TRUE;
                } else if ((this->LogicLayer[tile] & L_CRENEL) != 0) {
                    occluded = TRUE;
                } else if ((this->LogicLayer[tile] & L_STAIRS) != 0) {
                    occluded = TRUE;
                } else {
                    this->MiscDisplayLayer[tile] |= 0x10;
                    occluded = FALSE;
                }
                for (int i = 0; i < 8; i++) {
                    int const neighbour = this->directionTranslationMatrix[row][i] + tile;
                    if ((height > 8 && height != this->HeightLayer[neighbour])
                        || (this->LogicLayer[neighbour] & L_TREE_VARIATION) != 0) {
                        this->MiscDisplayLayer[tile] &= 0xffef;
                        break;
                    }
                    if ((this->LogicLayer[neighbour] & L_FARM_FIELD_WHEAT) != 0) {
                        occluded = TRUE;
                    }
                    if ((this->LogicLayer[neighbour] & L_FARM_FIELD_HOP) != 0) {
                        occluded = TRUE;
                    }
                }
                this->MiscDisplayLayer[tile] &= 0xfffc;

                BOOLEnum stepLeft = FALSE;
                BOOLEnum stepRight = FALSE;
                int shadowTile = this->directionTranslationMatrix[row][this->screenSouthEastDirection] + tile;
                int lowest = 250;
                if (this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]] < 250) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]];
                }
                int const nearly = screenY + 2;
                if (this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]] > nearly) {
                    occluded = TRUE;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[shadowTile]].flag2 != 0) {
                        occluded = TRUE;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[shadowTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = TRUE;
                    }
                    if (DAT_BuildingsState::instance
                            .buildings[this->BuildingLayer[this->directionTranslationMatrix[this->orientedRowStep
                                                               + row][this->screenSouthEastDirection]
                                + shadowTile]]
                            .flag2
                        != 0) {
                        occluded = TRUE;
                    }
                } else {
                    if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[shadowTile])
                            != 0) {
                        occluded = TRUE;
                    }
                    int const southTile = this->directionTranslationMatrix[row][this->screenSouthDirection] + tile;
                    if (((this->LogicLayer[southTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[southTile])
                                != 0)
                        || ((this->LogicLayer[southTile] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[southTile] & L_STOCKPILEUnk) == 0)) {
                        occluded = TRUE;
                    }
                    int const eastTile = this->directionTranslationMatrix[row][this->screenEastDirection] + tile;
                    if (((this->LogicLayer[eastTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[eastTile])
                                != 0)
                        || ((this->LogicLayer[eastTile] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[eastTile] & L_STOCKPILEUnk) == 0)) {
                        occluded = TRUE;
                    }
                    int const southTile2
                        = this->directionTranslationMatrix[this->orientedRowStep + row][this->screenSouthDirection]
                        + shadowTile;
                    if (((this->LogicLayer[southTile2] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[southTile2])
                                != 0)
                        || ((this->LogicLayer[southTile2] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[southTile2] & L_STOCKPILEUnk) == 0)) {
                        occluded = TRUE;
                    }
                    int const eastTile2
                        = this->directionTranslationMatrix[this->orientedRowStep + row][this->screenEastDirection]
                        + shadowTile;
                    if (((this->LogicLayer[eastTile2] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[eastTile2])
                                != 0)
                        || ((this->LogicLayer[eastTile2] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[eastTile2] & L_STOCKPILEUnk) == 0)) {
                        occluded = TRUE;
                    }
                    shadowTile += this->directionTranslationMatrix[this->orientedRowStep + row]
                                                                  [this->screenSouthEastDirection];
                    if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[shadowTile])
                            != 0) {
                        occluded = TRUE;
                    }
                    int const southTile3
                        = this->directionTranslationMatrix[row + this->orientedRowStep * 2][this->screenSouthDirection]
                        + shadowTile;
                    if (((this->LogicLayer[southTile3] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[southTile3])
                                != 0)
                        || ((this->LogicLayer[southTile3] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[southTile3] & L_STOCKPILEUnk) == 0)) {
                        occluded = TRUE;
                    }
                    int const eastTile3
                        = this->directionTranslationMatrix[row + this->orientedRowStep * 2][this->screenEastDirection]
                        + shadowTile;
                    if (((this->LogicLayer[eastTile3] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                   DAT_BuildingsState::ptr)(this->BuildingLayer[eastTile3])
                                != 0)
                        || ((this->LogicLayer[eastTile3] & L_WALL_OR_GATEHOUSE) != 0
                            && (this->LogicLayer[eastTile3] & L_STOCKPILEUnk) == 0)) {
                        occluded = TRUE;
                    }
                    shadowTile += this->directionTranslationMatrix[row + this->orientedRowStep * 2]
                                                                  [this->screenSouthEastDirection];
                    if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[shadowTile])
                            != 0) {
                        occluded = TRUE;
                    }
                }

                int const southTile = this->directionTranslationMatrix[row][this->screenSouthDirection] + tile;
                if (this->heightBasedScreenYOffset[this->HeightLayer[southTile]] < lowest) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[southTile]];
                }
                if (this->heightBasedScreenYOffset[this->HeightLayer[southTile]] >= screenY) {
                    stepLeft = TRUE;
                    if (this->heightBasedScreenYOffset[this->HeightLayer[southTile]] > nearly) {
                        occluded = TRUE;
                    }
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[southTile]].flag2 != 0) {
                        occluded = TRUE;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[southTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = TRUE;
                    }
                } else {
                    if ((this->LogicLayer[southTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                               DAT_BuildingsState::ptr)(this->BuildingLayer[southTile])
                            != 0) {
                        occluded = TRUE;
                    }
                }

                int const eastTile = this->directionTranslationMatrix[row][this->screenEastDirection] + tile;
                if (this->heightBasedScreenYOffset[this->HeightLayer[eastTile]] < lowest) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[eastTile]];
                }
                if (this->heightBasedScreenYOffset[this->HeightLayer[eastTile]] >= screenY) {
                    stepRight = TRUE;
                    if (this->heightBasedScreenYOffset[this->HeightLayer[eastTile]] > nearly) {
                        occluded = TRUE;
                    }
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[eastTile]].flag2 != 0) {
                        occluded = TRUE;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[eastTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = TRUE;
                    }
                } else if ((this->LogicLayer[tile] & L_KEEP_NON_MANOR_HOUSE) == 0
                    && (this->LogicLayer[eastTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                           DAT_BuildingsState::ptr)(this->BuildingLayer[eastTile])
                        != 0) {
                    occluded = TRUE;
                }
                if (!occluded) {
                    this->MiscDisplayLayer[tile] |= 0x10;
                } else {
                    this->MiscDisplayLayer[tile] &= 0xffef;
                }

                if (screenY > lowest) {
                    if (this->disableElevationRendering == 0) {
                        this->ShowHiLayer[tile] = (char)screenY - (char)lowest;
                    }
                    if ((this->LogicLayer[tile] & L_SEA) == 0) {
                        if (stepLeft) {
                            this->MiscDisplayLayer[tile] |= 1;
                        }
                        if (stepRight) {
                            this->MiscDisplayLayer[tile] |= 2;
                        }
                    }
                }
            }
        }
    }

}
}
