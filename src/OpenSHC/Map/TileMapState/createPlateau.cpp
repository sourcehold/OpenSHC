
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00501F50
    void TileMapState::createPlateau(int tile, uint the_y, int brush, int plateauHeightSetting)
    {
        int baseTile = tile;
        uint baseY = the_y;
        /* the original reuses the brush parameter to hold the size */
        brush = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];

        byte maxHeightInBrush = 0;
        int index = 0;
        if (brush > 0) {
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&the_y, baseTile, baseY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0
                    && maxHeightInBrush < this->HeightLayer[tile]) {
                    maxHeightInBrush = this->HeightLayer[tile];
                }
                index++;
            } while (index < brush);
        }

        tile = baseTile;
        the_y = baseY;
        index = 0;
        if (brush > 0) {
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &tile, (int*)&the_y, baseTile, baseY);
                if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0
                    && (this->LogicLayer[tile] & (L_SEA | L_BUILDING | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT)) == 0
                    && this->BuildingLayer[tile] == 0
                    && (this->LogicLayer[tile]
                           & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_MOAT_DUG_OR_PLANNED | L_KEEP_NON_MANOR_HOUSE
                               | L_MOAT))
                        == 0) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_ROCKY;
                    if (plateauHeightSetting == 4) {
                        this->HeightLayer[tile] = 80;
                    } else if (plateauHeightSetting == 8) {
                        this->HeightLayer[tile] = 130;
                    }
                    this->DefaultHeightLayer[tile] = this->HeightLayer[tile];
                    if ((this->LogicLayer[tile] & L_RIVER) != 0) {
                        this->HeightLayer[tile] = this->HeightLayer[tile] - 8;
                    }
                    this->Logic2Layer[tile] = (byte)plateauHeightSetting;
                    this->DAT_SomeTile = tile;
                    this->DAT_SomeY = the_y;

                    /* mark this tile and its eight neighbours changed, through the layer pointers */
                    byte* changed = (byte*)this->ptr_ChangedLayer + tile;
                    int* directionRow = (int*)this->ptr_MovementDirectionTranslationMatrix + the_y * 8;
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
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(the_y, tile);
                }
                index++;
            } while (index < brush);
        }
    }

}
}
