#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/WallOwner.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
    using OpenSHC::Map::LogicHelpers::WO_OWNER_MASK;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9000
    void TileMapState::reassignWallOwnershipForPlayer(int playerID, int newOwner)
    {
        for (int tile = 0; tile < countof(this->LogicLayer); ++tile) {
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
                continue;
            }
            int const building = this->BuildingLayer[tile];
            if (building != 0) {
                if (DAT_BuildingsState::instance.buildings[building].owner != newOwner) {
                    continue;
                }
            } else if ((this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                continue;
            }
            this->WallOwnerLayer[tile] = (this->WallOwnerLayer[tile] & ~WO_OWNER_MASK) | (newOwner - 1);
        }
    }

}
}
