#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x00501F50
    void TileMapState::createPlateau(int tile, uint y, int brush, int plateauHeightSetting)
    {
        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        int maxHeightInBrush = 0;
        int const baseTile = tile;
        uint const baseY = y;

        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0
                && this->HeightLayer[tile] > maxHeightInBrush) {
                maxHeightInBrush = this->HeightLayer[tile];
            }
        }

        tile = baseTile;
        y = baseY;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            int const brushTile = *(int volatile*)&tile;
            if ((this->LogicLayer[brushTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile] & (L_SEA | L_BUILDING | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT)) != 0) {
                continue;
            }
            if (this->BuildingLayer[brushTile] != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile]
                    & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_MOAT_DUG_OR_PLANNED | L_KEEP_NON_MANOR_HOUSE | L_MOAT))
                != 0) {
                continue;
            }
            this->LogicLayer[brushTile] &= ~L_ROCKY;
            if (plateauHeightSetting == 4) {
                this->HeightLayer[brushTile] = 80;
            } else if (plateauHeightSetting == 8) {
                this->HeightLayer[brushTile] = 130;
            }
            this->DefaultHeightLayer[brushTile] = this->HeightLayer[brushTile];
            if ((this->LogicLayer[brushTile] & L_RIVER) != 0) {
                this->HeightLayer[brushTile] -= 8;
            }
            uint const brushY = *(uint volatile*)&y;
            this->Logic2Layer[brushTile] = (byte)plateauHeightSetting;
            this->DAT_SomeTile = brushTile;
            this->DAT_SomeY = brushY;

            // handwritten assembly in the original: mark this tile and its eight neighbours changed
            MACRO_MARK_CHANGED_NEIGHBOURS_GLOBAL()
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(brushY, brushTile);
        }
    }

}
}
