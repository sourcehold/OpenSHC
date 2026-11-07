#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F9220
    void TileMapState::swapWallOwnership(int playerID, int otherPlayerID)
    {
        for (int tileUnk = 0; tileUnk < MC_MAP_TILES_COUNT; tileUnk += 6) {
            if ((this->LogicLayer[tileUnk + 0] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tileUnk + 0] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 0]
                        = this->WallOwnerLayer[tileUnk + 0] & ~7 | (char)otherPlayerID - 1U;
                } else if ((this->WallOwnerLayer[tileUnk + 0] & 7) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tileUnk + 0] = this->WallOwnerLayer[tileUnk + 0] & ~7 | (char)playerID - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 1] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tileUnk + 1] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 1]
                        = this->WallOwnerLayer[tileUnk + 1] & ~7 | (char)otherPlayerID - 1U;
                } else if ((this->WallOwnerLayer[tileUnk + 1] & 7) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tileUnk + 1] = this->WallOwnerLayer[tileUnk + 1] & ~7 | (char)playerID - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 2] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tileUnk + 2] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 2]
                        = this->WallOwnerLayer[tileUnk + 2] & ~7 | (char)otherPlayerID - 1U;
                } else if ((this->WallOwnerLayer[tileUnk + 2] & 7) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tileUnk + 2] = this->WallOwnerLayer[tileUnk + 2] & ~7 | (char)playerID - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 3] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tileUnk + 3] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 3]
                        = this->WallOwnerLayer[tileUnk + 3] & ~7 | (char)otherPlayerID - 1U;
                } else if ((this->WallOwnerLayer[tileUnk + 3] & 7) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tileUnk + 3] = this->WallOwnerLayer[tileUnk + 3] & ~7 | (char)playerID - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 4] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tileUnk + 4] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 4]
                        = this->WallOwnerLayer[tileUnk + 4] & ~7 | (char)otherPlayerID - 1U;
                } else if ((this->WallOwnerLayer[tileUnk + 4] & 7) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tileUnk + 4] = this->WallOwnerLayer[tileUnk + 4] & ~7 | (char)playerID - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 5] & L_WALL_OR_GATEHOUSE) != 0) {
                if ((this->WallOwnerLayer[tileUnk + 5] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 5]
                        = this->WallOwnerLayer[tileUnk + 5] & ~7 | (char)otherPlayerID - 1U;
                } else if ((this->WallOwnerLayer[tileUnk + 5] & 7) + 1 == otherPlayerID) {
                    this->WallOwnerLayer[tileUnk + 5] = this->WallOwnerLayer[tileUnk + 5] & ~7 | (char)playerID - 1U;
                }
            }
        }
    }

}
}
