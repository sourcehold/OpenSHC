#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF470
    void AICState::aiCommandTribe11StandGroundToGate(int playerID)
    {
        int iVar1;
        int iVar2;
        if ((((DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL)
                 && (iVar2 = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xb], iVar2 != 0))
                && (DAT_TribesState::instance.tribes[iVar2].uid
                    == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xb]))
            && (DAT_TribesState::instance.tribes[iVar2].selectionTargetUnitID != 0)) {
            DAT_TribesState::instance.tribes[iVar2].unitStance = Map::Units::Behavior::USE_STAND_GROUND;
            iVar1 = MACRO_CALL_MEMBER(
                Map::Units::TroopValueState_Func::moveTribeToNearbyGatehouse, DAT_TroopValueState::ptr)(iVar2);
            if (iVar1 == 0) {
                MACRO_CALL_MEMBER(
                    Map::Units::TroopValueState_Func::moveTowardsParticularUnits, DAT_TroopValueState::ptr)(iVar2);
            }
        }
    }
}
}
