#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500370
    BOOLEnum TileMapState::findTileInSameAreaAndNoTooHeightDifference(int area, int tile, int yUnk)
    {
        for (int attempts = 0; attempts < 8; attempts++) {
            int neighbour = this->directionTranslationMatrix[yUnk][attempts] + tile;
            if (this->HeightLayer[neighbour] > this->HeightLayer[tile] + 0x10) {
                continue;
            }
            if ((short)this->PathConnectionLayer[neighbour] != area) {
                continue;
            }
            return TRUE;
        }
        return FALSE;
    }

}
}
