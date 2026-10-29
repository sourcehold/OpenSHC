#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9000
    void TileMapState::reassignWallOwnershipForPlayer(int playerID, int newOwner)
    {
        for (int tileUnk = 0; tileUnk < 80400; tileUnk += 6) {
            if ((this->LogicLayer[tileUnk + 0] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tileUnk + 0];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tileUnk + 0] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 0] = this->WallOwnerLayer[tileUnk + 0] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 1] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tileUnk + 1];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tileUnk + 1] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 1] = this->WallOwnerLayer[tileUnk + 1] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 2] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tileUnk + 2];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tileUnk + 2] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 2] = this->WallOwnerLayer[tileUnk + 2] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 3] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tileUnk + 3];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tileUnk + 3] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 3] = this->WallOwnerLayer[tileUnk + 3] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 4] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tileUnk + 4];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tileUnk + 4] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 4] = this->WallOwnerLayer[tileUnk + 4] & 0xf8 | (char)newOwner - 1U;
                }
            }
            if ((this->LogicLayer[tileUnk + 5] & L_WALL_OR_GATEHOUSE) != 0) {
                int building = this->BuildingLayer[tileUnk + 5];
                if (building != 0 ? DAT_BuildingsState::instance.buildings[building].owner == newOwner
                                  : (this->WallOwnerLayer[tileUnk + 5] & 7) + 1 == playerID) {
                    this->WallOwnerLayer[tileUnk + 5] = this->WallOwnerLayer[tileUnk + 5] & 0xf8 | (char)newOwner - 1U;
                }
            }
        }
    }

}
}
