#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapRenderDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5ED0
    void ViewportRenderState::computeMouseTileFromScreenPosition(int screenX, int screenY)
    {
        int probeScreenY = screenY - 8;
        int foundTile = 0;
        int orientationBase = 8;

        this->viewportState.field_0x6c = 0;
        this->viewportState.cursorTile = 0;
        this->viewportState.mouseX = 0;
        this->viewportState.mouseY = 0;
        if (this->viewportState.field_0x0 == 0) {
            return;
        }

        int const& isZoomedOut = this->viewportState.isZoomedOutUnk;
        int quadrantX;
        if (isZoomedOut == 0) {
            quadrantX = ((this->viewportState.viewportX % 32 - this->windowX) + screenX) >> 1 & 0xf;
        } else {
            quadrantX = ((this->viewportState.viewportX % 32 + screenX * 2) - this->windowX) >> 1 & 0xf;
        }

        if (DAT_TileMapState::instance.mapOrientation == 0) {
            orientationBase = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationBase = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationBase = 160808;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationBase = 241208;
        }
        int probeDoubledY = probeScreenY * 2 + 8;
        int probeOffset = probeScreenY - screenY;

        // a do-while on purpose: the same loop as a for adds an entry test the original does not have (0.88 -> 0.59)
        do {
            if ((DAT_TileMapState::instance.disableElevationRendering != 0
                    || DAT_TileMapState::instance.flatViewToggleValue2 != 0)
                && probeOffset != -8) {
                break;
            }

            int lookupIndex;
            int tileRowY;
            if (this->viewportState.isZoomedOutUnk == 0) {
                int unclampedY = (this->viewportState.viewportY - this->windowY) + 8 + probeScreenY;
                tileRowY = ((this->viewportState.viewportY % 16 - this->windowY) + probeScreenY - 8) & 0xf;
                int unclampedX = (screenX - this->windowX) + this->viewportState.viewportX;
                lookupIndex = (unclampedX / 32) + (unclampedY / 16) * 401 + orientationBase;
            } else {
                int unclampedX = ((screenX * 2 + 160) - this->windowX) + this->viewportState.viewportX;
                tileRowY = ((this->viewportState.viewportY % 16 - this->windowY) + probeDoubledY) & 0xf;
                int unclampedY = (probeDoubledY - this->windowY) + this->viewportState.viewportY;
                lookupIndex = (unclampedY / 16) * 401 + (unclampedX / 32) + orientationBase;
            }

            int quadrant = DAT_MapRenderDefinedData::instance.field_0xc24[tileRowY][quadrantX];
            if (quadrant == 1) {
                lookupIndex = lookupIndex + 200;
            } else if (quadrant == 2) {
                lookupIndex = lookupIndex + 201;
            } else if (quadrant == 3) {
                lookupIndex = lookupIndex + 401;
            }

            int tile = this->screenPointToTileNumber[lookupIndex];
            if ((DAT_TileMapState::instance.LogicLayer[tile]
                    & (Map::LogicHelpers::L_BORDER | Map::LogicHelpers::L_BORDER_EDGE))
                != 0) {
                break;
            }

            int tileHeightOffset
                = DAT_TileMapState::instance.heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[tile]];
            if ((DAT_TileMapState::instance.LogicLayer[tile] & Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) != 0) {
                tileHeightOffset = tileHeightOffset
                    + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[tile]);
            }
            if (this->viewportState.isZoomedOutUnk != 0) {
                tileHeightOffset = tileHeightOffset / 2;
            }

            if ((probeOffset - tileHeightOffset) + 8 + screenY <= screenY
                || DAT_TileMapState::instance.disableElevationRendering != 0
                || DAT_TileMapState::instance.flatViewToggleValue2 != 0) {
                foundTile = tile;
            }

            probeScreenY = probeScreenY + 1;
            probeDoubledY = probeDoubledY + 2;
            probeOffset = probeOffset + 1;
        } while (probeOffset < 255);

        this->viewportState.mouseAtomRefFloorTile = foundTile;
        if (DAT_TileMapState::instance.PathConnectionLayer[foundTile] == 0
            || (DAT_TileMapState::instance.LogicLayer[foundTile] & Map::LogicHelpers::L_CRENEL) != 0) {
            int neighbourTile
                = DAT_TileMapState::instance
                      .directionTranslationMatrix[this->tileTranslationMatrix_YComponent[foundTile]]
                                                 [(DAT_TileMapState::instance.screenSouthEastDirection + 4) % 8]
                + foundTile;
            uint tileFlags = DAT_TileMapState::instance.LogicLayer[foundTile];
            if ((tileFlags & Map::LogicHelpers::L_MOAT) == 0) {
                if ((tileFlags & Map::LogicHelpers::L_CRENEL) != 0) {
                    if ((DAT_TileMapState::instance.LogicLayer[neighbourTile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                        != 0) {
                        foundTile = neighbourTile;
                    }
                } else if ((tileFlags & Map::LogicHelpers::L_BUILDING) != 0) {
                    switch (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[foundTile]]
                            .buildingType) {
                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    case OpenSHC::Map::Buildings::BT_KEEPFOUR:
                    case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                    case OpenSHC::Map::Buildings::BT_TOWER:
                    case OpenSHC::Map::Buildings::BT_TOWER1:
                    case OpenSHC::Map::Buildings::BT_TOWER2:
                    case OpenSHC::Map::Buildings::BT_TOWER3:
                    case OpenSHC::Map::Buildings::BT_TOWER4:
                    case OpenSHC::Map::Buildings::BT_TOWER5:
                        if ((DAT_TileMapState::instance.LogicLayer[neighbourTile]
                                & Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                            != 0) {
                            foundTile = neighbourTile;
                        }
                        break;
                    default:
                        foundTile = 0;
                        break;
                    }
                } else {
                    foundTile = 0;
                }
            }
        }

        if ((DAT_TileMapState::instance.LogicLayer[foundTile]
                & (Map::LogicHelpers::L_WALL_OR_GATEHOUSE | Map::LogicHelpers::L_CRENEL
                    | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE))
                != 0
            && (DAT_TileMapState::instance.LogicLayer[foundTile] & 2) == 0) {
            this->viewportState.field_0x6c = 1;
        }
        this->viewportState.cursorTile = foundTile;
        this->viewportState.somePitchDitchID = 0;
        if (foundTile == 0) {
            this->viewportState.mouseY = 0;
            this->viewportState.mouseX = 0;
            this->viewportState.field_0x6c = 0;
            this->viewportState.field_0x38 = 0;
            this->viewportState.field_0x40 = 0;
            this->viewportState.field_0x3c = 0;
            return;
        }

        this->viewportState.mouseY = this->tileTranslationMatrix_YComponent[foundTile];
        this->viewportState.mouseX = foundTile - this->translationMatrix[this->viewportState.mouseY].addXgetTile;
        if (DAT_TileMapState::instance.flatViewToggleValue1 != 0) {
            foundTile = this->viewportState.mouseTile;
        }
        this->viewportState.field_0x38 = DAT_TileMapState::instance.LogicLayer[foundTile] & Map::LogicHelpers::L_MOAT;
        this->viewportState.field_0x40
            = DAT_TileMapState::instance.LogicLayer[foundTile] & Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
        int moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
            foundTile);
        if (moatID == 0) {
            this->viewportState.field_0x38 = 0;
            this->viewportState.field_0x40 = 0;
        }
        this->viewportState.field_0x3c = this->viewportState.field_0x38;
        if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_TileMapState::instance.moats[moatID].owner]
            == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
            this->viewportState.field_0x38 = 0;
        } else {
            this->viewportState.field_0x40 = 0;
            this->viewportState.field_0x3c = 0;
        }
        if ((DAT_TileMapState::instance.LogicLayer[foundTile] & 8) != 0) {
            this->viewportState.somePitchDitchID = MACRO_CALL_MEMBER(
                OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(foundTile);
        }
    }

}
}
