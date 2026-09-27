#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537E00
        void UnitsState::setTowerSiegeEngineToIdle(int buildingID)
        {
            UnitTypeShort _siegeEngineType;
            if (DAT_BuildingsState::instance.buildings[buildingID].containsSiegeMangonel1OrBallista2 == 1) {
                _siegeEngineType = OpenSHC::Map::Units::UT_S_MANGONEL;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].containsSiegeMangonel1OrBallista2 == 2) {
                _siegeEngineType = OpenSHC::Map::Units::UT_S_BALLISTA;
            } else {
                return;
            }
            for (int unitID = 0; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[unitID].dying == 0 && this->units[unitID].unitType == _siegeEngineType
                    && DAT_TileMapState::instance.BuildingLayer[this->units[unitID].tile] == buildingID) {
                    this->units[unitID].state.generic
                        = (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk);
                    return;
                }
            }
        }

    }
}
}
