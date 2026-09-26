#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF660
    void AICState::aiCommandWallAssaultTribes(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL)
            return;

        for (int i = 0; i < 2; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[190 + i];
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[i + 190])
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID == 0)
                continue;

            DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                tribeID, Map::Units::STBT_0x3f2);
        }
    }
}
}
