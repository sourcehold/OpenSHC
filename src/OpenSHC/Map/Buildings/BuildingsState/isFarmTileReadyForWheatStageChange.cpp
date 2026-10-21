#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB90
        undefined4 BuildingsState::isFarmTileReadyForWheatStageChange(int buildingID)
        {
            // tileRef1 .. tileRef36 are consecutive fields in the generated header
            for (int tileIndex = 0; tileIndex < 36; ++tileIndex) {
                int const tile = (&this->buildings[buildingID].tileRef1)[tileIndex];
                int const damage = (char)DAT_TileMapState::instance.DamageLayer[tile];
                DAT_BuildingsState::instance.farmerDestinationTile = tile;
                if (this->buildings[buildingID].wheatGrowStateRelated == 6) {
                    if (damage >= 11 && damage < 101) {
                        return 1;
                    }
                } else if (this->buildings[buildingID].wheatGrowStateRelated == 8) {
                    if (damage == 121) {
                        return 1;
                    }
                } else if (this->buildings[buildingID].wheatGrowStateRelated == 3) {
                    if (damage == 0 || damage == 120) {
                        return 1;
                    }
                    if (damage >= 101 && damage < 120) {
                        return 1;
                    }
                } else if (this->buildings[buildingID].wheatGrowStateRelated == 5) {
                    if (damage >= 1 && damage < 2) {
                        return 1;
                    }
                } else {
                    return 0;
                }
            }
            return 0;
        }

    }
}
}
