#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D090
        void BuildingsState::harmWheatFarmsOfPlayer(int playerID)
        {
            for (int buildingID = 0; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0 && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == BT_WHEATFARM) {
                    for (int tileIndex = 0; tileIndex != 36; ++tileIndex) {
                        int const tile = this->buildings[buildingID].tileRefs[tileIndex];
                        DAT_TileMapState::instance.DamageLayer[tile]
                            = (char)DAT_TileMapState::instance.DamageLayer[tile] < 8 ? 0 : 101;
                    }
                    this->buildings[buildingID].growCounter = -1200;
                    this->buildings[buildingID].farmGrowState = 2;
                }
            }
        }

    }
}
}
