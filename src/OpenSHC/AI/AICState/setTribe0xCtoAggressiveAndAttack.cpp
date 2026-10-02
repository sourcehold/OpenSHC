#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF400
    void AICState::setTribe0xCtoAggressiveAndAttack(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return;
        }

        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[12];
        if (tribeID == 0) {
            return;
        }
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[12]) {
            return;
        }
        if (DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID == 0) {
            return;
        }

        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
            tribeID, Map::Units::STBT_0x3f2);
    }
}
}
