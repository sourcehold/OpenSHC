#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIC/AITargetChoice.hpp"
#include "OpenSHC/AI/AIC/AITargetChoiceInt.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIC::AITargetChoice;
    using OpenSHC::AI::AIC::AITargetChoiceInt;
    using OpenSHC::Game::Player::PlayerData;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CACB0
    void AICState ::setTargetForTribeBasedOnTargetChoiceLogic(int owner, int tribe)

    {

        int _aiType = DAT_GameState::instance.playerDataArray[owner].aiType;

        int _targetPlayer = 0;

        if (_aiType != 0) {

            int _ownerKeepY = DAT_GameState::instance.playerDataArray[owner].campground.yEntry;
            int _ownerKeepX = DAT_GameState::instance.playerDataArray[owner].campground.xEntry;

            int _minDistance = 10000;
            int _maxGold = 0;
            int _minPoints = 1000000;

            int _player = 1;
            PlayerData* _ptrPlayerData = (PlayerData*)(&DAT_GameState::instance.playerDataArray[1]);

            do {

                if ((DAT_GameState::instance.mapAndTime.playerTeams[_player]
                        != DAT_GameState::instance.mapAndTime.playerTeams[owner])) {

                    int _lord = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_player);

                    if (_lord != 0) {

                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((_ptrPlayerData->campground).xEntry,
                            (_ptrPlayerData->campground).yEntry, _ownerKeepX, _ownerKeepY);

                        AITargetChoiceInt _targetChoice = this->aics[_aiType - 1].TargetChoice;

                        if (_targetChoice == OpenSHC::AI::AIC::AITC_PLAYER) {

                            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_player] != -1) {

                                int _distance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                                if (_distance <= _minDistance) {
                                    _minDistance = _distance;
                                    _targetPlayer = _player;
                                }
                            }

                        } else if (_targetChoice == OpenSHC::AI::AIC::AITC_CLOSEST) {

                            int _distance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            if (_distance <= _minDistance) {
                                _minDistance = _distance;
                                _targetPlayer = _player;
                            }

                        } else if (_targetChoice == OpenSHC::AI::AIC::AITC_GOLD) {

                            int _gold = _ptrPlayerData->currentResources[0xf];
                            if (_maxGold <= _gold) {
                                _minDistance = _minDistance;
                                _maxGold = _gold;
                                _minPoints = _minPoints;
                                _targetPlayer = _player;
                            }

                        } else if (_targetChoice == OpenSHC::AI::AIC::AITC_BALANCED) {

                            int _points = _ptrPlayerData->currentPopulation * 5
                                + _ptrPlayerData->totalTroopValue
                                + _ptrPlayerData->currentResources[0xf] / 100
                                + DAT_DirectionAlgorithmState::instance.distanceHigh * 2;
                            if (_points <= _minPoints) {
                                _minDistance = _minDistance;
                                _maxGold = _maxGold;
                                _minPoints = _points;
                                _targetPlayer = _player;
                            }
                        }
                    }
                }

                _player = _player + 1;
                _ptrPlayerData = _ptrPlayerData + 1;

            } while (_player < 9);

            if (_targetPlayer == 0) {

                int _playerID_backup = 1;
                PlayerData* _ptrPlayerData_backup = &DAT_GameState::instance.playerDataArray[1];

                do {

                    if ((DAT_GameState::instance.mapAndTime.playerTeams[_playerID_backup]
                            != DAT_GameState::instance.mapAndTime.playerTeams[owner])) {

                        int _lordBackup = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                                DAT_UnitsState::ptr)(_playerID_backup);

                        if (_lordBackup != 0) {

                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                DAT_DirectionAlgorithmState::ptr)((_ptrPlayerData_backup->campground).xEntry,
                                (_ptrPlayerData_backup->campground).yEntry, _ownerKeepX, _ownerKeepY);

                            if (DAT_DirectionAlgorithmState::instance.distanceHigh <= _minDistance) {
                                _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                                _targetPlayer = _playerID_backup;
                            }
                        }
                    }

                    _playerID_backup = _playerID_backup + 1;
                    _ptrPlayerData_backup = _ptrPlayerData_backup + 1;

                } while (_playerID_backup < 9);

                if (_targetPlayer == 0) {
                    return;
                }
            }

            DAT_TribesState::instance.tribes[tribe].targetPlayer_outpost = (short)_targetPlayer;
        }

        return;
    }

}
}
