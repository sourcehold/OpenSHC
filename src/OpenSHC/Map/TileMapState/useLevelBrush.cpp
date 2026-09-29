
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
        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, &tile, (int*)&y, baseTile, baseY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                    if ((int)(uint)this->HeightLayer[tile] > highest) {
                        highest = this->HeightLayer[tile];
                    }
                    if ((int)(uint)this->HeightLayer[tile] < (int)brush) {
                        brush = this->HeightLayer[tile];
                    }
                }
                index++;
            } while (index < brushSize);
        }

        int average = (int)(brush + highest) / 2;
        tile = baseTile;
        y = baseY;
        if (brushSize < 1) {
            return;
        }

        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, &tile, (int*)&y, baseTile, baseY);
            uint logic = this->LogicLayer[tile];
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
            if (this->BuildingLayer[tile] != 0 || (logic & L_SEA) != 0) {
                continue;
            }

            if ((logic & L_RIVER) != 0) {
                this->HeightLayer[tile] = this->HeightLayer[tile] + 8;
            }
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_ROCKY;
            /* the tile moves a tenth of the way towards the brush average, plus one */
            byte levelled;
            bool levelChanged = true;
            if ((int)(uint)this->HeightLayer[tile] < average) {
                levelled = (char)((average - (int)(uint)this->HeightLayer[tile]) / 10) + this->HeightLayer[tile] + 1;
            } else if ((int)(uint)this->HeightLayer[tile] > average) {
                levelled = this->HeightLayer[tile]
                    - (char)(((int)(uint)this->HeightLayer[tile] - average) / 10) - 1;
            } else {
                levelChanged = false;
            }
            if (levelChanged) {
                this->HeightLayer[tile] = levelled;
                this->Logic2Layer[tile] = 0;
            }
            if (this->HeightLayer[tile] < 8) {
                this->HeightLayer[tile] = 8;
            }
            if (this->HeightLayer[tile] > 0x9c) {
                this->HeightLayer[tile] = 0x9c;
            }
            this->DefaultHeightLayer[tile] = this->HeightLayer[tile];
            if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                this->HeightLayer[tile] = this->HeightLayer[tile] - 8;
            }
            this->DAT_SomeTile = tile;
            this->DAT_SomeY = y;

            /* mark this tile and its eight neighbours changed, through the layer pointers */
            byte* changed = (byte*)this->ptr_ChangedLayer + tile;
            int* directionRow = (int*)this->ptr_MovementDirectionTranslationMatrix + y * 8;
            changed[1] = 2;
            changed[-1] = 2;
            changed[0] = 2;
            byte* northRow = changed + directionRow[0];
            northRow[-1] = 2;
            northRow[1] = 2;
            northRow[0] = 2;
            changed = changed + directionRow[4];
            changed[-1] = 2;
            changed[1] = 2;
            changed[0] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(y, tile);
        }
    }

}
}
