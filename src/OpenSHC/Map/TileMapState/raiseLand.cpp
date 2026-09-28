
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00501D90
    void TileMapState::raiseLand(int tile, uint y, uint brush, int change)
    {
        int baseTile = tile;
        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        int index = 0;
        /* the original reuses the brush parameter to hold the base y */
        brush = y;
        if (brushSize < 1) {
            this->forceUpdateTextureTilemap = 1;
            this->forceUpdateLogicalAndMiscDisplayLayers = 1;
            return;
        }

        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, brush);
            uint logic = this->LogicLayer[tile];
            if ((logic & (L_BORDER | L_BORDER_EDGE)) == 0
                && ((logic & (L_SEA | L_MARSH)) == 0 || this->unknownZero_0x554904 != 0)
                && ((logic & (L_SEA | L_MARSH)) != 0 || this->unknownZero_0x554904 != 1)
                && (logic
                       & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_MOAT_DUG_OR_PLANNED | L_KEEP_NON_MANOR_HOUSE | L_MOAT))
                    == 0
                && this->BuildingLayer[tile] == 0) {
                byte minHeight;
                byte maxHeight;
                if ((logic & L_SEA) != 0) {
                    minHeight = 0;
                    maxHeight = 0;
                } else if ((logic & (L_SEA | L_MARSH | L_MOAT)) == 0) {
                    minHeight = 8;
                    maxHeight = 128;
                } else {
                    minHeight = 0;
                    maxHeight = 20;
                }
                this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_ROCKY;
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 8;
                }
                this->ChangedLayer[tile] = 2;
                if (this->HeightLayer[tile] <= minHeight) {
                    this->HeightLayer[tile] = minHeight;
                }
                if (this->HeightLayer[tile] != 0 || change >= 0) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] + (char)change;
                    this->Logic2Layer[tile] = 0;
                }
                if (this->HeightLayer[tile] < minHeight) {
                    this->HeightLayer[tile] = minHeight;
                }
                if (this->HeightLayer[tile] > maxHeight) {
                    this->HeightLayer[tile] = maxHeight;
                }
                this->DefaultHeightLayer[tile] = this->HeightLayer[tile];
                if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] - 8;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    DAT_PathFindingState::ptr)(y, tile);
            }
            index++;
        } while (index < brushSize);
        this->forceUpdateTextureTilemap = 1;
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
    }

}
}
