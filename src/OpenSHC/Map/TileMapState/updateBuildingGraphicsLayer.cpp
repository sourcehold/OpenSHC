
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00506370
    void TileMapState::updateBuildingGraphicsLayer(int buildingID)
    {
        ushort buildingXPos = DAT_BuildingsState::instance.buildings[buildingID].x;
        ushort buildingYPos = DAT_BuildingsState::instance.buildings[buildingID].y;
        DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 = 0;
        if (this->refreshRelatedOne == 0 && DAT_BuildingsState::instance.buildings[buildingID].gfxOffset != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 = 1;
        }
        int stored = DAT_BuildingsState::instance.buildings[buildingID].currentNumberOfResource
            - (int)DAT_BuildingsState::instance.buildings[buildingID].someResourceNumber;

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int tile
                = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + (short)buildingYPos].addXgetTile
                + (short)buildingXPos + this->buildingX;
            if (this->field93_0x5548c8 != 0) {
                /* the placement overlay replaces every building graphic with its outline */
                this->AlphaGFXLayer[tile] = 0;
                this->GfxLayer[tile]
                    = ((short)DAT_TerrainDefinedData::instance
                              .BrushSizeArray[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight + 7]
                          + (short)this->buildingRotationRelatedValue + (short)GMTotalPicturesProcessed::instance[0x9d])
                    - 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_STOCKPILE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE) {
                /* a stockpile's pile grows with what is stored on it */
                if (stored < 1) {
                    this->GfxLayer[tile] = (short)this->buildingRotationRelatedValue
                        + (short)GMTotalPicturesProcessed::instance[0xf] + 4;
                } else {
                    short resource = DAT_BuildingsState::instance.buildings[buildingID].currentStoredResourceType;
                    short pile;
                    if (DAT_TerrainDefinedData::instance.field1001_0x8b4[resource] == 2) {
                        int remaining
                            = DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource - stored;
                        pile = (short)this->buildingRotationRelatedValue
                            + ((short)(remaining / 4) + ((ushort)remaining & 3) * 0xc) * 4;
                    } else if (DAT_TerrainDefinedData::instance.field1001_0x8b4[resource] == 0) {
                        pile = (short)this->buildingRotationRelatedValue + -4 + (short)stored * 4;
                    } else {
                        pile = (short)this->buildingRotationRelatedValue
                            + ((short)DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource
                                  - (short)stored)
                                * 4;
                    }
                    this->GfxLayer[tile] = (short)GMTotalPicturesProcessed::instance[0xf]
                        + (short)DAT_TerrainDefinedData::instance.field996_0x84c[resource] + -1 + pile;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_MERCENARYPOST
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_BARRACKS
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN) {
                this->GfxLayer[tile] = ((short)GMTotalPicturesProcessed::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                           + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                           + (short)this->buildingRotationRelatedValue)
                    - 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT) {
                /* a side door faces along the keep's axis, so its graphic follows the map rotation */
                uint facing = this->mapOrientation;
                if (DAT_BuildingsState::instance.buildings[buildingID].orientation == 6
                    || DAT_BuildingsState::instance.buildings[buildingID].orientation == 2) {
                    facing = (this->mapOrientation + 2) % 8;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                    if (facing == 2 || facing == 6) {
                        this->GfxLayer[tile]
                            = (short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .unknownManorHouseOrStoneKeepRelated
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                    } else {
                        this->GfxLayer[tile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID)
                            - 1;
                    }
                } else if (facing == 2 || facing == 6) {
                    this->GfxLayer[tile] = (short)GMTotalPicturesProcessed::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset;
                } else {
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                        - 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_KEEPDOOR) {
                if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                    if (this->mapOrientation != 2 && this->mapOrientation != 6) {
                        this->GfxLayer[tile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = (short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .unknownManorHouseOrStoneKeepRelated
                            + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                    }
                } else {
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .unknownManorHouseOrStoneKeepRelated
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                        - 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                int variation;
                if (this->mapOrientation == 2 || this->mapOrientation == 6) {
                    variation = (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 0x50) + 0x50;
                } else {
                    variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                    if (variation == 0x50) {
                        this->GfxLayer[tile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = (((short)GMTotalPicturesProcessed::instance
                                       [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                   + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset2)
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    }
                } else if (variation != 0x50) {
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset3
                              + (short)this->buildingRotationRelatedValue)
                        - 1;
                } else {
                    this->GfxLayer[tile]
                        = (((short)GMTotalPicturesProcessed::instance
                                   [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                               + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                              + (short)this->buildingRotationRelatedValue)
                        - 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                int variation = 0x50;
                if (this->mapOrientation == 2 || this->mapOrientation == 6) {
                    variation = 0x51;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 != 0) {
                    if (variation == 0x50) {
                        this->GfxLayer[tile]
                            = (((short)GMTotalPicturesProcessed::instance
                                       [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                   + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset)
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = (short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                            + (short)this->buildingRotationRelatedValue + 0x298;
                    }
                } else if (variation == 0x50) {
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->buildingRotationRelatedValue)
                        - 1;
                } else {
                    this->GfxLayer[tile] = (short)GMTotalPicturesProcessed::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)this->buildingRotationRelatedValue + 0x236;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                int plank
                    = DAT_TerrainDefinedData::instance
                          .field2467_0x1fec[(int)DAT_BuildingsState::instance.buildings[buildingID].buildingVariation
                              / 2][index];
                if (plank != 0) {
                    this->GfxLayer[tile] = (short)GMTotalPicturesProcessed::instance
                                               [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                        + (short)plank + 0x61e;
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(tile) == 0) {
                    this->GfxLayer[tile] = ((byte)this->RandomLayer[tile] & 3)
                        + (ushort)this->LuminesenceLayer[tile] * 4 + (short)GMTotalPicturesProcessed::instance[2];
                } else {
                    this->GfxLayer[tile] = ((byte)this->RandomLayer[tile] & 3)
                        + (this->LuminesenceLayer[tile] + 0x33) * 4 + (short)GMTotalPicturesProcessed::instance[5];
                }
            } else if ((DAT_BuildingsState::instance.buildings[buildingID].buildingType
                               != OpenSHC::Map::Buildings::BT_KILLINGPIT
                           || DAT_BuildingsState::instance.buildings[buildingID].state > 0
                           || DAT_GameState::instance.mapAndTime
                                   .playerTeams[DAT_BuildingsState::instance.buildings[buildingID].owner]
                               == DAT_GameState::instance.mapAndTime
                                   .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
                /* a killing pit is invisible to anyone not on the owner's team */
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 0xf) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 != 0) {
                        this->GfxLayer[tile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 0) {
                        this->GfxLayer[tile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                      .unknownManorHouseOrStoneKeepRelated
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    } else {
                        this->GfxLayer[tile]
                            = ((short)GMTotalPicturesProcessed::instance
                                      [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                                  + (short)DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID
                                  + (short)this->buildingRotationRelatedValue)
                            - 1;
                    }
                    this->AlphaGFXLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID]
                                  .unknownManorHouseOrStoneKeepRelated
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->buildingRotationRelatedValue)
                        - 1;
                } else {
                    int relative
                        = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation - this->mapOrientation;
                    if (relative < 0) {
                        relative = relative + 8;
                    }
                    short rotation = (short)relative;
                    short span;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 8) {
                        rotation = (short)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                        span = rotation * 8;
                    } else {
                        span = (short)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                        span = span * span;
                    }
                    short sprite;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 0) {
                        sprite = (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                    } else {
                        sprite = (short)DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID;
                    }
                    this->GfxLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + sprite + (short)this->buildingRotationRelatedValue + span * rotation)
                        - 1;
                    this->AlphaGFXLayer[tile]
                        = ((short)GMTotalPicturesProcessed::instance
                                  [(short)DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                              + (short)DAT_BuildingsState::instance.buildings[buildingID].spriteID
                              + (short)this->buildingRotationRelatedValue + span * rotation)
                        - 1;
                }
            }
            index++;
        } while (index < this->constructionTileCount);
    }

}
}
