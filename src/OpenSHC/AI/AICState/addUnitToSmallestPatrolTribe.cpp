#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2730
    void AICState::addUnitToSmallestPatrolTribe(int unitID)
    {
        int iVar1 = (int)DAT_UnitsState::instance.units[unitID].owner;
        int _aiType = DAT_GameState::instance.playerDataArray[iVar1].aiType;
        if (_aiType != AITA_NULL) {
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 4;
            iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getSmallestPatrolTribe, DAT_TribesState::ptr)(
                iVar1, (int)this->aics[_aiType - 1].OuterPatrolGroupsCount);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, iVar1);
        }
    }
}
}
