#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EF40
        void BuildingsState::harmHopFarmsOfPlayer(int param_1)
        {
            for (int buildingID = 0; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0 && this->buildings[buildingID].owner == param_1
                    && this->buildings[buildingID].buildingType == BT_HOPFARM) {
                    // tileRef1 .. tileRef36 are consecutive fields in the generated header
                    for (int tileIndex = 0; tileIndex != 24; ++tileIndex) {
                        int const tile = (&this->buildings[buildingID].tileRef1)[tileIndex];
                        DAT_TileMapState::instance.DamageLayer[tile]
                            = (char)DAT_TileMapState::instance.DamageLayer[tile] < 6 ? 0 : 28;
                    }
                    this->buildings[buildingID].growCounter = -1800;
                    this->buildings[buildingID].wheatGrowStateRelated = 2;
                }
            }
        }

    }
}
}
