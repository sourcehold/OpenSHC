#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D07C0
    void AICState::playTauntToAttackedPlayerBikFromPlayer(int playerID)
    {
        int iVar1
            = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID);
        if (iVar1 != 0) {
            int _aiTypeMinusOne = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
            int _myTeam = DAT_GameState::instance.mapAndTime.playerTeams[playerID];
            int _curPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            int _bik = 0;
            if (_myTeam == DAT_GameState::instance.mapAndTime.playerTeams[_curPlayer]) {
                _bik = 0x17;
            }
            int _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
            if (_bik == 0) {
                _bik = ((byte)SEC_RNG::instance.currentNumber2 & 3) + 1;
            }
            if (_attackedPlayerID == _curPlayer) {
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
                    playerID, _aiTypeMinusOne, _bik);
            }
        }
    }
}
}
