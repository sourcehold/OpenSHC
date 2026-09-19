#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4040
    void AICState::addEngineersToTribe(int playerID)
    {
        int _unitID = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            Map::Units::Unit* _pUnit = &DAT_UnitsState::instance.units[1];
            do {
                /* if logicalState == normal && owner == playerID && unitType == 0x1e (engineer)
                   && aiUnitBehaviourType == 10 */
                if ((((_pUnit->logicalState == Map::Units::ULS_NORMAL) && (_pUnit->owner == playerID))
                        && (_pUnit->dying == 0))
                    && (((_pUnit->unitType == Map::Units::UT_E_ENGINEER) && (_pUnit->aiUnitBehaviourType == 10))
                        && (_pUnit->tribeID == 0))) {
                    MACRO_CALL_MEMBER(AICState_Func::addUnitToItsTribe, this)(_unitID, 10);
                }
                _unitID = _unitID + 1;
                _pUnit = _pUnit + 1;
            } while (_unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
    }

}
}
