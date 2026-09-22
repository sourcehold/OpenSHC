#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D27E0
    void AICState::addUnitToItsTribe(int unitID, int aiUnitBehaviourType)
    {
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_GameState::instance.playerDataArray[owner].aiType == AITA_NULL)
            return;

        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = aiUnitBehaviourType;
        int tribeID
            = MACRO_CALL_MEMBER(AICState_Func::addUnitToSmallestBehaviourTypeTribe, this)(owner, unitID, aiUnitBehaviourType);
        if (tribeID != 0)
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
    }
}
}
