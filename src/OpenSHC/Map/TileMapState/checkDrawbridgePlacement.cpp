#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FA2D0
    void TileMapState::checkDrawbridgePlacement(int x, int y)
    {
        if (this->buildingPlacementFail != FALSE) {
            return;
        }
        this->buildingPlacementFail = TRUE;

        for (int rotation = 0; rotation < 4; rotation++) {
            int buildings[9];
            for (int count = 0; count < 9; count++) {
                uint const tileY = y + DAT_TerrainDefinedData::instance.drawBridgeOffsets[rotation][count].y;
                int const offsetX = DAT_TerrainDefinedData::instance.drawBridgeOffsets[rotation][count].x;
                uint const tileX = offsetX + x;
                buildings[count] = 0;
                if (tileX > 399 || tileY > 399) {
                    break;
                }
                if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
                    break;
                }
                int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + offsetX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    break;
                }
                buildings[count] = this->BuildingLayer[tile];
            }

            if (buildings[0] == 0) {
                continue;
            }
            if (DAT_BuildingsState::instance.buildings[buildings[0]].logicalState
                != OpenSHC::Map::Buildings::BLS_NORMAL) {
                continue;
            }
            int span;
            if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingType
                == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE) {
                span = 7;
            } else if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingType
                == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
                span = 5;
            } else {
                continue;
            }
            // the gatehouse faces along one axis, so only two of the four rotations can carry a bridge
            if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingVariation == 81) {
                if (rotation == 1 || rotation == 3) {
                    continue;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingVariation == 80) {
                if (rotation == 0 || rotation == 2) {
                    continue;
                }
            }

            int i = 0;
            int matching = 0;
            for (; i < span; i++) {
                if (buildings[i] == buildings[0]) {
                    matching++;
                }
            }
            if (matching != span) {
                continue;
            }
            this->uiBuildingRotation = rotation * 2;
            this->field_0x554944 = this->uiBuildingRotation * 25;
            this->buildingPlacementFail = FALSE;
            return;
        }
    }

}
}
