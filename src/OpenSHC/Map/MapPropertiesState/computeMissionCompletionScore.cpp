#include "../../Map.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;
    using Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BDE40
    void MapPropertiesState::computeMissionCompletionScore()
    {
        bool bVar1;
        int* piVar2;
        int iVar3;
        uint uVar4;
        int iVar5;
        int iVar6;
        char* pcVar7;
        short* psVar8;
        int local_8;
        int local_4;
        local_4 = 0;
        local_8 = 0;
        this->missionScore = 0xffffffff;
        this->objectiveGoodsCount = 0;
        iVar5 = 0;
        if (0 < this->eventsCount) {
            pcVar7 = (char*)((int)&this->scenarioEvents[0].data + 0xf);
            iVar6 = 1;
            do {
                if (*(int*)(pcVar7 + -0x17) != 3)
                    goto LAB_004be33e;
                if (((*(int*)(pcVar7 + -0xb) == 1) || (*(int*)(pcVar7 + -0xb) == 0x1b)) && (*pcVar7 != '\0')) {
                    local_4 = *(int*)(pcVar7 + -0x1f);
                    local_8 = *(int*)(pcVar7 + -0x1b);
                }
                if ((*(int*)(pcVar7 + -0xb) != 0) && (*(int*)(pcVar7 + -0xb) != 0x1a))
                    goto LAB_004be33e;
                if (iVar6 < this->eventsCount) {
                    piVar2 = (int*)(pcVar7 + 0xd9);
                    iVar5 = iVar6;
                    do {
                        if ((piVar2[-3] == 3) && ((*piVar2 == 0 || (*piVar2 == 0x1a))))
                            goto LAB_004be33e;
                        iVar5 = iVar5 + 1;
                        piVar2 = piVar2 + 0x39;
                    } while (iVar5 < this->eventsCount);
                }
                if (pcVar7[0x18] == '\0')
                    goto LAB_004bdfd7;
                this->objectiveGoodsType[this->objectiveGoodsCount] = (int)pcVar7[0x17];
                iVar5 = this->objectiveGoodsCount;
                iVar3 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                    (int)*(short*)(pcVar7 + 0x15));
                this->objectiveGoodsSurplus[iVar5]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[iVar5]]
                    - iVar3;
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 0xb:
                case 0xc:
                case 0xd:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    goto LAB_004bdfb7;
                default:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                LAB_004bdfb7:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = iVar5;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x14;
                    break;
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                case 0x18:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x32;
                }
                if (0 < this->objectiveGoodsSurplus[this->objectiveGoodsCount]) {
                    this->objectiveGoodsCount = this->objectiveGoodsCount + 1;
                }
            LAB_004bdfd7:
                if (pcVar7[0x44] == '\0')
                    goto LAB_004be0ae;
                this->objectiveGoodsType[this->objectiveGoodsCount] = (int)pcVar7[0x43];
                iVar5 = this->objectiveGoodsCount;
                iVar3 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                    (int)*(short*)(pcVar7 + 0x41));
                this->objectiveGoodsSurplus[iVar5]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[iVar5]]
                    - iVar3;
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 0xb:
                case 0xc:
                case 0xd:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    goto LAB_004be08e;
                default:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                LAB_004be08e:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = iVar5;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x14;
                    break;
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                case 0x18:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x32;
                }
                if (0 < this->objectiveGoodsSurplus[this->objectiveGoodsCount]) {
                    this->objectiveGoodsCount = this->objectiveGoodsCount + 1;
                }
            LAB_004be0ae:
                if (pcVar7[0x14] == '\0')
                    goto LAB_004be185;
                this->objectiveGoodsType[this->objectiveGoodsCount] = (int)pcVar7[0x13];
                iVar5 = this->objectiveGoodsCount;
                iVar3 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                    (int)*(short*)(pcVar7 + 0x11));
                this->objectiveGoodsSurplus[iVar5]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[iVar5]]
                    - iVar3;
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 0xb:
                case 0xc:
                case 0xd:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    goto LAB_004be165;
                default:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                LAB_004be165:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = iVar5;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x14;
                    break;
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                case 0x18:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x32;
                }
                if (0 < this->objectiveGoodsSurplus[this->objectiveGoodsCount]) {
                    this->objectiveGoodsCount = this->objectiveGoodsCount + 1;
                }
            LAB_004be185:
                if (pcVar7[0x1c] == '\0')
                    goto LAB_004be25c;
                this->objectiveGoodsType[this->objectiveGoodsCount] = (int)pcVar7[0x1b];
                iVar5 = this->objectiveGoodsCount;
                iVar3 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue, this)(
                    (int)*(short*)(pcVar7 + 0x19));
                this->objectiveGoodsSurplus[iVar5]
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[this->objectiveGoodsType[iVar5]]
                    - iVar3;
                switch (this->objectiveGoodsType[this->objectiveGoodsCount]) {
                case 2:
                case 10:
                case 0xb:
                case 0xc:
                case 0xd:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 5;
                    goto LAB_004be23c;
                default:
                    iVar5 = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 10;
                LAB_004be23c:
                    this->objectiveGoodsScore[this->objectiveGoodsCount] = iVar5;
                    break;
                case 6:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x14;
                    break;
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                case 0x18:
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount] * 0x32;
                }
                if (0 < this->objectiveGoodsSurplus[this->objectiveGoodsCount]) {
                    this->objectiveGoodsCount = this->objectiveGoodsCount + 1;
                }
            LAB_004be25c:
                if (pcVar7[0x10] != '\0') {
                    this->objectiveGoodsType[this->objectiveGoodsCount] = 0xf;
                    iVar5 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                        this)((int)*(short*)(pcVar7 + 0xd));
                    this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .currentResources[0xf]
                        - iVar5;
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount];
                    if (0 < this->objectiveGoodsSurplus[this->objectiveGoodsCount]) {
                        this->objectiveGoodsCount = this->objectiveGoodsCount + 1;
                    }
                }
                if (pcVar7[4] != '\0') {
                    this->objectiveGoodsType[this->objectiveGoodsCount] = -1;
                    iVar5 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                        this)((int)*(short*)(pcVar7 + 1));
                    this->objectiveGoodsSurplus[this->objectiveGoodsCount]
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .currentPopulation
                        - iVar5;
                    this->objectiveGoodsScore[this->objectiveGoodsCount]
                        = this->objectiveGoodsSurplus[this->objectiveGoodsCount];
                    if (0 < this->objectiveGoodsSurplus[this->objectiveGoodsCount]) {
                        this->objectiveGoodsCount = this->objectiveGoodsCount + 1;
                    }
                }
            LAB_004be33e:
                pcVar7 = pcVar7 + 0xe4;
                bVar1 = iVar6 < this->eventsCount;
                iVar5 = local_8;
                iVar6 = iVar6 + 1;
            } while (bVar1);
        }
        iVar6 = 0;
        this->monthsRemaining = 0;
        this->timeBonusScore = 0;
        if (iVar5) {
            uVar4 = ((iVar5 - DAT_GameState::instance.mapAndTime.year) * 0xc - DAT_GameState::instance.mapAndTime.month)
                + local_4;
            this->monthsRemaining = uVar4 & ((int)uVar4 < 1) - 1;
            this->timeBonusScore = this->monthsRemaining * 100;
        }
        this->missionScore = DAT_MissionAestheticsDefinedData::instance
                                 .MissionScoreByDifficulty[DAT_GameState::instance.mapAndTime.difficulty]
            + this->timeBonusScore;
        iVar5 = 0;
        if (0 < this->objectiveGoodsCount) {
            piVar2 = this->objectiveGoodsScore;
            do {
                this->missionScore = this->missionScore + *piVar2;
                iVar5 = iVar5 + 1;
                piVar2 = piVar2 + 1;
            } while (iVar5 < this->objectiveGoodsCount);
        }
        this->troopSurvivalScore = 0;
        if ((DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION)
            || ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                && ((int)this->SEC_U3_MapType2_1 < 2)))) {
            psVar8 = &DAT_UnitsState::instance.units[1].owner;
            iVar5 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            do {
                if (((psVar8[-5] != Map::Units::ULS_INVISIBLE) && (*psVar8 == iVar5))
                    && (psVar8[0x107] != 0)) {
                    iVar5 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                        DAT_TroopValueState::ptr)((Map::Units::UnitType)((int)psVar8[-4]));
                    iVar6 = iVar6 + iVar5;
                    iVar5 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                }
                psVar8 = psVar8 + 0x248;
            } while ((int)psVar8 < 0x1651422);
            iVar5 = DAT_GameState::instance.playerDataArray[iVar5].weightedLosses;
            iVar6 = iVar5 + iVar6;
            if (iVar6) {
                this->troopLossPercent = (iVar5 * 100) / iVar6;
                this->troopSurvivalScore = (100 - this->troopLossPercent) * 100;
                this->missionScore = this->missionScore + this->troopSurvivalScore;
            }
        }
        if (DAT_GameCore::instance.mapU4Int1) {
            iVar5 = 0;
            psVar8 = &DAT_UnitsState::instance.units[1].owner;
            do {
                if (((psVar8[-5] != Map::Units::ULS_INVISIBLE) && (*psVar8 == 1)) && (psVar8[0x107] != 0)) {
                    iVar6 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                        DAT_TroopValueState::ptr)((Map::Units::UnitType)((int)psVar8[-4]));
                    iVar5 = iVar5 + iVar6;
                }
                psVar8 = psVar8 + 0x248;
            } while ((int)psVar8 < 0x1651422);
            this->enemyTroopValueLost = DAT_GameState::instance.playerDataArray[2].weightedLosses;
            this->enemyTroopValueTotal = DAT_GameState::instance.playerDataArray[2].weightedLosses + iVar5;
            this->enemyTroopValueSurviving = iVar5;
        }
    }

}
}
