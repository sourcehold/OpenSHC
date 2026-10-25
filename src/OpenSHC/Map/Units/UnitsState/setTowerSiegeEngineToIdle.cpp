#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Buildings/Enums/DefensiveTowerEngineType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00537E00
        void UnitsState::setTowerSiegeEngineToIdle(int buildingID)
        {
            /* the original writes the search out once per siege engine type */
            switch (DAT_BuildingsState::instance.buildings[buildingID].defensiveTowerEngineType) {
            case Buildings::Enums::DTET_MANGONEL:
                for (int unitID = 0; unitID < this->maxUnitCount; ++unitID) {
                    if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                        && !this->units[unitID].dying
                        && this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_MANGONEL
                        && DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile] == buildingID) {
                        this->units[unitID].state.generic
                            = (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk);
                        return;
                    }
                }
                break;
            case Buildings::Enums::DTET_BALLISTA:
                for (int unitID = 0; unitID < this->maxUnitCount; ++unitID) {
                    if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                        && !this->units[unitID].dying
                        && this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA
                        && DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile] == buildingID) {
                        this->units[unitID].state.generic
                            = (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk);
                        return;
                    }
                }
                break;
            }
        }

    }
}
}
