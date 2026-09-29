#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8900
    BOOLEnum TileMapState::hasOnlyTowerNeighborsNoWalls(int tile, int y)
    {
        int unknownWallRelated = 0;
        int wallOrGatehouse = 0;
        if ((this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[this->directionTranslationMatrix[y][0] + tile] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[this->directionTranslationMatrix[y][2] + tile] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[this->directionTranslationMatrix[y][4] + tile] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        if ((this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & L_UNKNOWN_WALL_RELATED) != 0) {
            unknownWallRelated++;
        } else if ((this->LogicLayer[this->directionTranslationMatrix[y][6] + tile] & L_WALL_OR_GATEHOUSE) != 0) {
            wallOrGatehouse++;
        }
        if (unknownWallRelated != 0 && wallOrGatehouse == 0) {
            return TRUE;
        }
        return FALSE;
    }

}
}
