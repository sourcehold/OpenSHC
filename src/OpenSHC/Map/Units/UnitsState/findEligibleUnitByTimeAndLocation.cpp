#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005345A0
        int UnitsState::findEligibleUnitByTimeAndLocation(
            int unitID, int playerID, int unitXPosition, int unitYPosition, int zero1, int zero2)
        {
            int _bestUnitID = 0;
            int _bestScore = 0;
            for (int _candidateUnitID = 1; _candidateUnitID < (int)this->maxUnitCount; ++_candidateUnitID) {
                if (this->units[_candidateUnitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[_candidateUnitID].dying != 0) {
                    continue;
                }
                if (this->units[_candidateUnitID].owner != playerID) {
                    continue;
                }
                if (DAT_UnitPropertiesDefinedData::instance.SomeUnitStatMatrix5[this->units[_candidateUnitID].unitType]
                    != 0) {
                    continue;
                }
                if (_candidateUnitID == unitID) {
                    continue;
                }
                if (zero2 == 1 || zero2 == 10) {
                    if (this->units[_candidateUnitID].field131_0x2ac != (short)zero2) {
                        continue;
                    }
                }
                /* DAT_MatchTime - SEC_Units[_candidateUnitID].someMatchTimeVariable */
                int _score
                    = (DAT_GameCore::instance.mapTimeInTicks - this->units[_candidateUnitID].someMatchTimeVariable)
                    >> 5;
                if (zero1 != 0) {
                    int _distance = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(
                        unitXPosition, unitYPosition, this->units[_candidateUnitID].x, this->units[_candidateUnitID].y);
                    /* this formula means divide by 4 and round it up. */
                    _score = _score - ((_distance + (_distance >> 0x1f & 3U)) >> 2);
                }
                if (_bestScore < _score) {
                    _bestScore = _score;
                    _bestUnitID = _candidateUnitID;
                }
            }
            if (_bestUnitID == 0) {
                return 0;
            }
            this->units[_bestUnitID].someMatchTimeVariable = DAT_GameCore::instance.mapTimeInTicks;
            return _bestUnitID;
        }

    }
}
}
