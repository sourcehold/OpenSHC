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
        int rowStart = 0;
        int rowLength = 0;
        do {
            this->LogicLayer[rowStart] = this->LogicLayer[rowStart] | L_BORDER;
            if (rowLength > 0) {
                this->LogicLayer[rowStart + 1] = this->LogicLayer[rowStart + 1] | L_BORDER_EDGE;
            }
            if (rowLength > 0 && (this->LogicLayer[rowStart + rowLength] & L_BORDER) == 0) {
                this->LogicLayer[rowStart + rowLength] = L_BORDER_EDGE;
            }
            this->LogicLayer[rowStart + rowLength + 1] = L_BORDER;
            rowStart = rowStart + rowLength + 2;
            rowLength = rowLength + 2;
        } while (rowLength < 400);

        for (rowLength = 398; rowLength > -1; rowLength = rowLength - 2) {
            this->LogicLayer[rowStart] = L_BORDER;
            if (rowLength > 0) {
                this->LogicLayer[rowStart + 1] = L_BORDER_EDGE;
            }
            if (rowLength > 0 && (this->LogicLayer[rowStart + rowLength] & L_BORDER) == 0) {
                this->LogicLayer[rowStart + rowLength] = L_BORDER_EDGE;
            }
            this->LogicLayer[rowStart + rowLength + 1] = L_BORDER;
            rowStart = rowStart + rowLength + 2;
        }

        /* and again inset by (400 - mapSize) / 2 for a map smaller than the full diamond */
        int tile = 0;
        int row = 0;
        for (int skipped = inset; skipped > 0; skipped--) {
            tile = tile + 2 + row;
            row = row + 2;
        }
        if (row < 400) {
            int edge = row - inset;
            do {
                this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER;
                if (edge > 0) {
                    this->LogicLayer[tile + inset + 1] = this->LogicLayer[tile + inset + 1] | L_BORDER_EDGE;
                }
                tile = tile + 1 + row;
                if (edge > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                    this->LogicLayer[tile - inset - 1] = this->LogicLayer[tile - inset - 1] | L_BORDER_EDGE;
                }
                this->LogicLayer[tile - inset] = this->LogicLayer[tile - inset] | L_BORDER;
                row = row + 2;
                tile = tile + 1;
                edge = edge + 2;
            } while (row < 400);
        }
        if (row < 399) {
            int edge = 0x18e - inset;
            for (int back = 0x18e; row <= back; back = back - 2) {
                this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER;
                if (edge > 0) {
                    this->LogicLayer[tile + inset + 1] = this->LogicLayer[tile + inset + 1] | L_BORDER_EDGE;
                }
                tile = tile + 1 + back;
                if (edge > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                    this->LogicLayer[tile - inset - 1] = this->LogicLayer[tile - inset - 1] | L_BORDER_EDGE;
                }
                this->LogicLayer[tile - inset] = this->LogicLayer[tile - inset] | L_BORDER;
                tile = tile + 1;
                edge = edge - 2;
            }
        }
        if (mapSize != 400) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setWalkabilityBorderLogicLayerForSmallerMapSizes,
                DAT_PathFindingState::ptr)();
        }
    }

}
}
