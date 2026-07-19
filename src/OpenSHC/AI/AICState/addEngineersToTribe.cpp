#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4040
    void AICState::addEngineersToTribe(int playerID)
    {
        int unitID;

        unitID = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            /* Unit offset 150 */
            Map::Units::Unit* psVar1 = &DAT_UnitsState::instance.units[1];
            do {
                /* if logicalState == normal && owner == playerID && unitType == 0x1e (engineer)
                   && aiUnitBehaviourType == 10 */
                if ((((psVar1->logicalState == Map::Units::ULS_NORMAL) && (psVar1->owner == playerID))
                        && (psVar1->dying == 0))
                    && (((psVar1->unitType == Map::Units::UT_E_ENGINEER) && (psVar1->aiUnitBehaviourType == 10))
                        && (psVar1->tribeID == 0))) {
                    MACRO_CALL_MEMBER(AICState_Func::addUnitToItsTribe, this)(unitID, 10);
                }
                unitID = unitID + 1;
                psVar1 = psVar1 + 1;
            } while (unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
    }

}
}
