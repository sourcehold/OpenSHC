#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CB90
        undefined4 BuildingsState::isFarmTileReadyForWheatStageChange(int param_1)
        {
            // The damage layer holds the growth stage of the wheat on the field tiles
            for (int i = 0; i < 36; ++i) {
                DAT_BuildingsState::instance.farmerDestinationTile = (&this->buildings[param_1].tileRef1)[i];
                int stage
                    = (char)DAT_TileMapState::instance.DamageLayer[DAT_BuildingsState::instance.farmerDestinationTile];
                if (*(short*)&this->buildings[param_1].wheatGrowStateRelated == 6) {
                    if (stage >= 11 && stage < 101) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].wheatGrowStateRelated == 8) {
                    if (stage == 121) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].wheatGrowStateRelated == 3) {
                    if (stage == 0 || stage == 120 || (stage >= 101 && stage < 120)) {
                        return 1;
                    }
                } else if (*(short*)&this->buildings[param_1].wheatGrowStateRelated == 5) {
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
