#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC680
    int AICState::addEngineersToSelection(int playerID, int unitCount)
    {
        int tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (unitCount <= 0)
                return tribeID;
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
            if (DAT_UnitsState::instance.units[unitID].state.generic == Map::Units::States::US_STAND_UPUnk)
                continue;

            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
            unitCount--;
        }
        return tribeID;
    }

}
}
