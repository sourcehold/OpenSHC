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
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return;
        }

        int const iVar2 = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xb];

        if (iVar2 == 0) {
            return;
        }

        if (DAT_TribesState::instance.tribes[iVar2].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xb]) {
            return;
        }

        if (DAT_TribesState::instance.tribes[iVar2].selectionTargetUnitID == 0) {
            return;
        }

        DAT_TribesState::instance.tribes[iVar2].unitStance = Map::Units::Behavior::USE_STAND_GROUND;

        if (MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTribeToNearbyGatehouse, DAT_TroopValueState::ptr)(
                iVar2)
            == 0) {
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::moveTowardsParticularUnits, DAT_TroopValueState::ptr)(
                iVar2);
        }
    }
}
}
