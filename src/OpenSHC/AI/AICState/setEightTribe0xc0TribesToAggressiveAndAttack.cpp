#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF5E0
    void AICState::setEightTribe0xc0TribesToAggressiveAndAttack(int playerID)
    {
        int _tribeID;
        int iVar1;
        short* psVar2;
        if (DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL) {
            iVar1 = 0;
            psVar2 = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 0xc0;
            do {
                _tribeID = (int)*psVar2;
                if (((_tribeID != 0) &&
                    (DAT_TribesState::instance.tribes[_tribeID].uid == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[iVar1 + 0xc0])) &&
                    (DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID != 0)) {
                    DAT_TribesState::instance.tribes[_tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(_tribeID, Map::Units::STBT_0x3f2);
                }
                iVar1 = iVar1 + 1;
                psVar2 = psVar2 + 1;
            } while (iVar1 < 8);
        }
    }
}
}
