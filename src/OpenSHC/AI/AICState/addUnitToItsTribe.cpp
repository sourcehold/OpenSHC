#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D27E0
    void AICState::addUnitToItsTribe(int unitID, int aiUnitBehaviourType)
    {
        int iVar1 = (int)DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_GameState::instance.playerDataArray[iVar1].aiType != AITA_NULL) {
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = (short)aiUnitBehaviourType;
            iVar1 = MACRO_CALL_MEMBER(AICState_Func::addUnitToSmallestBehaviourTypeTribe, this)(iVar1, unitID, aiUnitBehaviourType);
            if (iVar1 != 0) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, iVar1);
            }
        }
    }
}
}
