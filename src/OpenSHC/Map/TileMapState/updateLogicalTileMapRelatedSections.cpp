#include "OpenSHC/Map/TileMapState.func.hpp"

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

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F70F0
    void TileMapState::updateLogicalTileMapRelatedSections()
    {
        if (this->forceUpdateLogicalAndMiscDisplayLayers == 0) {
            return;
        }
        this->forceUpdateLogicalAndMiscDisplayLayers = 0;
        int tile = DAT_ViewportRenderState::instance
                       .translationMatrix[DAT_PathFindingState::instance.mappingYRelated]
                       .firstTileOfRow;
        DAT_BuildingsState::instance.field34_0x18e074 = 1;
        for (int row = DAT_PathFindingState::instance.mappingYRelated;
             row < 400 && row <= DAT_PathFindingState::instance.yLimit; row++) {
            for (int column = 0; column < this->yArray1[row]; column++, tile++) {
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0
                    || this->ChangedLayer[tile] == 0) {
                    continue;
                }

                uint height = this->HeightLayer[tile];
                int screenY = this->heightBasedScreenYOffset[height];
                this->ShowHiLayer[tile] = '\0';
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xffef;
                /* whether the tile draws its own texture or the default earth */
                if (height == 0) {
                    if (((this->LogicLayer[tile] & L_RIVER) == 0
                            && (this->Logic2Layer[tile] & L2_BEACH) != 0)
                        || (this->LogicLayer[tile] & L_MOAT) != 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_DEFAULT_EARTH_OR_TEXTURE;
                    } else {
                        this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_DEFAULT_EARTH_OR_TEXTURE;
                    }
                } else if (height < 9) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_DEFAULT_EARTH_OR_TEXTURE;
                } else if ((this->Logic2Layer[tile] & L2_PLATEAU_MEDIUM) != 0
                    || (this->Logic2Layer[tile] & L2_PLATEAU_HIGH) != 0
                    || (this->Logic2Layer[tile] & L2_EARTH_AND_STONES) != 0
                    || (this->Logic2Layer[tile] & L2_OASIS_GRASS) != 0
                    || (this->Logic2Layer[tile] & L2_SCRUB) != 0
                    || (char)this->Logic2Layer[tile] < '\0'
                    || (this->Logic2Layer[tile] & L2_STONES_OR_DRIVEN_SANDUnk) != 0) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_DEFAULT_EARTH_OR_TEXTURE;
                } else {
                    this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_DEFAULT_EARTH_OR_TEXTURE;
                }

                /* a tile level with all eight neighbours keeps its texture */
                for (int i = 0; i < 8; i++) {
                    int neighbour = this->directionTranslationMatrix[row][i] + tile;
                    if ((height > 8 || this->HeightLayer[neighbour] == 0)
                        && height != this->HeightLayer[neighbour]) {
                        if ((this->LogicLayer[neighbour] & (L_RIVER | L_MOAT)) == 0) {
                            this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_DEFAULT_EARTH_OR_TEXTURE;
                        }
                        break;
                    }
                }
                if (this->BuildingLayer[tile] != 0
                    && DAT_BuildingsState::instance.buildings[this->BuildingLayer[tile]].buildingType
                        == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                    this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0x10;
                }

                if (this->field93_0x5548c8 == 0) {
                    /* look up the light's diagonal for anything standing high enough to shadow us */
                    int walkTile = tile;
                    int* direction = this->directionTranslationMatrix[row] + this->field84_0x5548a4;
                    bool shadowed = false;
                    for (int depth = 0; depth < 0x80; depth = depth + 0x10) {
                        walkTile = walkTile + *direction;
                        if ((this->LogicLayer[walkTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                            break;
                        }
                        if (screenY <= (this->heightBasedScreenYOffset[this->HeightLayer[walkTile]] - depth) + -0x10) {
                            this->ShowHiLayer[tile] = 0xff;
                            shadowed = true;
                            break;
                        }
                        direction = direction + this->field88_0x5548b4 * 8;
                    }
                    if (height == 0 || shadowed) {
                        continue;
                    }
                } else {
                    this->ShowHiLayer[tile] = '\b';
                }

                bool occluded = true;
                if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                    && (this->LogicLayer[tile] & L_TREE_VARIATION) == 0
                    && (this->LogicLayer[tile] & L_FARM_FIELD_WHEAT) == 0
                    && (this->LogicLayer[tile] & L_FARM_FIELD_HOP) == 0
                    && (this->LogicLayer[tile] & L_CRENEL) == 0
                    && (this->LogicLayer[tile] & L_STAIRS) == 0) {
                    this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0x10;
                    occluded = false;
                }
                for (int i = 0; i < 8; i++) {
                    int neighbour = this->directionTranslationMatrix[row][i] + tile;
                    if ((height > 8 && height != this->HeightLayer[neighbour])
                        || (this->LogicLayer[neighbour] & L_TREE_VARIATION) != 0) {
                        this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xffef;
                        break;
                    }
                    if ((this->LogicLayer[neighbour] & L_FARM_FIELD_WHEAT) != 0) {
                        occluded = true;
                    }
                    if ((this->LogicLayer[neighbour] & L_FARM_FIELD_HOP) != 0) {
                        occluded = true;
                    }
                }
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xfffc;

                bool stepLeft = false;
                bool stepRight = false;
                int shadowTile = this->directionTranslationMatrix[row][this->field84_0x5548a4] + tile;
                int lowest = 0xfa;
                if (this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]] < 0xfa) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]];
                }
                int nearly = screenY + 2;
                if (nearly < this->heightBasedScreenYOffset[this->HeightLayer[shadowTile]]) {
                    occluded = true;
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                                if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[shadowTile])
                                        != 0) {
                                    occluded = true;
                                }
                                if (((this->LogicLayer[this->directionTranslationMatrix[row][this->field86_0x5548ac] + tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[this->directionTranslationMatrix[row][this->field86_0x5548ac] + tile])
                                        != 0)
                                    || ((this->LogicLayer[this->directionTranslationMatrix[row][this->field86_0x5548ac] + tile] & L_WALL_OR_GATEHOUSE) != 0
                                        && (this->LogicLayer[this->directionTranslationMatrix[row][this->field86_0x5548ac] + tile] & L_STOCKPILEUnk) == 0)) {
                                    occluded = true;
                                }
                                if (((this->LogicLayer[this->directionTranslationMatrix[row][this->field85_0x5548a8] + tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[this->directionTranslationMatrix[row][this->field85_0x5548a8] + tile])
                                        != 0)
                                    || ((this->LogicLayer[this->directionTranslationMatrix[row][this->field85_0x5548a8] + tile] & L_WALL_OR_GATEHOUSE) != 0
                                        && (this->LogicLayer[this->directionTranslationMatrix[row][this->field85_0x5548a8] + tile] & L_STOCKPILEUnk) == 0)) {
                                    occluded = true;
                                }
                                if (((this->LogicLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field86_0x5548ac] + shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field86_0x5548ac] + shadowTile])
                                        != 0)
                                    || ((this->LogicLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field86_0x5548ac] + shadowTile] & L_WALL_OR_GATEHOUSE) != 0
                                        && (this->LogicLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field86_0x5548ac] + shadowTile] & L_STOCKPILEUnk) == 0)) {
                                    occluded = true;
                                }
                                if (((this->LogicLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field85_0x5548a8] + shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field85_0x5548a8] + shadowTile])
                                        != 0)
                                    || ((this->LogicLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field85_0x5548a8] + shadowTile] & L_WALL_OR_GATEHOUSE) != 0
                                        && (this->LogicLayer[this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field85_0x5548a8] + shadowTile] & L_STOCKPILEUnk) == 0)) {
                                    occluded = true;
                                }
                                shadowTile = shadowTile
                                    + this->directionTranslationMatrix[this->field88_0x5548b4 + row][this->field84_0x5548a4];
                                if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[shadowTile])
                                        != 0) {
                                    occluded = true;
                                }
                                if (((this->LogicLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field86_0x5548ac] + shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field86_0x5548ac] + shadowTile])
                                        != 0)
                                    || ((this->LogicLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field86_0x5548ac] + shadowTile] & L_WALL_OR_GATEHOUSE) != 0
                                        && (this->LogicLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field86_0x5548ac] + shadowTile] & L_STOCKPILEUnk) == 0)) {
                                    occluded = true;
                                }
                                if (((this->LogicLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field85_0x5548a8] + shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field85_0x5548a8] + shadowTile])
                                        != 0)
                                    || ((this->LogicLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field85_0x5548a8] + shadowTile] & L_WALL_OR_GATEHOUSE) != 0
                                        && (this->LogicLayer[this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field85_0x5548a8] + shadowTile] & L_STOCKPILEUnk) == 0)) {
                                    occluded = true;
                                }
                                shadowTile = shadowTile
                                    + this->directionTranslationMatrix[row + this->field88_0x5548b4 * 2][this->field84_0x5548a4];
                                if ((this->LogicLayer[shadowTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                                           this->BuildingLayer[shadowTile])
                                        != 0) {
                                    occluded = true;
                                }
                } else {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[shadowTile]].flag2 != 0) {
                        occluded = true;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[shadowTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = true;
                    }
                    if (DAT_BuildingsState::instance
                            .buildings[this->BuildingLayer[this->directionTranslationMatrix
                                                               [this->field88_0x5548b4 + row]
                                                               [this->field84_0x5548a4]
                                + shadowTile]]
                            .flag2
                        != 0) {
                        occluded = true;
                    }
                }

                int leftTile = this->directionTranslationMatrix[row][this->field86_0x5548ac] + tile;
                if (this->heightBasedScreenYOffset[this->HeightLayer[leftTile]] < lowest) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[leftTile]];
                }
                if (screenY <= this->heightBasedScreenYOffset[this->HeightLayer[leftTile]]) {
                    stepLeft = true;
                    if (nearly < this->heightBasedScreenYOffset[this->HeightLayer[leftTile]]) {
                        occluded = true;
                    }
                }
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                    if ((this->LogicLayer[leftTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                               this->BuildingLayer[leftTile])
                            != 0) {
                        occluded = true;
                    }
                } else {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[leftTile]].flag2 != 0) {
                        occluded = true;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[leftTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        occluded = true;
                    }
                }

                int rightTile = this->directionTranslationMatrix[row][this->field85_0x5548a8] + tile;
                if (this->heightBasedScreenYOffset[this->HeightLayer[rightTile]] < lowest) {
                    lowest = this->heightBasedScreenYOffset[this->HeightLayer[rightTile]];
                }
                if (screenY <= this->heightBasedScreenYOffset[this->HeightLayer[rightTile]]) {
                    stepRight = true;
                    if (nearly < this->heightBasedScreenYOffset[this->HeightLayer[rightTile]]) {
                        occluded = true;
                    }
                }
                bool clear;
                if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                    if ((this->LogicLayer[tile] & L_KEEP_NON_MANOR_HOUSE) != 0
                        || (this->LogicLayer[rightTile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                        || MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag1, DAT_BuildingsState::ptr)(
                               this->BuildingLayer[rightTile])
                            == 0) {
                        clear = occluded;
                    } else {
                        clear = true;
                    }
                } else {
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[rightTile]].flag2 != 0) {
                        occluded = true;
                    }
                    if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[rightTile]].buildingType
                        == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                        clear = true;
                    } else {
                        clear = occluded;
                    }
                }
                if (clear) {
                    this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xffef;
                } else {
                    this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0x10;
                }

                if (lowest < screenY) {
                    if (this->field93_0x5548c8 == 0) {
                        this->ShowHiLayer[tile] = (char)screenY - (char)lowest;
                    }
                    if ((this->LogicLayer[tile] & L_SEA) == 0) {
                        if (stepLeft) {
                            this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 1;
                        }
                        if (stepRight) {
                            this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 2;
                        }
                    }
                }
            }
        }
    }

}
}
