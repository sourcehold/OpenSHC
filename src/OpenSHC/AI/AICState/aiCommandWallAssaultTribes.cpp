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
    void AICState::aiCommandWallAssaultTribes(int param_1)
    {
        int tribeID;
        int iVar1;
        short* psVar2;
        if (DAT_GameState::instance.playerDataArray[param_1].aiType != AITA_NULL) {
            iVar1 = 0;
            psVar2 = DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs + 0xbe;
            do {
                tribeID = (int)*psVar2;
                if (((tribeID != 0)
                        && (DAT_TribesState::instance.tribes[tribeID].uid
                            == DAT_GameState::instance.playerDataArray[param_1].aiTribeUIDs[iVar1 + 0xbe]))
                    && (DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID != 0)) {
                    DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, Map::Units::STBT_0x3f2);
                }
                iVar1 = iVar1 + 1;
                psVar2 = psVar2 + 1;
            } while (iVar1 < 2);
        }
    }
}
}
