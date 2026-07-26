#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Player::PlayerData;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D05D0
    int AICState ::shareGoldAmongTeamMembers(int playerID, int gold)

    {

        int* piVar1;

        char cVar2;

        int _playerOffset;

        int _goldPerPlayer;

        char* pcVar3;

        char* pcVar4;

        PlayerData* _ptrPlayerData;

        int _totalPlayers;

        int _candidates[9];

        int _targetPlayer;

        int _playerIndex;

        int _playerIndexTracker;

        int* _ptrCurrentGold;

        _totalPlayers = 0;

        _ptrPlayerData = &DAT_GameState::instance.playerDataArray[2];

        _playerOffset = 0;

        _playerIndex = 3;

        do {

            if ((((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _playerOffset + 4) != 0)
                     || (*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _playerOffset + 4)
                         != -1))
                    && (_playerIndex + -2 != playerID))
                && ((*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + _playerOffset + 4)
                        == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                    && (DAT_GameState::instance.playerDataArray[1].lordKilledByPlayerID == 0)))) {

                /*
                        if lord of team member not dead, then: */

                _candidates[_totalPlayers] = _playerIndex + -2;

                _totalPlayers = _totalPlayers + 1;
            }

            if (((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _playerOffset + 8) != 0)
                    || (*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _playerOffset + 8)
                        != -1))
                && ((_playerIndex + -1 != playerID
                    && ((*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + _playerOffset + 8)
                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                        && (_ptrPlayerData->lordKilledByPlayerID == 0)))))) {

                _candidates[_totalPlayers] = _playerIndex + -1;

                _totalPlayers = _totalPlayers + 1;
            }

            if ((((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _playerOffset + 0xc) != 0)
                     || (*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _playerOffset + 0xc)
                         != -1))
                    && (_playerIndex != playerID))
                && ((*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + _playerOffset + 0xc)
                        == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                    && (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID == 0)))) {

                _candidates[_totalPlayers] = _playerIndex;

                _totalPlayers = _totalPlayers + 1;
            }

            if (((*(int*)((int)DAT_GameSynchronyState::instance.currentAIArray + _playerOffset + 0x10) != 0)
                    || (*(int*)((int)DAT_GameSynchronyState::instance.currentPlayerFullIDArray + _playerOffset + 0x10)
                        != -1))
                && ((_playerIndex + 1 != playerID
                    && ((*(int*)((int)DAT_GameState::instance.mapAndTime.playerTeams + _playerOffset + 0x10)
                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                        && (DAT_GameState::instance.playerDataArray[4].lordKilledByPlayerID == 0)))))) {

                _candidates[_totalPlayers] = _playerIndex + 1;

                _totalPlayers = _totalPlayers + 1;
            }

            _playerIndexTracker = _playerIndex + 2;

            _playerOffset = _playerOffset + 16;

            _ptrPlayerData = _ptrPlayerData + 0x39f4;

            _playerIndex = _playerIndex + 4;

        } while (_playerIndexTracker < 9);

        /*
            fixme: repurposed variable */

        if (((_totalPlayers != 0)
                && (_goldPerPlayer = gold / _totalPlayers, _playerOffset = _goldPerPlayer, _goldPerPlayer != 0))
            && (_playerIndex = 0, 0 < _totalPlayers)) {

            _ptrCurrentGold = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xf;

            do {

                _targetPlayer = _candidates[_playerIndex];

                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_targetPlayer] != -1) {

                    /*
                              "Goods received from ally"
                       added by script: "Goods received from ally" */

                    pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 1);

                    pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;

                    do {

                        cVar2 = *pcVar3;

                        *pcVar4 = cVar2;

                        pcVar3 = pcVar3 + 1;

                        pcVar4 = pcVar4 + 1;

                    } while (cVar2 != '\0');

                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(_targetPlayer, 0);

                    /*
                              "Goods types"
                       added by script: "Gold" */

                    pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, 0xf);

                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                        DAT_GameSynchronyState::instance.receivedChatMessage, "%d %s - ", _goldPerPlayer, pcVar3);

                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(_targetPlayer, playerID);
                }

                *_ptrCurrentGold = *_ptrCurrentGold - _goldPerPlayer;

                piVar1 = DAT_GameState::instance.playerDataArray[_targetPlayer].currentResources + 0xf;

                *piVar1 = *piVar1 + _goldPerPlayer;

                _playerOffset = _targetPlayer * 0x39f4 + 0x115c304;

                _playerIndex = _playerIndex + 1;

            } while (_playerIndex < _totalPlayers);
        }

        return _playerOffset;
    }

}
}
