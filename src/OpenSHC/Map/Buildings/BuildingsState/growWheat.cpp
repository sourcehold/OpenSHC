#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CC30
        void BuildingsState::growWheat(int buildingID)
        {
            // The damage layer holds the growth stage of the wheat on the field tiles.
            // Not all stage counters are used, the compiler removes those.
            int empty = 0;
            int seeded = 0;
            int stage2To4 = 0;
            int stage5To7 = 0;
            int stage8To10 = 0;
            int growing = 0;
            int stage101 = 0;
            int stage102 = 0;
            int stage103To119 = 0;
            int stage120 = 0;
            int stage121 = 0;
            for (int i = 0; i < 36; ++i) {
                int tile = (&this->buildings[buildingID].tileRef1)[i];
                if ((char)DAT_TileMapState::instance.DamageLayer[tile] >= 2
                    && (char)DAT_TileMapState::instance.DamageLayer[tile] < 103) {
                    ++DAT_TileMapState::instance.DamageLayer[tile];
                }
                char stage = DAT_TileMapState::instance.DamageLayer[tile];
                if (stage < 1) {
                    ++empty;
                } else if (stage < 2) {
                    ++seeded;
                } else if (stage < 5) {
                    ++stage2To4;
                } else if (stage < 8) {
                    ++stage5To7;
                } else if (stage < 11) {
                    ++stage8To10;
                } else if (stage < 101) {
                    ++growing;
                } else if (stage < 102) {
                    ++stage101;
                } else if (stage < 103) {
                    ++stage102;
                } else if (stage < 120) {
                    ++stage103To119;
                } else if (stage == 120) {
                    ++stage120;
                } else if (stage == 121) {
                    ++stage121;
                }
            }

            if (stage121 >= 4) {
                *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 8;
                return;
            }
            if (growing >= 12 || (growing != 0 && stage120 != 0)) {
                *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 6;
                return;
            }
            if (stage121 != 0) {
                *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 8;
                return;
            }
            if (empty == 0) {
                if (stage120 != 0) {
                    *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 3;
                    return;
                }
                if (stage102 != 0) {
                    *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 3;
                    return;
                }
                if (stage103To119 != 0) {
                    *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 3;
                    return;
                }
                *(short*)&this->buildings[buildingID].wheatGrowStateRelated = seeded != 0 ? 5 : 2;
                return;
            }
            *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 3;
        }

    }
}
}
