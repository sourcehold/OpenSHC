#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D090
        void BuildingsState::harmWheatFarmsOfPlayer(int playerID)
        {
            for (int i = 0; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].owner != playerID
                    || this->buildings[i].buildingType != BT_WHEATFARM) {
                    continue;
                }
                // Young wheat is destroyed, grown wheat is set back
                for (int t = 0; t < 36; ++t) {
                    int tile = (&this->buildings[i].tileRef1)[t];
                    if ((char)DAT_TileMapState::instance.DamageLayer[tile] < 8) {
                        DAT_TileMapState::instance.DamageLayer[tile] = 0;
                    } else {
                        DAT_TileMapState::instance.DamageLayer[tile] = 101;
                    }
                }
                this->buildings[i].growCounter = -1200;
                *(short*)&this->buildings[i].wheatGrowStateRelated = 2;
            }
        }

    }
}
}
