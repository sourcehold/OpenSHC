#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537A00
        int UnitsState::findNearestIdleCowForPlayer(int playerID, int x, int y)
        {
            int _bestDistance = 10000;
            int _bestUnitID = 0;
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].owner != playerID) {
                    continue;
                }
                if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_COW) {
                    continue;
                }
                if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(x, y, this->units[unitID].x, this->units[unitID].y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < _bestDistance) {
                    _bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    _bestUnitID = unitID;
                }
            }
            return _bestUnitID;
        }

    }
}
}
