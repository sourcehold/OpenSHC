#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
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
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00502680
    void TileMapState::useTerrainHeightBrush(int tile, uint y, uint brush, short mapper)
    {
        int const baseTile = tile;
        uint const baseY = y;
        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];

        int highest = 0;
        int lowest = 200;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }
            if (this->HeightLayer[tile] > highest) {
                highest = this->HeightLayer[tile];
            }
            if (this->HeightLayer[tile] < lowest) {
                lowest = this->HeightLayer[tile];
            }
        }

        int const average = (lowest + highest) / 2;
        tile = baseTile;
        y = baseY;
        for (int index = 0; index < brushSize; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, index, &tile, (int*)&y, baseTile, baseY);
            int const brushTile = *(int volatile*)&tile;
            if ((this->LogicLayer[brushTile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }
            if ((this->LogicLayer[brushTile]
                    & (L_SEA | L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT))
                != 0) {
                continue;
            }
            if (this->BuildingLayer[brushTile] != 0) {
                continue;
            }

            this->HeightLayer[brushTile] += 1;
            if (mapper == 0) {
                // mapper min
                this->HeightLayer[brushTile] = 8;
                this->Logic2Layer[brushTile] &= 0xf3;
            } else if (mapper == 1) {
                // mapper max, bug:fixme: is 156 really the maximum height?
                this->HeightLayer[brushTile] = 156;
                this->LogicLayer[brushTile] |= 0x8000;
            } else if (mapper == 5) {
                this->HeightLayer[brushTile] = 100;
            } else if (mapper == 2) {
                // scale towards the brush average, in eighths of the ratio to it
                int ratio = 100;
                if (average != 0) {
                    ratio = *(byte volatile*)&this->HeightLayer[brushTile] * 100 / average;
                }
                ratio = (ratio / 8 + 100) * *(byte volatile*)&this->HeightLayer[brushTile] / 100;
                if (ratio > 156) {
                    ratio = 156;
                }
                this->HeightLayer[brushTile] = (byte)ratio;
            }

            if ((this->LogicLayer[brushTile] & L_ROCKY) != 0) {
                int const organism = this->OrganismLayer[brushTile];
                if (organism >= 2000) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(
                        organism - 2000);
                }
            }
            this->LogicLayer[brushTile] &= ~L_ROCKY;
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
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
    }

}
}
