
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00501CD0
    void TileMapState::increaseHeightForTunnelWithBrush(int tile, uint x, uint y, int increment)
    {
        int baseTile = tile;
        uint baseY = y;
        for (int index = 0; index < 9; index++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                0, index, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
                continue;
            }
            if (this->BuildingLayer[tile] != 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & (L_SEA | L_BORDER | L_BORDER_EDGE | L_ROCKY)) != 0) {
                continue;
            }
            if ((this->LogicLayer[tile] & (L_RIVER | L_FORD | L_MARSH | L_MOAT)) != 0) {
                continue;
            }

            if ((this->HeightLayer[tile] < 0x10 || this->DefaultHeightLayer[tile] < 0x10)
                && (int)((uint)this->HeightLayer[tile] + increment) >= 0) {
                this->HeightLayer[tile] = this->HeightLayer[tile] + (char)increment;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(y, tile);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(5, x, y);
    }

}
}
