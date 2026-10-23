#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB90
        BOOLEnum BuildingsState::isFarmTileReadyForWheatStageChange(int param_1)
        {
            // The damage layer holds the growth stage of the wheat on the field tiles
            for (int i = 0; i < 36; ++i) {
                int tile = (&this->buildings[param_1].tileRefs[0])[i];
                int stage = (char)DAT_TileMapState::instance.DamageLayer[tile];
                DAT_BuildingsState::instance.farmerDestinationTile = tile;
                if (*(short*)&this->buildings[param_1].farmGrowState == 6) {
                    if (stage >= 11 && stage < 101) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].farmGrowState == 8) {
                    if (stage == 121) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].farmGrowState == 3) {
                    if (stage == 0 || stage == 120 || (stage >= 101 && stage < 120)) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].farmGrowState == 5) {
                    if (stage >= 1 && stage < 2) {
                        return 1;
                    }
                }
            }
            return 0;
        }

    }
}
}
