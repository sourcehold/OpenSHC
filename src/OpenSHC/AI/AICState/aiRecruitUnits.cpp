#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoiceInt.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AICState;
    using OpenSHC::AI::AIRecruitUnitChoice;
    using OpenSHC::AI::AIRecruitUnitChoiceInt;
    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIUnitBehaviourType;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::TrailType;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3AE0
    void AICState ::aiRecruitUnits(int playerID)

    {

        int* piVar1;

        AIRecruitUnitChoiceInt AVar2;

        bool bVar3;

        int iVar4;

        int iVar5;

        int _tribeID_defDiggingUnitMax;

        int _unitID;

        UnitType _unitType;

        int iVar6;

        AICState* _pAICState;

        int local_8;

        int _aicRecruitInterval;

        int _nervousActionTracker;

        int _buildingID;

        int _unitChoiceIndex;

        AIRecruitUnitChoiceInt _unitTypeChoice;

        int _defTotal;

        AITypeInt _aiType;

        int _playerID2;

        bool _recruitDefDiggingUnit;

        _playerID2 = playerID;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        _unitType = ((UnitType)0);

        _pAICState = this;

        if (_aiType != OpenSHC::AI::AIT_NULL) {

            bVar3 = false;

            _recruitDefDiggingUnit = false;

            iVar6 = _aiType + ~OpenSHC::AI::AIT_NULL;

            if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                    && (DAT_GameCore::instance.isSkirmishTrail == TRUE))
                && (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME)) {

                bVar3 = true;
            }

            iVar4 = iVar6 * 0xa9;

            _aicRecruitInterval = *(int*)((int)this
                + (DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling + iVar4) * 4 + 0x164);

            local_8 = -(uint)(_aicRecruitInterval != 0) + 2;

            if (bVar3) {

                local_8 = -(uint)(_aicRecruitInterval != 0) + 3;
            }

            _nervousActionTracker = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;

            if (_nervousActionTracker < 1) {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].aiRecruitIntervalTracker;

                *piVar1 = *piVar1 + 1;

                if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitIntervalTracker < _aicRecruitInterval) {

                    return;
                }

            }

            else {

                local_8 = 4;
            }

            iVar5 = DAT_GameState::instance.playerDataArray[playerID].idlePeasantsCount;

            DAT_GameState::instance.playerDataArray[playerID].aiRecruitIntervalTracker = 0;

            if ((0 < iVar5) && (DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0)) {

                AVar2 = DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState;

                if (AVar2 == OpenSHC::AI::AIRUC_DEFENSIVE) {

                    _defTotal = *(int*)((int)this + iVar6 * 0x2a4 + 0x170);

                    if (bVar3) {

                        _defTotal = (_defTotal * 4) / 3;
                    }

                    if (0 < _nervousActionTracker) {

                        _defTotal = _defTotal * 4;
                    }

                    if (_defTotal <= DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk) {

                        return;
                    }

                }

                else if (AVar2 == OpenSHC::AI::AIRUC_RAIDING) {

                    iVar5 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(
                        iVar6, playerID);

                    if (iVar5 <= DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk) {

                        return;
                    }

                }

                else if ((AVar2 == OpenSHC::AI::AIRUC_ATTACKING)
                    && (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState != 0)) {

                    return;
                }

                iVar6 = iVar6 * 0x2a4;

                /*
                        DefDiggingUnitMax */

                /*
                        DefDiggingUnitMax */

                if (((*(int*)((int)this + iVar6 + 0x15c) != 0)
                        && (iVar5
                            = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::countUnfinishedMoatTilesForPlayer,
                                DAT_TileMapState::ptr)(playerID),
                            iVar5 != 0))
                    && ((_tribeID_defDiggingUnitMax
                        = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[10],
                        _tribeID_defDiggingUnitMax == 0
                            || ((DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[10]
                                    != DAT_TribesState::instance.tribes[_tribeID_defDiggingUnitMax].uid
                                || ((int)DAT_TribesState::instance.tribes[_tribeID_defDiggingUnitMax].size
                                    < *(int*)((int)this + iVar6 + 0x15c))))))) {

                    _recruitDefDiggingUnit = true;
                }

                playerID = 0;

                if (0 < local_8) {

                    do {

                        if (_recruitDefDiggingUnit) {

                            if (((byte)SEC_RNG::instance.currentNumber2 & 1) != 0) {

                                _recruitDefDiggingUnit = false;

                                goto LAB_004d3cc1;
                            }

                            if (DAT_GameState::instance.playerDataArray[_playerID2].barracks.id == 0) {

                                if (DAT_GameState::instance.playerDataArray[_playerID2].mercenaryPost.id == 0) {

                                    return;
                                }

                                /*
                                                DefDiggingUnit */

                                _unitType = *(UnitType*)((int)this + iVar6 + 0x160);

                            }

                            else {

                                /*
                                                DefDiggingUnit */

                                _unitType = *(UnitType*)((int)this + iVar6 + 0x160);
                            }

                        }

                        else {

                        LAB_004d3cc1:
                            _unitTypeChoice
                                = DAT_GameState::instance.playerDataArray[_playerID2].aiRecruitUnitChoiceState;

                            if (_unitTypeChoice == OpenSHC::AI::AIRUC_DEFENSIVE) {

                                if (7 < DAT_GameState::instance.playerDataArray[_playerID2].aiDefUnitChoiceIndex) {

                                    DAT_GameState::instance.playerDataArray[_playerID2].aiDefUnitChoiceIndex = 0;
                                }

                                /*
                                                DefUnit 1 up to 8 */

                                if (*(int*)((int)this
                                        + (DAT_GameState::instance.playerDataArray[_playerID2].aiDefUnitChoiceIndex
                                              + iVar4)
                                            * 4
                                        + 0x184)
                                    == 0) {

                                    DAT_GameState::instance.playerDataArray[_playerID2].aiDefUnitChoiceIndex = 0;
                                }

                                _unitChoiceIndex
                                    = DAT_GameState::instance.playerDataArray[_playerID2].aiDefUnitChoiceIndex;

                                /*
                                                DefUnit 1 up to 8 */

                                _unitType = *(UnitType*)((int)this + (iVar4 + _unitChoiceIndex) * 4 + 0x184);

                                DAT_GameState::instance.playerDataArray[_playerID2].aiDefUnitChoiceIndex
                                    = _unitChoiceIndex + 1;

                            }

                            else if (_unitTypeChoice == OpenSHC::AI::AIRUC_RAIDING) {

                                if (7 < DAT_GameState::instance.playerDataArray[_playerID2].aiRaidUnitChoiceIndex) {

                                    DAT_GameState::instance.playerDataArray[_playerID2].aiRaidUnitChoiceIndex = 0;
                                }

                                if (*(int*)((int)this
                                        + (DAT_GameState::instance.playerDataArray[_playerID2].aiRaidUnitChoiceIndex
                                              + iVar4)
                                            * 4
                                        + 0x1ac)
                                    == 0) {

                                    DAT_GameState::instance.playerDataArray[_playerID2].aiRaidUnitChoiceIndex = 0;
                                }

                                iVar5 = DAT_GameState::instance.playerDataArray[_playerID2].aiRaidUnitChoiceIndex;

                                _unitType = *(UnitType*)((int)this + (iVar4 + iVar5) * 4 + 0x1ac);

                                DAT_GameState::instance.playerDataArray[_playerID2].aiRaidUnitChoiceIndex = iVar5 + 1;

                            }

                            else if (_unitTypeChoice == OpenSHC::AI::AIRUC_ATTACKING) {

                                _pAICState = (AICState*)MACRO_CALL_MEMBER(
                                    OpenSHC::AI::AICState_Func::randomlySelectAttackUnitTypeToRecruit, this)(
                                    _playerID2);

                                _unitType
                                    = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getUnitTypeForUnitBehaviourType,
                                        this)(_playerID2, (AIUnitBehaviourType)((int)(_pAICState)));
                            }
                        }

                        if (_unitType == ((UnitType)0)) {

                            return;
                        }

                        if (_unitType == OpenSHC::Map::Units::UT_E_ENGINEER) {

                            _buildingID = DAT_GameState::instance.playerDataArray[_playerID2].engineersGuild.id;

                        }

                        else if (_unitType == OpenSHC::Map::Units::UT_E_LADDER) {

                            _buildingID = DAT_GameState::instance.playerDataArray[_playerID2].engineersGuild.id;

                        }

                        else if (_unitType == OpenSHC::Map::Units::UT_TUNNELER) {

                            _buildingID = DAT_GameState::instance.playerDataArray[_playerID2].tunnelersGuild.id;

                        }

                        else if (_unitType == OpenSHC::Map::Units::UT_E_MONK) {

                            _buildingID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                                DAT_BuildingsState::ptr)(_playerID2, OpenSHC::Map::Buildings::BT_CATHEDRAL);

                        }

                        else if ((int)_unitType < 0x46) {

                            _buildingID = DAT_GameState::instance.playerDataArray[_playerID2].barracks.id;

                        }

                        else {

                            _buildingID = DAT_GameState::instance.playerDataArray[_playerID2].mercenaryPost.id;
                        }

                        if (_buildingID == 0) {

                            return;
                        }

                        if ((((_unitType == OpenSHC::Map::Units::UT_E_ENGINEER)
                                 || (_unitType == OpenSHC::Map::Units::UT_E_LADDER))
                                || (_unitType == OpenSHC::Map::Units::UT_TUNNELER))
                            || ((_unitType == OpenSHC::Map::Units::UT_E_MONK || (0x45 < (int)_unitType)))) {

                            _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit,
                                DAT_UnitsState::ptr)(_unitType, (undefined4)((int)(_buildingID)), _playerID2, 0);

                        }

                        else {

                            _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit,
                                DAT_UnitsState::ptr)(_unitType, (undefined4)((int)(_buildingID)), _playerID2, 0);
                        }

                        if (_unitID == 0) {

                            /*
                                          tradeAmountEquipment */

                            iVar6 = *(int*)((int)this + iVar6 + 0x9c);

                            if (iVar6 < 1) {

                                return;
                            }

                            if (DAT_UnitsState::instance.DAT_EuroUnitAcquisitionFailReason != 2) {

                                return;
                            }

                            if (DAT_GameState::instance.playerDataArray[_playerID2].aiNervousActionsTracker < 1) {

                                DAT_GameState::instance.playerDataArray[_playerID2]
                                    .resourcesToAcquireArray[DAT_UnitsState::instance.DAT_EuroUnitRequiredResource]
                                    = iVar6;

                                return;
                            }

                            DAT_GameState::instance.playerDataArray[_playerID2]
                                .resourcesToAcquireArray[DAT_UnitsState::instance.DAT_EuroUnitRequiredResource] = 5;

                            return;
                        }

                        if (_recruitDefDiggingUnit) {

                            /*
                                          digging units? */

                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiAddUnitToMoatDiggerTribe, this)(_unitID);

                        }

                        else {

                            AVar2 = DAT_GameState::instance.playerDataArray[_playerID2].aiRecruitUnitChoiceState;

                            /*
                                          0 = defensive, 1 = raid, 2 = army */

                            if (AVar2 == OpenSHC::AI::AIRUC_DEFENSIVE) {

                                if (DAT_GameState::instance.playerDataArray[_playerID2].totalDefensiveTroopsUnk
                                    < *(int*)((int)this + iVar6 + 0x180)) {

                                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::assignUnitToATribe, this)(_unitID);

                                }

                                else {

                                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitToSmallestPatrolTribe, this)(
                                        _unitID);
                                }

                            }

                            else if (AVar2 == OpenSHC::AI::AIRUC_RAIDING) {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiAssignUnitToDefensiveTribe, this)(
                                    _unitID);

                            }

                            else if (AVar2 == OpenSHC::AI::AIRUC_ATTACKING) {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitToItsTribe, this)(
                                    _unitID, (int)((int)(_pAICState)));
                            }
                        }

                        playerID = playerID + 1;

                        if (local_8 <= playerID) {

                            return;
                        }

                    } while (true);
                }
            }
        }

        return;
    }

}
}
