#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIC/AITargetChoice.hpp"
#include "OpenSHC/AI/AIC/AITargetChoiceInt.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIC::AITargetChoice;
    using OpenSHC::AI::AIC::AITargetChoiceInt;
    using OpenSHC::Game::Player::PlayerData;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4680
    void AICState ::selectAttackTarget(int playerID)
    {
        AITypeInt _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        int _selectedPlayer = 0;

        if (_aiType != OpenSHC::AI::AIT_NULL) {
            int fromXPosition = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
            int fromYPosition = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;
            int _lowestDistance = 10000;
            int _highestGold = 0;
            int _lowestPoints = 1000000;

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeNervousness, this)(playerID);

            int _reqState = DAT_GameState::instance.playerDataArray[playerID].requestStateUnk;
            if (((_reqState == 2) || (_reqState == 1))
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                    DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk) == 0) {
                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
            }

            int _reqState2 = DAT_GameState::instance.playerDataArray[playerID].requestStateUnk;
            if (_reqState2 == 2) {
                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID = 0;
                return;
            }
            if (_reqState2 == 1) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                        DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk) != 0) {
                    DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID
                        = DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk;
                    return;
                }
                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
            }

            PlayerData* _pPlayerData2 = (PlayerData*)(&DAT_GameState::instance.playerDataArray[1]);
            int _iPlayer = 1;

            do {
                if ((DAT_GameState::instance.mapAndTime.playerTeams[_iPlayer]
                        != DAT_GameState::instance.mapAndTime.playerTeams[playerID])
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                        DAT_UnitsState::ptr)(_iPlayer) != 0) {

                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)((_pPlayerData2->campground).xEntry,
                        (_pPlayerData2->campground).yEntry, fromXPosition, fromYPosition);

                    AITargetChoiceInt _targetChoiceType = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].TargetChoice;
                    int _currentGoldValue = _highestGold;
                    int _points = _lowestPoints;

                    if (_targetChoiceType == OpenSHC::AI::AIC::AITC_PLAYER) {
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_iPlayer] != -1) {
                            if (DAT_DirectionAlgorithmState::instance.distanceHigh <= _lowestDistance) {
                                _lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                                _lowestPoints = _points;
                                _highestGold = _currentGoldValue;
                                _selectedPlayer = _iPlayer;
                            }
                        }
                    } else if (_targetChoiceType == OpenSHC::AI::AIC::AITC_CLOSEST) {
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh <= _lowestDistance) {
                            _lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            _lowestPoints = _points;
                            _highestGold = _currentGoldValue;
                            _selectedPlayer = _iPlayer;
                        }
                    } else if (_targetChoiceType == OpenSHC::AI::AIC::AITC_GOLD) {
                        _currentGoldValue = _pPlayerData2->currentResources[0xf];
                        if (_highestGold <= _pPlayerData2->currentResources[0xf]) {
                            _lowestPoints = _points;
                            _highestGold = _currentGoldValue;
                            _selectedPlayer = _iPlayer;
                        }
                    } else if (_targetChoiceType == OpenSHC::AI::AIC::AITC_BALANCED) {
                        _points = _pPlayerData2->currentPopulation * 5 + _pPlayerData2->totalTroopValue
                            + _pPlayerData2->currentResources[0xf] / 100
                            + DAT_DirectionAlgorithmState::instance.distanceHigh * 2;
                        if (_points <= _lowestPoints) {
                            _lowestPoints = _points;
                            _highestGold = _currentGoldValue;
                            _selectedPlayer = _iPlayer;
                        }
                    }
                }

                _iPlayer = _iPlayer + 1;
                _pPlayerData2 = _pPlayerData2 + 0xe7d;
            } while (_iPlayer < 9);

            if (_selectedPlayer == 0) {
                int _iPlayer2 = 1;
                PlayerData* _ptrPlayerData = &DAT_GameState::instance.playerDataArray[1];
                do {
                    if (((DAT_GameState::instance.mapAndTime.playerTeams[_iPlayer2]
                             != DAT_GameState::instance.mapAndTime.playerTeams[playerID])
                            && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                                DAT_UnitsState::ptr)(_iPlayer2) != 0)
                        && (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                DAT_DirectionAlgorithmState::ptr)((_ptrPlayerData->campground).xEntry,
                                (_ptrPlayerData->campground).yEntry, fromXPosition, fromYPosition),
                            DAT_DirectionAlgorithmState::instance.distanceHigh <= _lowestDistance)) {
                        _lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        _selectedPlayer = _iPlayer2;
                    }
                    _iPlayer2 = _iPlayer2 + 1;
                    _ptrPlayerData = _ptrPlayerData + 0xe7d;
                } while (_iPlayer2 < 9);

                if (_selectedPlayer == 0)
                    return;
            }

            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk = _selectedPlayer;
            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID = _selectedPlayer;
        }
    }
}
}
