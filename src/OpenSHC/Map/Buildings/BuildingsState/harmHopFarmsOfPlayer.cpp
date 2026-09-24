#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EF40
        void BuildingsState::harmHopFarmsOfPlayer(int param_1)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].owner != param_1
                    || this->buildings[i].buildingType != BT_HOPFARM) {
                    continue;
                }
                // Young hops are destroyed, grown hops are set back
                for (int t = 0; t < 24; ++t) {
                    int tile = (&this->buildings[i].tileRef1)[t];
                    if ((char)DAT_TileMapState::instance.DamageLayer[tile] < 6) {
                        DAT_TileMapState::instance.DamageLayer[tile] = 0;
                    } else {
                        DAT_TileMapState::instance.DamageLayer[tile] = 28;
                    }
                }
                this->buildings[i].growCounter = -1800;
                *(short*)&this->buildings[i].wheatGrowStateRelated = 2;
            }
        }

    }
}
}
