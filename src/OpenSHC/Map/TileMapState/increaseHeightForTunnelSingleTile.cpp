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
    // FUNCTION: STRONGHOLDCRUSADER 0x004F80E0
    void TileMapState::increaseHeightForTunnelSingleTile(int tile, uint x, uint y, int increment)
    {
        if ((this->LogicLayer[tile]
                & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_RIVER | L_FORD | L_KEEP_NON_MANOR_HOUSE | L_MARSH | L_MOAT))
            != 0) {
            return;
        }
        if ((this->LogicLayer[tile] & (L_SEA | L_BORDER | L_BORDER_EDGE | L_ROCKY)) != 0) {
            return;
        }
        if (this->BuildingLayer[tile] != 0) {
            return;
        }

        if ((this->HeightLayer[tile] < 16 || this->DefaultHeightLayer[tile] < 16)
            && (int)((uint)this->HeightLayer[tile] + increment) >= 0) {
            this->HeightLayer[tile] = this->HeightLayer[tile] + (char)increment;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(4, x, y);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(y, tile);
    }

}
}
