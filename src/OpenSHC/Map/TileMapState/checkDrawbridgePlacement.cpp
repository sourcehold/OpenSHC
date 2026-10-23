#include "OpenSHC/Map/TileMapState.func.hpp"

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
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FA2D0
    void TileMapState::checkDrawbridgePlacement(int x, int y)
    {
        if (this->buildingPlacementFail != FALSE) {
            return;
        }
        this->buildingPlacementFail = TRUE;

        for (int rotation = 0; rotation < 4; rotation++) {
            int buildings[9];
            int count = 0;
            do {
                uint offsetY = DAT_TerrainDefinedData::instance.drawBridgeOffsets[rotation][count].y + y;
                int offsetX = DAT_TerrainDefinedData::instance.drawBridgeOffsets[rotation][count].x;
                buildings[count] = 0;
                if ((uint)(offsetX + x) > 399 || offsetY > 399) {
                    break;
                }
                if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[offsetY * 400 + offsetX + x] == 0) {
                    break;
                }
                int tile = DAT_ViewportRenderState::instance.translationMatrix[offsetY].addXgetTile + offsetX + x;
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    break;
                }
                buildings[count] = this->BuildingLayer[tile];
                count++;
            } while (count < 9);

            if (buildings[0] == 0) {
                continue;
            }
            if (DAT_BuildingsState::instance.buildings[buildings[0]].logicalState != OpenSHC::Map::Buildings::BLS_NORMAL) {
                continue;
            }
            int span;
            if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE) {
                span = 7;
            } else {
                if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
                    continue;
                }
                span = 5;
            }
            /* the gatehouse faces along one axis, so only two of the four rotations can carry a bridge */
            if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingVariation == 0x51) {
                if (rotation == 1 || rotation == 3) {
                    continue;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildings[0]].buildingVariation == 0x50
                && (rotation == 0 || rotation == 2)) {
                continue;
            }

            int matching = 0;
            for (int i = 0; i < span; i++) {
                if (buildings[i] == buildings[0]) {
                    matching++;
                }
            }
            if (matching == span) {
                this->buildingPlacementFail = FALSE;
                this->uiBuildingRotation = rotation * 2;
                this->field127_0x554944 = this->uiBuildingRotation * 25;
                return;
            }
        }
    }

}
}
