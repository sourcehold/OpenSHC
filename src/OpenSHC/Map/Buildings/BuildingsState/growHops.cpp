#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EBF0
        void BuildingsState::growHops(int buildingID)
        {
            // The damage layer holds the growth stage of the hops on the field tiles
            int empty = 0;
            int young = 0;
            int growing = 0;
            int grown = 0;
            int ripe = 0;
            for (int i = 0; i < 24; ++i) {
                int tile = (&this->buildings[buildingID].tileRef1)[i];
                if ((char)DAT_TileMapState::instance.DamageLayer[tile] >= 2) {
                    if ((char)DAT_TileMapState::instance.DamageLayer[tile] > 84) {
                        DAT_TileMapState::instance.DamageLayer[tile] = 0;
                    } else if ((char)DAT_TileMapState::instance.DamageLayer[tile] < 80
                        && (char)DAT_TileMapState::instance.DamageLayer[tile] >= 32) {
                        DAT_TileMapState::instance.DamageLayer[tile] = 0;
                    } else {
                        ++DAT_TileMapState::instance.DamageLayer[tile];
                    }
                }
                char stage = DAT_TileMapState::instance.DamageLayer[tile];
                if (stage < 2) {
                    ++empty;
                } else if (stage < 14) {
                    ++young;
                } else if (stage < 28) {
                    ++growing;
                } else if (stage <= 80) {
                    ++grown;
                } else {
                    ++ripe;
                }
            }

            if (growing >= 6) {
                *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 5;
                return;
            }
            if (growing != 0 && ripe != 0) {
                *(short*)&this->buildings[buildingID].wheatGrowStateRelated = 5;
                return;
            }
            *(short*)&this->buildings[buildingID].wheatGrowStateRelated = empty != 0 ? 3 : 2;
        }

    }
}
}
