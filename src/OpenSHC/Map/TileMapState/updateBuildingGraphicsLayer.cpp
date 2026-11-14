#include "../TileMapState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00506370
    void TileMapState::updateBuildingGraphicsLayer(int buildingID)
    {
        int const buildingXPos = DAT_BuildingsState::instance.buildings[buildingID].x;
        int const buildingYPos = DAT_BuildingsState::instance.buildings[buildingID].y;
        int index = 0;
        DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics = 0;
        if (this->refreshRelatedOne == 0 && DAT_BuildingsState::instance.buildings[buildingID].gfxOffset != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics = 1;
        }
        int const stored = DAT_BuildingsState::instance.buildings[buildingID].currentNumberOfResource
            - DAT_BuildingsState::instance.buildings[buildingID].someResourceNumber;

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int const tile
                = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + buildingYPos].addXgetTile
                + buildingXPos + this->buildingX;
            if (this->disableElevationRendering != 0) {
                // the placement overlay replaces every building graphic with its outline
                this->GfxLayer[tile]
                    = DAT_TerrainDefinedData::instance
                          .BrushSizeArray[DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight + 7]
                    + this->buildingRotationRelatedValue + GMFirstPictureIndex::instance[157] - 1;
                this->AlphaGFXLayer[tile] = 0;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_STOCKPILE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE) {
                // a stockpile's pile grows with what is stored on it
                if (stored > 0) {
                    int const pileGfx = DAT_TerrainDefinedData::instance
                                            .field_0x84c[DAT_BuildingsState::instance.buildings[buildingID]
                                                    .currentStoredResourceType];
                    int pile;
                    if (DAT_TerrainDefinedData::instance
                            .field_0x8b4[DAT_BuildingsState::instance.buildings[buildingID].currentStoredResourceType]
                        == 2) {
                        int const remaining
                            = DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource - stored;
                        pile = this->buildingRotationRelatedValue + (remaining / 4 + (remaining & 3) * 12) * 4;
                    } else if (DAT_TerrainDefinedData::instance.field_0x8b4
                                   [DAT_BuildingsState::instance.buildings[buildingID].currentStoredResourceType]
                        != 0) {
                        pile = this->buildingRotationRelatedValue
                            + (DAT_BuildingsState::instance.buildings[buildingID].currentLimitOfResource - stored) * 4;
                    } else {
                        pile = this->buildingRotationRelatedValue - 4 + stored * 4;
                    }
                    this->GfxLayer[tile] = GMFirstPictureIndex::instance[15] + pileGfx + pile - 1;
                } else {
                    this->GfxLayer[tile] = this->buildingRotationRelatedValue + GMFirstPictureIndex::instance[15] + 4;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_MERCENARYPOST
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_BARRACKS
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN) {
                this->GfxLayer[tile]
                    = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID]
                    + DAT_BuildingsState::instance.buildings[buildingID].spriteID + this->buildingRotationRelatedValue
                    - 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT) {
                // a side door faces along the keep's axis, so its graphic follows the map rotation
                int facing = this->mapOrientation;
                if (DAT_BuildingsState::instance.buildings[buildingID].orientation == 6
                    || DAT_BuildingsState::instance.buildings[buildingID].orientation == 2) {
                    facing = (facing + 2) % 8;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics != 0) {
                    if (facing != 2 && facing != 6) {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset - 1;
                    } else {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset;
                    }
                } else if (facing != 2 && facing != 6) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID - 1;
                } else {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_KEEPDOOR) {
                if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics != 0) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                        + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset - 1;
                } else if (this->mapOrientation != 2 && this->mapOrientation != 6) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID - 1;
                } else {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                int variation;
                if (this->mapOrientation != 2 && this->mapOrientation != 6) {
                    variation = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation;
                } else {
                    variation = (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 80) + 80;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics != 0) {
                    if (variation == 80) {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                            + this->buildingRotationRelatedValue - 1;
                    } else {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset3
                            + this->buildingRotationRelatedValue - 1;
                    }
                } else if (variation == 80) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID
                        + this->buildingRotationRelatedValue - 1;
                } else {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset2
                        + this->buildingRotationRelatedValue - 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                int variation;
                if (this->mapOrientation != 2 && this->mapOrientation != 6) {
                    variation = 80;
                } else {
                    variation = 81;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics != 0) {
                    if (variation == 80) {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                            + this->buildingRotationRelatedValue - 1;
                    } else {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + this->buildingRotationRelatedValue + 664;
                    }
                } else if (variation == 80) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID
                        + this->buildingRotationRelatedValue - 1;
                } else {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + this->buildingRotationRelatedValue + 566;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                int const plank = DAT_TerrainDefinedData::instance
                                      .field_0x1fec[DAT_BuildingsState::instance.buildings[buildingID].buildingVariation
                                          / 2][index];
                if (plank != 0) {
                    this->GfxLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + plank + 1566;
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(tile) != 0) {
                    this->GfxLayer[tile] = (this->RandomLayer[tile] & 3) + (this->LuminesenceLayer[tile] + 51) * 4
                        + GMFirstPictureIndex::instance[5];
                } else {
                    this->GfxLayer[tile] = (this->RandomLayer[tile] & 3) + this->LuminesenceLayer[tile] * 4
                        + GMFirstPictureIndex::instance[2];
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
                // a killing pit is invisible to anyone not on the owner's team
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation != 15) {
                    int rotation
                        = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation - this->mapOrientation;
                    if (rotation < 0) {
                        rotation += 8;
                    }
                    int span;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 8) {
                        rotation = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                        span = DAT_BuildingsState::instance.buildings[buildingID].buildingVariation * rotation;
                    } else {
                        span = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                    }
                    int const offset = span * rotation;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID
                            + this->buildingRotationRelatedValue + offset - 1;
                    } else {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].spriteID
                            + this->buildingRotationRelatedValue + offset - 1;
                    }
                    this->AlphaGFXLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID
                        + this->buildingRotationRelatedValue + offset - 1;
                } else {
                    if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics != 0) {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                            + this->buildingRotationRelatedValue - 1;
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 0) {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID
                            + this->buildingRotationRelatedValue - 1;
                    } else {
                        this->GfxLayer[tile]
                            = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                      .spriteSheetID]
                            + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                            + DAT_BuildingsState::instance.buildings[buildingID].spriteID
                            + this->buildingRotationRelatedValue - 1;
                    }
                    this->AlphaGFXLayer[tile]
                        = GMFirstPictureIndex::instance[DAT_BuildingsState::instance.buildings[buildingID]
                                  .spriteSheetID]
                        + DAT_BuildingsState::instance.buildings[buildingID].unknownManorHouseOrStoneKeepRelated
                        + DAT_BuildingsState::instance.buildings[buildingID].spriteID
                        + this->buildingRotationRelatedValue - 1;
                }
            }
            index++;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
