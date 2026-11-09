#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapRenderDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8430
    void ViewportRenderState::updateBuildingPreviewPosition(int mouseXScreenSpace, int mouseYScreenSpace)
    {
        int orientationBase = 8;

        this->viewportState.field_0x0 = 1;
        if (mouseYScreenSpace - this->windowY < 0) {
            this->viewportState.field_0x0 = 0;
        }
        if (mouseYScreenSpace - this->windowY >= this->screenPixelHeight) {
            this->viewportState.field_0x0 = 0;
        }
        if (mouseXScreenSpace - this->windowX < 0) {
            this->viewportState.field_0x0 = 0;
        }
        if (mouseXScreenSpace - this->windowX >= this->screenPixelWidth) {
            this->viewportState.field_0x0 = 0;
        }

        if (DAT_TextureRenderCoreObject::instance.activeMenuTabIndex != 0) {
            int const tab = DAT_TextureRenderCoreObject::instance.activeMenuTabIndex - 1;
            for (int i = 0; DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][0].x != -1;
                i++) {
                if (mouseXScreenSpace >= DAT_MenuHandlerState::instance.x
                            + DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][0].x
                    && mouseXScreenSpace
                        <= DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][1].x
                            + DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][0].x
                            + DAT_MenuHandlerState::instance.x
                    && mouseYScreenSpace
                        >= DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][0].y
                            + DAT_MenuHandlerState::instance.y
                    && mouseYScreenSpace
                        <= DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][1].y
                            + DAT_MapRenderDefinedData::instance.BuildingPreviewPositionRelatedOffsets[tab][i][0].y
                            + DAT_MenuHandlerState::instance.y) {
                    this->viewportState.field_0x0 = 0;
                    return;
                }
            }
        }

        if (this->viewportState.field_0x0 == 0) {
            if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILD_MENU) {
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                && DAT_TileMapState::instance.shiftRelated0or3 != 1) {
                return;
            }

            mouseXScreenSpace = 0;
            mouseYScreenSpace = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::convertMinimapClickToTileXY,
                DAT_MinimapViewState::ptr)(&mouseXScreenSpace, &mouseYScreenSpace);
            if (mouseXScreenSpace == -1) {
                return;
            }

            int minimapTile = this->translationMatrix[mouseYScreenSpace].addXgetTile + mouseXScreenSpace;
            this->viewportState.field_0x48 = 0;
            this->viewportState.field_0x18 = DAT_TileMapState::instance.BuildingLayer[minimapTile];
            this->viewportState.field_0x20 = DAT_TileMapState::instance.UnitLayer[minimapTile];
            this->viewportState.mouseRayEntityID = DAT_TileMapState::instance.EntityLayer[minimapTile];

            int minimapGateTile = 0;
            short minimapBuildingID = DAT_TileMapState::instance.BuildingLayer[minimapTile];
            if (minimapBuildingID <= 0
                && (DAT_TileMapState::instance.LogicLayer[minimapTile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE) != 0) {
                minimapGateTile = minimapTile;
            } else if (DAT_TileMapState::instance.BuildingLayer[minimapTile] <= 0) {
                this->viewportState.field_0x48 = DAT_TileMapState::instance.BuildingWasLayer[minimapTile];
            }
            if (0 <= minimapGateTile) {
                this->viewportState.mouseRayBuildingID = 0;
                this->viewportState.cursorWallTile = minimapGateTile;
            }

            this->viewportState.mouseX = mouseXScreenSpace;
            this->viewportState.mouseTileX = mouseXScreenSpace;
            this->viewportState.mouseAtomRefFloorTile = minimapTile;
            this->viewportState.cursorTile = minimapTile;
            this->viewportState.mouseTile = minimapTile;
            this->viewportState.mouseY = mouseYScreenSpace;
            this->viewportState.mouseTileY = mouseYScreenSpace;
            this->viewportState.field_0x38
                = DAT_TileMapState::instance.LogicLayer[minimapTile] & Map::LogicHelpers::L_MOAT;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(
                    minimapTile)
                == 0) {
                this->viewportState.field_0x38 = 0;
            }
            this->viewportState.field_0x40
                = DAT_TileMapState::instance.LogicLayer[minimapTile] & Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
            return;
        }

        int quadrantX;
        int quadrantY;
        if (this->viewportState.isZoomedOutUnk == 0) {
            quadrantX = ((this->viewportState.viewportX % 32 - this->windowX) + mouseXScreenSpace) >> 1 & 0xf;
            quadrantY = (this->viewportState.viewportY % 16 - this->windowY) + mouseYScreenSpace - 8;
        } else {
            quadrantX = ((this->viewportState.viewportX % 32 + mouseXScreenSpace * 2) - this->windowX) >> 1 & 0xf;
            quadrantY = (this->viewportState.viewportY % 16 + mouseYScreenSpace * 2 - 8) - this->windowY;
        }
        quadrantY = quadrantY & 0xf;

        if (DAT_TileMapState::instance.mapOrientation == 0) {
            orientationBase = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationBase = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationBase = 160808;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationBase = 241208;
        }

        int lookupIndex;
        if (this->viewportState.isZoomedOutUnk == 0) {
            int const unclampedY = (this->viewportState.viewportY - this->windowY) + mouseYScreenSpace + 8;
            int const unclampedX = (this->viewportState.viewportX - this->windowX) + mouseXScreenSpace;
            lookupIndex = unclampedX / 32 + orientationBase + unclampedY / 16 * 401;
        } else {
            int const unclampedY = ((mouseYScreenSpace * 2 + 8) - this->windowY) + this->viewportState.viewportY;
            int const unclampedX = ((mouseXScreenSpace * 2 + 160) - this->windowX) + this->viewportState.viewportX;
            lookupIndex = unclampedX / 32 + orientationBase + unclampedY / 16 * 401;
        }
        int quadrant = DAT_MapRenderDefinedData::instance.field_0xc24[quadrantY][quadrantX];
        if (quadrant == 1) {
            lookupIndex = lookupIndex + 200;
        } else if (quadrant == 2) {
            lookupIndex = lookupIndex + 201;
        } else if (quadrant == 3) {
            lookupIndex = lookupIndex + 401;
        }

        this->viewportState.mouseTile = this->screenPointToTileNumber[lookupIndex];
        this->viewportState.field_0x14 = DAT_TileMapState::instance.EntityLayer[this->viewportState.mouseTile];
        this->viewportState.field_0x14 = DAT_TileMapState::instance.LogicLayer[this->viewportState.mouseTile];
        this->viewportState.field_0x18 = DAT_TileMapState::instance.BuildingLayer[this->viewportState.mouseTile];
        this->viewportState.field_0x20 = DAT_TileMapState::instance.UnitLayer[this->viewportState.mouseTile];
        this->viewportState.field_0x48 = 0;

        if (this->viewportState.mouseRayUnitID != 0) {
            this->viewportState.mouseRayLastUnitID = this->viewportState.mouseRayUnitID;
            this->viewportState.field_0x34 = timeGetTime();
            if (DAT_UnitsState::instance.units[this->viewportState.mouseRayUnitID].unitType
                    == OpenSHC::Map::Units::UT_S_TOWER
                && DAT_UnitsState::instance.units[this->viewportState.mouseRayUnitID].state.generic
                    == (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                this->viewportState.mouseRayBuildingID
                    = DAT_UnitsState::instance.units[this->viewportState.mouseRayUnitID].workplaceBuildingID_1;
                this->viewportState.mouseRayUnitID = 0;
            }
        }

        this->viewportState.field_0x4c = DAT_MapRenderDefinedData::instance.field_0x1024[quadrantY][quadrantX];
        this->viewportState.field_0x50 = DAT_MapRenderDefinedData::instance.field_0x1424[quadrantY][quadrantX];
        this->viewportState.field_0x58
            = DAT_UnitPropertiesDefinedData::instance
                  .field_0x10f4c[this->viewportState.field_0x4c + this->viewportState.field_0x50 * 8][0];
        this->viewportState.field_0x5c
            = DAT_UnitPropertiesDefinedData::instance
                  .field_0x10f4c[this->viewportState.field_0x4c + this->viewportState.field_0x50 * 8][1];
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY2, this)();

        int lastBuildingID = -1;
        int hoveredBuildingID = -1;
        int hoveredGateTile = -1;
        short hoveredBuildingLayer = DAT_TileMapState::instance.BuildingLayer[this->viewportState.mouseTile];
        if (hoveredBuildingLayer <= 0
            && (DAT_TileMapState::instance.LogicLayer[this->viewportState.mouseTile]
                   & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                != 0) {
            hoveredGateTile = this->viewportState.mouseTile;
        } else if (DAT_TileMapState::instance.BuildingLayer[this->viewportState.mouseTile] <= 0) {
            this->viewportState.field_0x48 = DAT_TileMapState::instance.BuildingWasLayer[this->viewportState.mouseTile];
        }

        orientationBase = 8;
        if (DAT_TileMapState::instance.mapOrientation == 0) {
            orientationBase = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            orientationBase = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            orientationBase = 160808;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            orientationBase = 241208;
        }

        int zoomDivisor = 1;
        if (this->viewportState.isZoomedOutUnk != 0) {
            zoomDivisor = 2;
        }

        int probeDoubledY = mouseYScreenSpace * 2 + 8;
        int probeScreenY = mouseYScreenSpace - 8;
        for (int probeOffset = -8; probeOffset < 255; probeOffset++) {
            if ((DAT_TileMapState::instance.disableElevationRendering != 0
                    || DAT_TileMapState::instance.flatViewToggleValue2 != 0)
                && probeOffset != -8) {
                break;
            }

            int probeIndex;
            int probeRowY;
            if (this->viewportState.isZoomedOutUnk == 0) {
                int probeY = (this->viewportState.viewportY - this->windowY) + 16 + probeScreenY;
                int probeX = (this->viewportState.viewportX - this->windowX) + mouseXScreenSpace;
                probeRowY = ((this->viewportState.viewportY % 16 - this->windowY) + probeScreenY) & 0xf;
                probeIndex = (probeX / 32) + (probeY / 16) * 401 + orientationBase;
            } else {
                int probeX = ((mouseXScreenSpace * 2 + 160) - this->windowX) + this->viewportState.viewportX;
                probeRowY = ((this->viewportState.viewportY % 16 - this->windowY) + probeDoubledY) & 0xf;
                int probeY = (this->viewportState.viewportY - this->windowY) + probeDoubledY;
                probeIndex = (probeY / 16) * 401 + (probeX / 32) + orientationBase;
            }

            int probeQuadrant = DAT_MapRenderDefinedData::instance.field_0xc24[probeRowY][quadrantX];
            if (probeQuadrant == 1) {
                probeIndex = probeIndex + 200;
            } else if (probeQuadrant == 2) {
                probeIndex = probeIndex + 201;
            } else if (probeQuadrant == 3) {
                probeIndex = probeIndex + 401;
            }

            int probeTile = this->screenPointToTileNumber[probeIndex];
            if ((DAT_TileMapState::instance.LogicLayer[probeTile]
                    & (Map::LogicHelpers::L_BORDER | Map::LogicHelpers::L_BORDER_EDGE))
                != 0) {
                break;
            }

            int probeBuildingID = DAT_TileMapState::instance.BuildingLayer[probeTile];
            if (probeBuildingID <= 0) {
                if ((DAT_TileMapState::instance.LogicLayer[probeTile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE) != 0) {
                    if (probeScreenY
                                - DAT_TileMapState::instance
                                        .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[probeTile]]
                                    / zoomDivisor
                            <= mouseYScreenSpace
                        || DAT_TileMapState::instance.disableElevationRendering != 0
                        || DAT_TileMapState::instance.flatViewToggleValue2 != 0) {
                        hoveredBuildingID = -1;
                        hoveredGateTile = probeTile;
                    }
                } else if (probeScreenY
                            - DAT_TileMapState::instance
                                    .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[probeTile]]
                                / zoomDivisor
                        <= mouseYScreenSpace
                    || DAT_TileMapState::instance.disableElevationRendering != 0
                    || DAT_TileMapState::instance.flatViewToggleValue2 != 0) {
                    this->viewportState.field_0x48 = DAT_TileMapState::instance.BuildingWasLayer[probeTile];
                    hoveredBuildingID = -1;
                }
            } else if (probeBuildingID != this->viewportState.field_0x18 && probeBuildingID != hoveredBuildingID
                && probeBuildingID != lastBuildingID) {
                if ((probeScreenY
                        - DAT_GMImageHeaders::instance.imh[DAT_TileMapState::instance.GfxLayer[probeTile]].tileOffset
                            / zoomDivisor)
                        - DAT_TileMapState::instance
                                .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[probeTile]]
                            / zoomDivisor
                    <= mouseYScreenSpace) {
                    hoveredBuildingID = probeBuildingID;
                    hoveredGateTile = -1;
                }
                lastBuildingID = probeBuildingID;
            }

            probeDoubledY = probeDoubledY + 2;
            probeScreenY = probeScreenY + 1;
        }

        this->viewportState.cursorWallTile = 0;
        if (hoveredBuildingID != -1) {
            BuildingTypeShort hoveredBuildingType
                = DAT_BuildingsState::instance.buildings[hoveredBuildingID].buildingType;
            if ((hoveredBuildingType == OpenSHC::Map::Buildings::BT_GRANARY
                    || hoveredBuildingType == OpenSHC::Map::Buildings::BT_ARMORY)
                && DAT_BuildingsState::instance.buildings[hoveredBuildingID].buildingIsVisuallyActive != 0) {
                this->viewportState.mouseRayBuildingID = hoveredBuildingID;
                this->viewportState.mouseRayUnitID = 0;
            }
        } else if (hoveredGateTile >= 0) {
            this->viewportState.mouseRayBuildingID = 0;
            this->viewportState.cursorWallTile = hoveredGateTile;
        }

        if (this->viewportState.field_0x48 != 0) {
            uint textNumInGroup = this->viewportState.field_0x48;
            switch (this->viewportState.field_0x48) {
            case 86:
                textNumInGroup = 74;
                break;
            case 87:
                textNumInGroup = 75;
                break;
            case 88:
                textNumInGroup = 76;
                break;
            case 89:
                textNumInGroup = 77;
                break;
            case 79:
                textNumInGroup = 78;
                break;
            case 41:
                textNumInGroup = 42;
                break;
            case 42:
                textNumInGroup = 44;
                break;
            }
            // set the text also for ruins tooltip: "This was a Round Tower"
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(5, 78, textNumInGroup, 0, 40, -1);
        }

        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeMouseTileFromScreenPosition, this)(
            mouseXScreenSpace, mouseYScreenSpace);
    }

}
}
