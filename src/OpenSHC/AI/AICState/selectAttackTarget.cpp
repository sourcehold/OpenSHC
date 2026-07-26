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

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4680
    void AICState ::selectAttackTarget(int playerID)

    {

        int fromXPosition;

        int fromYPosition;

        int iVar1;

        int _alive1;

        int _isLordAlive;

        int _lord;

        int _selectedPlayer;

        PlayerData* _pPlayerData2;

        int _iPlayer2;

        int _iPlayer;

        PlayerData* _ptrPlayerData;

        int _lowestDistance;

        int _highestGold;

        int _lowestPoints;

        int _currentGoldValue;

        int _points;

        int _reqState;

        int _reqState2;

        AITypeInt _aiType;

        AITargetChoiceInt _targetChoiceType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        _selectedPlayer = 0;

        if (_aiType != OpenSHC::AI::AIT_NULL) {

            fromXPosition = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;

            fromYPosition = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;

            _lowestDistance = 10000;

            _highestGold = 0;

            _lowestPoints = 1000000;

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::computeNervousness, this)(playerID);

            _reqState = DAT_GameState::instance.playerDataArray[playerID].requestStateUnk;

            if (((_reqState == 2) || (_reqState == 1))
                && (iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                        DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk),
                    iVar1 == 0)) {

                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
            }

            _reqState2 = DAT_GameState::instance.playerDataArray[playerID].requestStateUnk;

            if (_reqState2 == 2) {

                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID = 0;

                return;
            }

            if (_reqState2 == 1) {

                _alive1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                    DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk);

                if (_alive1 != 0) {

                    DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID
                        = DAT_GameState::instance.playerDataArray[playerID].requestedAttackTargetUnk;

                    return;
                }

                DAT_GameState::instance.playerDataArray[playerID].requestStateUnk = 0;
            }

            _pPlayerData2 = (PlayerData*)(&DAT_GameState::instance.playerDataArray[1]);

            _iPlayer = 1;

            do {

                if ((DAT_GameState::instance.mapAndTime.playerTeams[_iPlayer]
                        != DAT_GameState::instance.mapAndTime.playerTeams[playerID])
                    && (_isLordAlive = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_iPlayer),
                        _isLordAlive != 0)) {

                    /*
                              fixme:improve: use pythagoras */

                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)((_pPlayerData2->campground).xEntry,
                        (_pPlayerData2->campground).yEntry, fromXPosition, fromYPosition);

                    _targetChoiceType = this->aics[_aiType + ~OpenSHC::AI::AIT_NULL].TargetChoice;

                    _currentGoldValue = _highestGold;

                    _points = _lowestPoints;

                    if (_targetChoiceType == OpenSHC::AI::AIC::AITC_PLAYER) {

                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_iPlayer] != -1) {

                        LAB_004d47c5:
                            if (DAT_DirectionAlgorithmState::instance.distanceHigh <= _lowestDistance) {

                                _lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;

                            LAB_004d4845:
                                _lowestPoints = _points;

                                _highestGold = _currentGoldValue;

                                _selectedPlayer = _iPlayer;
                            }
                        }

                    }

                    else {

                        if (_targetChoiceType == OpenSHC::AI::AIC::AITC_CLOSEST)
                            goto LAB_004d47c5;

                        if (_targetChoiceType == OpenSHC::AI::AIC::AITC_GOLD) {

                            _currentGoldValue = _pPlayerData2->currentResources[0xf];

                            if (_highestGold <= _pPlayerData2->currentResources[0xf])
                                goto LAB_004d4845;

                        }

                        else if ((_targetChoiceType == OpenSHC::AI::AIC::AITC_BALANCED)
                            && (_points = _pPlayerData2->currentPopulation * 5 + _pPlayerData2->totalTroopValue
                                    + _pPlayerData2->currentResources[0xf] / 100
                                    + DAT_DirectionAlgorithmState::instance.distanceHigh * 2,
                                _points <= _lowestPoints))
                            goto LAB_004d4845;
                    }
                }

                _iPlayer = _iPlayer + 1;

                _pPlayerData2 = _pPlayerData2 + 0x39f4;

            } while (_iPlayer < 9);

            if (_selectedPlayer == 0) {

                _iPlayer2 = 1;

                _ptrPlayerData = &DAT_GameState::instance.playerDataArray[1];

                do {

                    if (((DAT_GameState::instance.mapAndTime.playerTeams[_iPlayer2]
                             != DAT_GameState::instance.mapAndTime.playerTeams[playerID])
                            && (_lord = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                                    DAT_UnitsState::ptr)(_iPlayer2),
                                _lord != 0))
                        && (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                DAT_DirectionAlgorithmState::ptr)((_ptrPlayerData->campground).xEntry,
                                (_ptrPlayerData->campground).yEntry, fromXPosition, fromYPosition),
                            DAT_DirectionAlgorithmState::instance.distanceHigh <= _lowestDistance)) {

                        _lowestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;

                        _selectedPlayer = _iPlayer2;
                    }

                    _iPlayer2 = _iPlayer2 + 1;

                    /*
                              next player */

                    _ptrPlayerData = _ptrPlayerData + 0xe7d;

                } while (_iPlayer2 < 9);

                if (_selectedPlayer == 0) {

                    return;
                }
            }

            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk = _selectedPlayer;

            DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID = _selectedPlayer;
        }

        return;
    }

}
}
