#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB90
        BOOLEnum BuildingsState::isFarmTileReadyForWheatStageChange(int buildingID)
        {
            for (int tileIndex = 0; tileIndex < 36; ++tileIndex) {
                int const tile = this->buildings[buildingID].tileRefs[tileIndex];
                int const damage = (char)DAT_TileMapState::instance.DamageLayer[tile];
                DAT_BuildingsState::instance.farmerDestinationTile = tile;
                if (this->buildings[buildingID].farmGrowState == 6) {
                    if (damage >= 11 && damage < 101) {
                        return TRUE;
                    }
                } else if (this->buildings[buildingID].farmGrowState == 8) {
                    if (damage == 121) {
                        return TRUE;
                    }
                } else if (this->buildings[buildingID].farmGrowState == 3) {
                    if (damage == 0 || damage == 120) {
                        return TRUE;
                    }
                    if (damage >= 101 && damage < 120) {
                        return TRUE;
                    }
                } else if (this->buildings[buildingID].farmGrowState == 5) {
                    if (damage >= 1 && damage < 2) {
                        return TRUE;
                    }
                } else {
                    return FALSE;
                }
            }
            return FALSE;
        }

    }
}
}
