#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDCF0
    BOOLEnum AICState ::aiShouldAttackOrWaitForTeamCoordination(int playerID)

    {

        AITypeInt _aiType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType == OpenSHC::AI::AIT_NULL) {
            return FALSE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].requestStateUnk != 1) {
            int _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
            if (DAT_GameState::instance.playerDataArray[_attackedPlayerID].totalTroopValue < 100) {
                DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength = 0;
            }

            int _attForceBase = *(int*)((int)this + (_aiType - 1) * 0x2a4 + 0x1f4);
            int _currentWaveStrength = DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength;
            int _totalAttack = DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops;

            if (_totalAttack < _attForceBase + _currentWaveStrength) {
                return FALSE;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel == 0) {
                return TRUE;
            }

            int _readyTeamMembers = 0;
            int _unreadyTeamMembers = 0;
            int _iPlayer = 1;
            PlayerData* _pPlayerData = &DAT_GameState::instance.playerDataArray[1];

            do {
                if (_iPlayer != playerID) {
                    int _isAlive = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                        DAT_UnitsState::ptr)(_iPlayer);
                    if (_isAlive != 0) {
                        BOOLEnum _isAI = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(_iPlayer);
                        if (_isAI != FALSE) {
                            if (DAT_GameState::instance.mapAndTime.playerTeams[_iPlayer]
                                == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                                if (_pPlayerData->aiPlayerState != 0) {
                                    return TRUE;
                                }
                                if (_pPlayerData->totalAttackTroops - _pPlayerData->totalAttackingEngineerTroops
                                    >= *(int*)((int)this + (_pPlayerData->aiType - 1) * 0x2a4 + 0x1f4)
                                        + _pPlayerData->currentWaveRandomAttackingStrength) {
                                    _readyTeamMembers = _readyTeamMembers + 1;
                                }
                                else {
                                    _unreadyTeamMembers = _unreadyTeamMembers + 1;
                                }
                            }
                        }
                    }
                }
                _iPlayer = _iPlayer + 1;
                _pPlayerData = _pPlayerData + 1;
            } while (_iPlayer < 9);

            if (_readyTeamMembers >= DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel) {
                return TRUE;
            }
            if (_unreadyTeamMembers == 0) {
                return TRUE;
            }
            DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience =
                DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience + 1;
            if (DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience <= 0x30
                || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)) {
                return FALSE;
            }
        }

        return TRUE;
    }

}
}
