#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005302B0
        void UnitsState::killAllUnownedUnits()
        {
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[unitID].dying == 0 && this->units[unitID].owner == 0
                    && this->units[unitID].isStalked != 0) {
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].dying = 1;
                }
            }
        }

    }
}
}
