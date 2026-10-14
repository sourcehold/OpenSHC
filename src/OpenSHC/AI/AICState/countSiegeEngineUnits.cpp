#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFBC0
    int AICState::countSiegeEngineUnits(int playerID)
    {
        int count = 0;
        for (int unitID = 1; unitID < 2500; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE)
                continue;
            if (DAT_UnitsState::instance.units[unitID].owner != playerID)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unknownSiegeTentRelated02 != 3)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType == 21)
                continue;

            if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                || DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET
                || DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_TOWER
                || DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM
                || DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA)
                count++;
        }
        return count;
    }

}
}
