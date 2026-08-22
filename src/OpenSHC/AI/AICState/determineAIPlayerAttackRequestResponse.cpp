#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D38C0
    BOOLEnum AICState ::determineAIPlayerAttackRequestResponse(
        int playerID, undefined4 param_2, int requestedByPlayerID)

    {

        AITypeInt AVar1;

        AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar1 != OpenSHC::AI::AIT_NULL) {

            if (DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue == 0) {

                if (DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                        - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops
                    < *(int*)((int)this + (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x1fc)) {

                    MACRO_CALL(OpenSHC::Global_Func::PlayWillNotAttack2BikFromPlayerToPlayer)(
                        playerID, requestedByPlayerID);

                    return FALSE;
                }

                MACRO_CALL(OpenSHC::Global_Func::PlayWillAttackBikFromPlayerToPlayer)(playerID, requestedByPlayerID);

                return TRUE;
            }

            MACRO_CALL(OpenSHC::Global_Func::PlayWillNotAttack1BikFromPlayerToPlayer)(playerID, requestedByPlayerID);
        }

        return FALSE;
    }

}
}
