#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x00502110
    void TileMapState::useLevelBrush(int tile, uint y, uint brush, int unused)
    {
        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        int highest = 0;
        // the original reuses the brush parameter to hold the lowest height seen
        brush = 200;
        int const baseTile = tile;
        uint const baseY = y;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                int const height = this->HeightLayer[tile];
                if (height > highest) {
                    highest = height;
                }
                if (height < (int)brush) {
                    brush = height;
                }
            }
        }

        int const average = (int)(brush + highest) / 2;
        tile = baseTile;
        y = baseY;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            int const brushTile = *(int volatile*)&tile;
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
            if (this->BuildingLayer[brushTile] != 0 || (logic & L_SEA) != 0) {
                continue;
            }

            if ((logic & L_RIVER) != 0) {
                this->HeightLayer[brushTile] += 8;
            }
            this->LogicLayer[brushTile] &= ~L_ROCKY;
            // the tile moves a tenth of the way towards the brush average, plus one
            byte levelled;
            bool levelChanged = true;
            if (this->HeightLayer[brushTile] < average) {
                byte const height = *(byte volatile*)&this->HeightLayer[brushTile];
                levelled = (char)((average - height) / 10) + height + 1;
            } else if (this->HeightLayer[brushTile] > average) {
                byte const height = *(byte volatile*)&this->HeightLayer[brushTile];
                levelled = height - (char)((height - average) / 10) - 1;
            } else {
                levelChanged = false;
            }
            if (levelChanged) {
                this->HeightLayer[brushTile] = levelled;
                this->Logic2Layer[brushTile] = 0;
            }
            if (this->HeightLayer[brushTile] < 8) {
                this->HeightLayer[brushTile] = 8;
            }
            if (this->HeightLayer[brushTile] > 156) {
                this->HeightLayer[brushTile] = 156;
            }
            this->DefaultHeightLayer[brushTile] = *(byte volatile*)&this->HeightLayer[brushTile];
            if ((this->LogicLayer[brushTile] & L_RIVER) != 0) {
                this->HeightLayer[brushTile] -= 8;
            }
            uint const brushY = *(uint volatile*)&y;
            this->DAT_SomeTile = brushTile;
            this->DAT_SomeY = brushY;

            // handwritten assembly in the original: mark this tile and its eight neighbours changed
            MACRO_MARK_CHANGED_NEIGHBOURS_GLOBAL();
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(brushY, brushTile);
        }
    }

}
}
