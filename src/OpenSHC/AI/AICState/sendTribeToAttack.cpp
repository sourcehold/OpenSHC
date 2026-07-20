#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF750
    void AICState::sendTribeToAttack(int playerID)
    {
        int tribeID;
        if ((DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL)
            && (tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xbd], tribeID != 0)) {
            if ((DAT_TribesState::instance.tribes[tribeID].uid
                    == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xbd])
                && (DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID != 0)) {
                DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                    tribeID, Map::Units::STBT_0x3fb);
            }
        }
    }
}
}
