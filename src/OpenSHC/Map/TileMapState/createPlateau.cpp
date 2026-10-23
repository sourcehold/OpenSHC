
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00501F50
    void TileMapState::createPlateau(int tile, uint the_y, int brush, int plateauHeightSetting)
    {
        int baseTile = tile;
        uint baseY = the_y;
        /* the original reuses the brush parameter to hold the size */
        brush = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];

        int maxHeightInBrush = 0;
        for (int index = 0; index < brush; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&the_y, baseTile, baseY);
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0
                && this->HeightLayer[tile] > maxHeightInBrush) {
                maxHeightInBrush = this->HeightLayer[tile];
            }
        }

        tile = baseTile;
        the_y = baseY;
        for (int index = 0; index < brush; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&the_y, baseTile, baseY);
            int brushTile = tile;
            uint logic = this->LogicLayer[brushTile];
            if ((logic & (L_BORDER | L_BORDER_EDGE)) == 0
                && (logic & (L_SEA | L_BUILDING | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT)) == 0
                && this->BuildingLayer[brushTile] == 0
                && (logic
                       & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_MOAT_DUG_OR_PLANNED | L_KEEP_NON_MANOR_HOUSE | L_MOAT))
                    == 0) {
                this->LogicLayer[brushTile] = this->LogicLayer[brushTile] & ~L_ROCKY;
                if (plateauHeightSetting == 4) {
                    this->HeightLayer[brushTile] = 80;
                } else if (plateauHeightSetting == 8) {
                    this->HeightLayer[brushTile] = 130;
                }
                this->DefaultHeightLayer[brushTile] = this->HeightLayer[brushTile];
                if ((this->LogicLayer[brushTile] & L_RIVER) != 0) {
                    this->HeightLayer[brushTile] = this->HeightLayer[brushTile] - 8;
                }
                uint brushY = the_y;
                this->Logic2Layer[brushTile] = (byte)plateauHeightSetting;
                this->DAT_SomeTile = brushTile;
                this->DAT_SomeY = brushY;

                /* handwritten assembly in the original: mark this tile and its eight neighbours changed */
                MACRO_MARK_CHANGED_NEIGHBOURS()
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    DAT_PathFindingState::ptr)(brushY, brushTile);
            }
        }
    }

}
}
