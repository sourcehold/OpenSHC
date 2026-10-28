#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D40B0
    void AICState::aiReassignTunnelersToTribe(int playerID)
    {
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState != Map::Units::ULS_NORMAL)
                continue;
            if (DAT_UnitsState::instance.units[unitID].owner != playerID)
                continue;
            if (DAT_UnitsState::instance.units[unitID].dying != 0)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unitType != Map::Units::UT_TUNNELER)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 15)
                continue;

            if (DAT_UnitsState::instance.units[unitID].tribeID != 0)
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].tribeID);
            MACRO_CALL_MEMBER(AICState_Func::addUnitToItsTribe, this)(unitID, 15);
        }
    }
}
}
