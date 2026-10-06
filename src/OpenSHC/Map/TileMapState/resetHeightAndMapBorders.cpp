#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6CF0
    void TileMapState::resetHeightAndMapBorders(int mapSize)
    {
        int inset = (400 - mapSize) / 2;
        this->mapSize = mapSize;
        for (int tile = 0; tile < 80400; tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            }
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_BORDER | L_BORDER_EDGE);
        }

        /* the two outer diagonals of the diamond carry the border flags */
        int rowLength = 0;
        int tile = 0;
        do {
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BORDER;
            tile++;
            if (rowLength > 0) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BORDER_EDGE;
            }
            tile = tile + rowLength;
            if (rowLength > 0 && (this->LogicLayer[tile - 1] & L_BORDER) == 0) {
                this->LogicLayer[tile - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[tile] = L_BORDER;
            rowLength = rowLength + 2;
            tile++;
        } while (rowLength < 400);

        for (rowLength = 398; rowLength >= 0; rowLength = rowLength - 2) {
            this->LogicLayer[tile] = L_BORDER;
            tile++;
            if (rowLength > 0) {
                this->LogicLayer[tile] = L_BORDER_EDGE;
            }
            tile = tile + rowLength;
            if (rowLength > 0 && (this->LogicLayer[tile - 1] & L_BORDER) == 0) {
                this->LogicLayer[tile - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[tile] = L_BORDER;
            tile++;
        }

        /* and again inset by (400 - mapSize) / 2 for a map smaller than the full diamond */
        int row = 0;
        tile = 0;
        for (int skipped = 0; skipped < inset; skipped++) {
            tile = tile + 2 + row;
            row = row + 2;
        }
        int firstRow = row;
        for (; row < 400; row = row + 2) {
            this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER;
            tile++;
            if (row - inset > 0) {
                this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER_EDGE;
            }
            tile = tile + row;
            if (row - inset > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                this->LogicLayer[tile - inset - 1] = this->LogicLayer[tile - inset - 1] | L_BORDER_EDGE;
            }
            this->LogicLayer[tile - inset] = this->LogicLayer[tile - inset] | L_BORDER;
            tile++;
        }
        for (row = 398; row >= firstRow; row = row - 2) {
            this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER;
            tile++;
            if (row - inset > 0) {
                this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER_EDGE;
            }
            tile = tile + row;
            if (row - inset > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                this->LogicLayer[tile - inset - 1] = this->LogicLayer[tile - inset - 1] | L_BORDER_EDGE;
            }
            this->LogicLayer[tile - inset] = this->LogicLayer[tile - inset] | L_BORDER;
            tile++;
        }
        if (mapSize != 400) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setWalkabilityBorderLogicLayerForSmallerMapSizes,
                DAT_PathFindingState::ptr)();
        }

        /* every border tile ends up at the minimum height */
        for (int borderTile = 0; borderTile < 80400; borderTile++) {
            if ((this->LogicLayer[borderTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->HeightLayer[borderTile] = 8;
            }
        }
    }

}
}
