#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x00501D90
    void TileMapState::raiseLand(int tile, uint y, uint brush, int change)
    {
        int const baseTile = tile;
        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        // the original reuses the brush parameter to hold the base y
        brush = y;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, brush);
            int const brushTile = tile;
            uint const logic = this->LogicLayer[brushTile];
            if ((logic & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }
            if ((logic & (L_SEA | L_MARSH)) != 0 && this->editorAffectType == 0) {
                continue;
            }
            if ((logic & (L_SEA | L_MARSH)) == 0 && this->editorAffectType == 1) {
                continue;
            }
            if ((logic & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_MOAT_DUG_OR_PLANNED | L_KEEP_NON_MANOR_HOUSE | L_MOAT))
                != 0) {
                continue;
            }
            if (this->BuildingLayer[brushTile] != 0) {
                continue;
            }
            int minHeight;
            int maxHeight;
            if ((logic & L_SEA) != 0) {
                minHeight = 0;
                maxHeight = 0;
            } else if ((logic & (L_SEA | L_MARSH | L_MOAT)) != 0) {
                minHeight = 0;
                maxHeight = 20;
            } else {
                minHeight = 8;
                maxHeight = 128;
            }
            this->LogicLayer[brushTile] &= ~L_ROCKY;
            if ((this->LogicLayer[brushTile] & L_RIVER) != 0) {
                this->HeightLayer[brushTile] += 8;
            }
            this->ChangedLayer[brushTile] = 2;
            if (this->HeightLayer[brushTile] <= minHeight) {
                this->HeightLayer[brushTile] = (byte)minHeight;
            }
            if (this->HeightLayer[brushTile] > 0 || change >= 0) {
                this->HeightLayer[brushTile] += (char)change;
                this->Logic2Layer[brushTile] = 0;
            }
            if (this->HeightLayer[brushTile] < minHeight) {
                this->HeightLayer[brushTile] = (byte)minHeight;
            }
            if (this->HeightLayer[brushTile] > maxHeight) {
                this->HeightLayer[brushTile] = (byte)maxHeight;
            }
            this->DefaultHeightLayer[brushTile] = this->HeightLayer[brushTile];
            if ((this->LogicLayer[brushTile] & L_RIVER) != 0) {
                this->HeightLayer[brushTile] -= 8;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(y, brushTile);
        }
        this->forceUpdateTextureTilemap = 1;
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
    }

}
}
