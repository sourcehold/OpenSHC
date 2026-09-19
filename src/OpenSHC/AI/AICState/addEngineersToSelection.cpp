#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC680
    int AICState::addEngineersToSelection(int playerID, int unitCount)
    {
        int tribeID;
        uint unitID;

        tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
        unitID = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            /* Unit offset 150 */
            Map::Units::Unit* _ptrUnit = &DAT_UnitsState::instance.units[1];
            do {
                if (unitCount <= 0) {
                    return tribeID;
                }
                if ((((_ptrUnit->logicalState == Map::Units::ULS_NORMAL) && (_ptrUnit->owner == playerID))
                        && (_ptrUnit->dying == 0))
                    && (((_ptrUnit->unitType == Map::Units::UT_E_ENGINEER) && (_ptrUnit->aiUnitBehaviourType == 10))
                        && ((_ptrUnit->tribeID == 0)
                            && ((_ptrUnit->state).generic != Map::Units::States::US_STAND_UPUnk)))) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                        unitID, tribeID);
                    unitCount = unitCount + -1;
                }
                unitID = unitID + 1;
                _ptrUnit = _ptrUnit + 1;
            } while ((int)unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
        return tribeID;
    }

}
}
