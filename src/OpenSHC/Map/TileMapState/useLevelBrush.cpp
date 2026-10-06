
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x00502110
    void TileMapState::useLevelBrush(int tile, uint y, uint brush, int param_4)
    {
        int baseTile = tile;
        uint baseY = y;
        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];

        int highest = 0;
        /* the original reuses the brush parameter to hold the lowest height seen */
        brush = 200;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                int height = this->HeightLayer[tile];
                if (height > highest) {
                    highest = height;
                }
                if (height < (int)brush) {
                    brush = height;
                }
            }
        }

        int average = (int)(brush + highest) / 2;
        tile = baseTile;
        y = baseY;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, &tile, (int*)&y, baseTile, baseY);
            int brushTile = tile;
            uint logic = this->LogicLayer[brushTile];
            if ((logic & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }
            if ((logic & (L_SEA | L_MARSH)) != 0 && this->unknownZero_0x554904 == 0) {
                continue;
            }
            if ((logic & (L_SEA | L_MARSH)) == 0 && this->unknownZero_0x554904 == 1) {
                continue;
            }
            if ((logic
                    & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_MOAT_DUG_OR_PLANNED | L_KEEP_NON_MANOR_HOUSE | L_MOAT))
                != 0) {
                continue;
            }
            if (this->BuildingLayer[brushTile] != 0 || (logic & L_SEA) != 0) {
                continue;
            }

            if ((logic & L_RIVER) != 0) {
                this->HeightLayer[brushTile] = this->HeightLayer[brushTile] + 8;
            }
            this->LogicLayer[brushTile] = this->LogicLayer[brushTile] & ~L_ROCKY;
            /* the tile moves a tenth of the way towards the brush average, plus one */
            byte levelled;
            bool levelChanged = true;
            if ((int)(uint)this->HeightLayer[brushTile] < average) {
                levelled = (char)((average - (int)(uint)this->HeightLayer[brushTile]) / 10)
                    + this->HeightLayer[brushTile] + 1;
            } else if ((int)(uint)this->HeightLayer[brushTile] > average) {
                levelled = this->HeightLayer[brushTile]
                    - (char)(((int)(uint)this->HeightLayer[brushTile] - average) / 10) - 1;
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
            if (this->HeightLayer[brushTile] > 0x9c) {
                this->HeightLayer[brushTile] = 0x9c;
            }
            this->DefaultHeightLayer[brushTile] = this->HeightLayer[brushTile];
            if ((this->LogicLayer[brushTile] & L_RIVER) != 0) {
                this->HeightLayer[brushTile] = this->HeightLayer[brushTile] - 8;
            }
            uint brushY = y;
            this->DAT_SomeTile = brushTile;
            this->DAT_SomeY = brushY;

            /* handwritten assembly in the original: mark this tile and its eight neighbours changed */
            MACRO_MARK_CHANGED_NEIGHBOURS()
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(brushY, brushTile);
        }
    }

}
}
