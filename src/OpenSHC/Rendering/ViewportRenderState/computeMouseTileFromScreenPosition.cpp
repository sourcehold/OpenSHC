#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

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
        int probeScreenY = screenY + -8;
        int foundTile = 0;
        int orientationBase = 8;

        this->viewportState.field27_0x6c = 0;
        this->viewportState.field24_0x60 = 0;
        this->viewportState.mouseX = 0;
        this->viewportState.mouseY = 0;
        if (this->viewportState.field0_0x0 == 0) {
            this->viewportState.field24_0x60 = 0;
            this->viewportState.mouseX = 0;
            this->viewportState.mouseY = 0;
            this->viewportState.field27_0x6c = 0;
            return;
        }

        uint quadrantX;
        if (this->viewportState.isZoomedOutUnk == 0) {
            uint viewportXInTile = this->viewportState.viewportX & 0x8000001f;
            if ((int)viewportXInTile < 0) {
                viewportXInTile = (viewportXInTile - 1 | 0xffffffe0) + 1;
            }
            quadrantX = (int)((viewportXInTile - this->windowX) + screenX) >> 1 & 0xf;
        } else {
            uint viewportXInTile = this->viewportState.viewportX & 0x8000001f;
            if ((int)viewportXInTile < 0) {
                viewportXInTile = (viewportXInTile - 1 | 0xffffffe0) + 1;
            }
            quadrantX = (int)((viewportXInTile + screenX * 2) - this->windowX) >> 1 & 0xf;
        }

        uint viewportYInTile = this->viewportState.viewportY & 0x8000000f;
        if ((int)viewportYInTile < 0) {
            viewportYInTile = (viewportYInTile - 1 | 0xfffffff0) + 1;
        }
        int probeOffset = probeScreenY - screenY;
        int probeDoubledY = screenY + probeScreenY;
        if (DAT_TileMapState::instance.mapOrientation == 0) {
            orientationBase = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationBase = 0x13a18;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationBase = 0x27428;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationBase = 0x3ae38;
        }

        do {
            if ((DAT_TileMapState::instance.field93_0x5548c8 != 0
                    || DAT_TileMapState::instance.flatViewToggleValue2 != 0)
                && probeOffset != -8) {
                break;
            }

            int lookupIndex;
            uint tileRowY;
            if (this->viewportState.isZoomedOutUnk == 0) {
                int unclampedY = (this->viewportState.viewportY - this->windowY) + 8 + probeScreenY;
                tileRowY = (viewportYInTile - this->windowY) + -8 + probeScreenY;
                int unclampedX = (screenX - this->windowX) + this->viewportState.viewportX;
                lookupIndex = ((int)(unclampedX + (unclampedX >> 0x1f & 0x1fU)) >> 5)
                    + ((int)(unclampedY + (unclampedY >> 0x1f & 0xfU)) >> 4) * 0x191 + orientationBase;
            } else {
                int unclampedX = ((screenX * 2 + 0xa0) - this->windowX) + this->viewportState.viewportX;
                tileRowY = (viewportYInTile - this->windowY) + probeDoubledY;
                int unclampedY = (probeDoubledY - this->windowY) + this->viewportState.viewportY;
                lookupIndex = ((int)(unclampedY + (unclampedY >> 0x1f & 0xfU)) >> 4) * 0x191
                    + ((int)(unclampedX + (unclampedX >> 0x1f & 0x1fU)) >> 5) + orientationBase;
            }

            int quadrant = DAT_MapRenderDefinedData::instance.field618_0xc24[tileRowY & 0xf][quadrantX];
            if (quadrant == 1) {
                lookupIndex = lookupIndex + 200;
            } else if (quadrant == 2) {
                lookupIndex = lookupIndex + 0xc9;
            } else if (quadrant == 3) {
                lookupIndex = lookupIndex + 0x191;
            }

            int tile = this->screenPointToTileNumber[lookupIndex + -8];
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x30U) != 0) {
                break;
            }

            int tileHeightOffset
                = DAT_TileMapState::instance.heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[tile]];
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000U) != 0) {
                tileHeightOffset = tileHeightOffset
                    + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[tile]);
            }
            if (this->viewportState.isZoomedOutUnk != 0) {
                tileHeightOffset = tileHeightOffset / 2;
            }

            if ((probeOffset - tileHeightOffset) + 8 + screenY <= screenY
                || DAT_TileMapState::instance.field93_0x5548c8 != 0
                || DAT_TileMapState::instance.flatViewToggleValue2 != 0) {
                foundTile = tile;
            }

            probeScreenY = probeScreenY + 1;
            probeDoubledY = probeDoubledY + 2;
            probeOffset = probeOffset + 1;
        } while (probeOffset < 0xff);

        this->viewportState.field24_0x60 = foundTile;
        if (DAT_TileMapState::instance.PathConnectionLayer[foundTile] == 0
            || (DAT_TileMapState::instance.LogicLayer[foundTile] & 0x200U) != 0) {
            uint direction = DAT_TileMapState::instance.field84_0x5548a4 + 4U & 0x80000007;
            if ((int)direction < 0) {
                direction = (direction - 1 | 0xfffffff8) + 1;
            }
            uint tileFlags = DAT_TileMapState::instance.LogicLayer[foundTile];
            int neighbourTile
                = DAT_TileMapState::instance
                      .directionTranslationMatrix[this->tileTranslationMatrix_YComponent[foundTile]][direction]
                + foundTile;
            if ((tileFlags & 0x40000000) == 0) {
                if ((tileFlags & 0x200) == 0) {
                    if ((tileFlags & 0x400) != 0) {
                        switch (
                            DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[foundTile]]
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
                            if ((DAT_TileMapState::instance.LogicLayer[neighbourTile] & 0x10000000U) != 0) {
                                this->viewportState.field24_0x60 = neighbourTile;
                            }
                            break;
                        default:
                            this->viewportState.field24_0x60 = 0;
                            break;
                        }
                    } else {
                        this->viewportState.field24_0x60 = 0;
                    }
                } else if ((DAT_TileMapState::instance.LogicLayer[neighbourTile] & 0x100U) != 0) {
                    this->viewportState.field24_0x60 = neighbourTile;
                }
            }
        }

        if ((DAT_TileMapState::instance.LogicLayer[this->viewportState.field24_0x60] & 0x10000300U) != 0
            && (DAT_TileMapState::instance.LogicLayer[this->viewportState.field24_0x60] & 2U) == 0) {
            this->viewportState.field27_0x6c = 1;
        }
        this->viewportState.somePitchDitchID = 0;
        this->viewportState.mouseAtomRefFloorTile = foundTile;

        if (this->viewportState.field24_0x60 == 0) {
            this->viewportState.mouseY = 0;
            this->viewportState.mouseX = 0;
            this->viewportState.field27_0x6c = 0;
            this->viewportState.field14_0x38 = 0;
            this->viewportState.field16_0x40 = 0;
            this->viewportState.field15_0x3c = 0;
            return;
        }

        this->viewportState.mouseY = this->tileTranslationMatrix_YComponent[this->viewportState.field24_0x60];
        this->viewportState.mouseX
            = this->viewportState.field24_0x60 - this->translationMatrix[this->viewportState.mouseY].addXgetTile;

        int hoveredTile = this->viewportState.field24_0x60;
        if (DAT_TileMapState::instance.flatViewToggleValue1 != 0) {
            hoveredTile = this->viewportState.mouseTile;
        }
        this->viewportState.field14_0x38 = DAT_TileMapState::instance.LogicLayer[hoveredTile] & 0x40000000;
        this->viewportState.field16_0x40 = DAT_TileMapState::instance.LogicLayer[hoveredTile] & 0x4000;

        int moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
            hoveredTile);
        if (moatID == 0) {
            this->viewportState.field14_0x38 = 0;
            this->viewportState.field16_0x40 = 0;
        }
        this->viewportState.field15_0x3c = this->viewportState.field14_0x38;
        if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_TileMapState::instance.moats[moatID].owner]
            == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
            this->viewportState.field14_0x38 = 0;
        } else {
            this->viewportState.field16_0x40 = 0;
            this->viewportState.field15_0x3c = 0;
        }

        if ((DAT_TileMapState::instance.LogicLayer[hoveredTile] & 8) != 0) {
            this->viewportState.somePitchDitchID = MACRO_CALL_MEMBER(
                OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, DAT_TileMapState::ptr)(hoveredTile);
        }
    }

}
}
