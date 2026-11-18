#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/WallOwner.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
    using OpenSHC::Map::LogicHelpers::WO_OWNER_MASK;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9220
    void TileMapState::swapWallOwnership(int playerID, int otherPlayerID)
    {
        for (int tile = 0; tile < countof(this->LogicLayer); tile++) {
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tile] & WO_OWNER_MASK) + 1 == playerID) {
                    this->WallOwnerLayer[tile] = (this->WallOwnerLayer[tile] & ~WO_OWNER_MASK) | (otherPlayerID - 1);
                } else if ((this->WallOwnerLayer[tile] & WO_OWNER_MASK) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tile] = (this->WallOwnerLayer[tile] & ~WO_OWNER_MASK) | (playerID - 1);
                }
            }
        }
    }

}
}
