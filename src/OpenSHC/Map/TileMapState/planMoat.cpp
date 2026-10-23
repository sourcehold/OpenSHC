
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00514480
    void TileMapState::planMoat(undefined4 playerID, int tile, uint tileY)
    {
        uint logic = this->LogicLayer[tile];
        if ((logic & (L_BORDER | L_BORDER_EDGE)) != 0) {
            return;
        }
        if (this->OrganismLayer[tile] != 0) {
            return;
        }
        if ((logic & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            return;
        }
        if (this->BuildingLayer[tile] != 0) {
            return;
        }
        if ((logic & (L_WALL_OR_GATEHOUSE | L_BOULDERS | L_IRON | L_RIVER | L_FORD | L_MARSH)) != 0) {
            return;
        }
        if ((logic & (L_SEA | L_PLAIN1_AND_FARM | L_ROCKY)) != 0) {
            return;
        }

        int moatX = tile - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
        if ((logic & (L_MOAT_DUG_OR_PLANNED | L_MOAT)) == 0 && this->HeightLayer[tile] <= 0xc) {
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createMoatData, this)(playerID, moatX, tileY, 0) != 0) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_MOAT_DUG_OR_PLANNED;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(tileY, tile);
        }
    }

}
}
