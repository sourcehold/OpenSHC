#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3AE0
    void AICState::aiRecruitUnits(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int aicIndex = aiType - 1;

        bool isExtremeTrail = DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER
            && DAT_GameCore::instance.isSkirmishTrail == TRUE
            && DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME;

        int recruitInterval = (&this->aics[aicIndex]
                .RecruitInterval)[DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling];
        int recruitCount = recruitInterval != 0 ? 1 : 2;
        if (isExtremeTrail)
            recruitCount++;

        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0) {
            DAT_GameState::instance.playerDataArray[playerID].aiRecruitIntervalTracker++;
            if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitIntervalTracker < recruitInterval)
                return;
        } else {
            recruitCount = 4;
        }

        DAT_GameState::instance.playerDataArray[playerID].aiRecruitIntervalTracker = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].idlePeasantsCount <= 0)
            return;
        if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending == 0)
            return;

        if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
            == OpenSHC::AI::AIRUC_DEFENSIVE) {
            int defTotal = this->aics[aicIndex].DefTotal;
            if (isExtremeTrail)
                defTotal = defTotal * 4 / 3;
            if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0)
                defTotal = defTotal * 4;
            if (DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk >= defTotal)
                return;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
            == OpenSHC::AI::AIRUC_RAIDING) {
            if (DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk >= MACRO_CALL_MEMBER(
                    OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(aicIndex, playerID))
                return;
        } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_ATTACKING
            && DAT_GameState::instance.playerDataArray[playerID].aiPlayerState != 0) {
            return;
        }

        bool recruitDiggingUnit = false;
        if (this->aics[aicIndex].DefDiggingUnitMax != 0
            && MACRO_CALL_MEMBER(
                   OpenSHC::Map::TileMapState_Func::countUnfinishedMoatTilesForPlayer, DAT_TileMapState::ptr)(playerID)
                != 0) {
            int diggerTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[10];
            if (diggerTribeID == 0
                || DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[10]
                    != DAT_TribesState::instance.tribes[diggerTribeID].uid
                || DAT_TribesState::instance.tribes[diggerTribeID].size < this->aics[aicIndex].DefDiggingUnitMax)
                recruitDiggingUnit = true;
        }

        UnitType unitType = (UnitType)0;
        int behaviourType = 0;
        for (int i = 0; i < recruitCount; i++) {
            if (recruitDiggingUnit && (SEC_RNG::instance.currentNumber2 & 1) != 0)
                recruitDiggingUnit = false;

            if (recruitDiggingUnit) {
                if (DAT_GameState::instance.playerDataArray[playerID].barracks.id == 0
                    && DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id == 0)
                    return;
                unitType = (UnitType)this->aics[aicIndex].DefDiggingUnit;
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_DEFENSIVE) {
                if (DAT_GameState::instance.playerDataArray[playerID].aiDefUnitChoiceIndex > 7)
                    DAT_GameState::instance.playerDataArray[playerID].aiDefUnitChoiceIndex = 0;
                if ((&this->aics[aicIndex]
                            .DefUnit1)[DAT_GameState::instance.playerDataArray[playerID].aiDefUnitChoiceIndex]
                    == 0)
                    DAT_GameState::instance.playerDataArray[playerID].aiDefUnitChoiceIndex = 0;
                int choice = DAT_GameState::instance.playerDataArray[playerID].aiDefUnitChoiceIndex;
                unitType = (UnitType)(&this->aics[aicIndex].DefUnit1)[choice];
                DAT_GameState::instance.playerDataArray[playerID].aiDefUnitChoiceIndex = choice + 1;
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_RAIDING) {
                if (DAT_GameState::instance.playerDataArray[playerID].aiRaidUnitChoiceIndex > 7)
                    DAT_GameState::instance.playerDataArray[playerID].aiRaidUnitChoiceIndex = 0;
                if ((&this->aics[aicIndex]
                            .RaidUnit1)[DAT_GameState::instance.playerDataArray[playerID].aiRaidUnitChoiceIndex]
                    == 0)
                    DAT_GameState::instance.playerDataArray[playerID].aiRaidUnitChoiceIndex = 0;
                int choice = DAT_GameState::instance.playerDataArray[playerID].aiRaidUnitChoiceIndex;
                unitType = (UnitType)(&this->aics[aicIndex].RaidUnit1)[choice];
                DAT_GameState::instance.playerDataArray[playerID].aiRaidUnitChoiceIndex = choice + 1;
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_ATTACKING) {
                behaviourType = MACRO_CALL_MEMBER(
                    OpenSHC::AI::AICState_Func::randomlySelectAttackUnitTypeToRecruit, this)(playerID);
                unitType = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getUnitTypeForUnitBehaviourType, this)(
                    playerID, (AIUnitBehaviourType)behaviourType);
            }
            if (unitType == (UnitType)0)
                return;

            int buildingID;
            if (unitType == OpenSHC::Map::Units::UT_E_ENGINEER || unitType == OpenSHC::Map::Units::UT_E_LADDER)
                buildingID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
            else if (unitType == OpenSHC::Map::Units::UT_TUNNELER)
                buildingID = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.id;
            else if (unitType == OpenSHC::Map::Units::UT_E_MONK)
                buildingID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_CATHEDRAL);
            else if (unitType < 70)
                buildingID = DAT_GameState::instance.playerDataArray[playerID].barracks.id;
            else
                buildingID = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id;
            if (buildingID == 0)
                return;

            int unitID;
            if (unitType == OpenSHC::Map::Units::UT_E_ENGINEER || unitType == OpenSHC::Map::Units::UT_E_LADDER
                || unitType == OpenSHC::Map::Units::UT_TUNNELER || unitType == OpenSHC::Map::Units::UT_E_MONK
                || unitType >= 70)
                unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    unitType, buildingID, playerID, 0);
            else
                unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(
                    unitType, buildingID, playerID, 0);

            if (unitID == 0) {
                if (this->aics[aicIndex].tradeAmountEquipment <= 0)
                    return;
                if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason != 2)
                    return;
                if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0)
                    DAT_GameState::instance.playerDataArray[playerID]
                        .resourcesToAcquireArray[DAT_UnitsState::instance.euroUnitRequiredResource]
                        = this->aics[aicIndex].tradeAmountEquipment;
                else
                    DAT_GameState::instance.playerDataArray[playerID]
                        .resourcesToAcquireArray[DAT_UnitsState::instance.euroUnitRequiredResource] = 5;
                return;
            }

            if (recruitDiggingUnit)
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiAddUnitToMoatDiggerTribe, this)(unitID);
            else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_DEFENSIVE) {
                if (DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk
                    < this->aics[aicIndex].DefWalls)
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::assignUnitToATribe, this)(unitID);
                else
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitToSmallestPatrolTribe, this)(unitID);
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_RAIDING) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiAssignUnitToDefensiveTribe, this)(unitID);
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiRecruitUnitChoiceState
                == OpenSHC::AI::AIRUC_ATTACKING) {
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitToItsTribe, this)(unitID, behaviourType);
            }
        }
    }
}
}
