#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2730
    void AICState::addUnitToSmallestPatrolTribe(int unitID)
    {
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        int aiType = DAT_GameState::instance.playerDataArray[owner].aiType;
        if (aiType == AITA_NULL)
            return;

        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 4;
        int tribeID = MACRO_CALL_MEMBER(AICState_Func::getSmallestPatrolTribe, this)(
            owner, this->aics[aiType - 1].OuterPatrolGroupsCount);
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
    }
}
}
