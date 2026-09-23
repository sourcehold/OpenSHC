#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4040
    void AICState::addEngineersToTribe(int playerID)
    {
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState != Map::Units::ULS_NORMAL)
                continue;
            if (DAT_UnitsState::instance.units[unitID].owner != playerID)
                continue;
            if (DAT_UnitsState::instance.units[unitID].dying != 0)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unitType != Map::Units::UT_E_ENGINEER)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 10)
                continue;
            if (DAT_UnitsState::instance.units[unitID].tribeID != 0)
                continue;

            MACRO_CALL_MEMBER(AICState_Func::addUnitToItsTribe, this)(unitID, 10);
        }
    }

}
}
