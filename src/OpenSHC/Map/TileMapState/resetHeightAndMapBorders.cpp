#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6CF0
    void TileMapState::resetHeightAndMapBorders(int mapSize)
    {
        int inset = (MC_MAP_XY_LIMIT - mapSize) / 2;
        this->mapSize = mapSize;
        for (int tile = 0; tile < countof(this->LogicLayer); tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            }
            this->LogicLayer[tile] &= ~(L_BORDER | L_BORDER_EDGE);
        }

        int rowLength = 0;
        int tile = 0;
        for (; rowLength < MC_MAP_XY_LIMIT; rowLength += 2) {
            this->LogicLayer[tile] |= L_BORDER;
            tile++;
            if (rowLength > 0) {
                this->LogicLayer[tile] |= L_BORDER_EDGE;
            }
            tile += rowLength;
            if (rowLength > 0 && (this->LogicLayer[tile - 1] & L_BORDER) == 0) {
                this->LogicLayer[tile - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[tile] = L_BORDER;
            tile++;
        }

        for (rowLength = MC_MAP_XY_LIMIT - 2; rowLength >= 0; rowLength -= 2) {
            this->LogicLayer[tile] = L_BORDER;
            tile++;
            if (rowLength > 0) {
                this->LogicLayer[tile] = L_BORDER_EDGE;
            }
            tile += rowLength;
            if (rowLength > 0 && (this->LogicLayer[tile - 1] & L_BORDER) == 0) {
                this->LogicLayer[tile - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[tile] = L_BORDER;
            tile++;
        }

        int row = 0;
        tile = 0;
        for (int skipped = 0; skipped < inset; skipped++) {
            tile += 2 + row;
            row += 2;
        }
        int firstRow = row;
        for (; row < MC_MAP_XY_LIMIT; row += 2) {
            this->LogicLayer[tile + inset] |= L_BORDER;
            tile++;
            if (row - inset > 0) {
                this->LogicLayer[tile + inset] |= L_BORDER_EDGE;
            }
            tile += row;
            if (row - inset > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                this->LogicLayer[tile - inset - 1] |= L_BORDER_EDGE;
            }
            this->LogicLayer[tile - inset] |= L_BORDER;
            tile++;
        }
        for (row = MC_MAP_XY_LIMIT - 2; row >= firstRow; row -= 2) {
            this->LogicLayer[tile + inset] |= L_BORDER;
            tile++;
            if (row - inset > 0) {
                this->LogicLayer[tile + inset] |= L_BORDER_EDGE;
            }
            tile += row;
            if (row - inset > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                this->LogicLayer[tile - inset - 1] |= L_BORDER_EDGE;
            }
            this->LogicLayer[tile - inset] |= L_BORDER;
            tile++;
        }
        if (mapSize != MC_MAP_XY_LIMIT) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::setWalkabilityBorderLogicLayerForSmallerMapSizes,
                DAT_PathFindingState::ptr)();
        }

        for (int borderTile = 0; borderTile < countof(this->LogicLayer); borderTile++) {
            if ((this->LogicLayer[borderTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->HeightLayer[borderTile] = 8;
            }
        }
    }

}
}
