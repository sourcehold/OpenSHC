#include "../TileMapState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8900
    BOOLEnum TileMapState::hasOnlyTowerNeighborsNoWalls(int tile, int y)
    {
        int unknownWallRelated = 0;
        int wallOrGatehouse = 0;
        int offset = this->directionTranslationMatrix[y][0] + tile;
        if ((this->LogicLayer[offset] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        offset = this->directionTranslationMatrix[y][2] + tile;
        if ((this->LogicLayer[offset] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        offset = this->directionTranslationMatrix[y][4] + tile;
        if ((this->LogicLayer[offset] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        offset = this->directionTranslationMatrix[y][6] + tile;
        if ((this->LogicLayer[offset] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[offset] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        if (unknownWallRelated != 0 && wallOrGatehouse == 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
