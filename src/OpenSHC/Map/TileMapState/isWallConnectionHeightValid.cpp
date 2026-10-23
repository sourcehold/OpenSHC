#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8840
    BOOLEnum TileMapState::isWallConnectionHeightValid(int tile, int y, int param_3)
    {
        int tileHeight = this->HeightLayer[tile];
        int firstDirection = 0;
        int secondDirection = 0;
        if (param_3 == 0) {
            secondDirection = 4;
        } else if (param_3 == 2) {
            firstDirection = 2;
            secondDirection = 6;
        } else if (param_3 == 4) {
            secondDirection = param_3;
        } else if (param_3 == 6) {
            firstDirection = 2;
            secondDirection = 6;
        }

        int first = this->directionTranslationMatrix[y][firstDirection] + tile;
        if ((this->LogicLayer[first] & L_WALL_OR_GATEHOUSE) == 0) {
            return FALSE;
        }
        if ((this->LogicLayer[first] & L_STOCKPILEUnk) != 0) {
            return FALSE;
        }
        int minHeight = tileHeight - 0x10;
        if (this->HeightLayer[first] < minHeight && this->DamageLayer[first] == 0) {
            return FALSE;
        }

        int second = this->directionTranslationMatrix[y][secondDirection] + tile;
        if ((this->LogicLayer[second] & L_WALL_OR_GATEHOUSE) == 0) {
            return FALSE;
        }
        if ((this->LogicLayer[second] & L_STOCKPILEUnk) != 0) {
            return FALSE;
        }
        if (this->HeightLayer[second] < minHeight && this->DamageLayer[second] == 0) {
            return FALSE;
        }
        return TRUE;
    }

}
}
