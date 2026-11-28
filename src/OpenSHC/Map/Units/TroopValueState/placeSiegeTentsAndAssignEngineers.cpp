#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Game::GameMode2;
        using Map::MapType2;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B710
        void TroopValueState::placeSiegeTentsAndAssignEngineers(int param_1, int param_2)
        {
            int owner = DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1];
            if (!owner) {
                owner = 2;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                owner = 2;
            }
            int engineerTotal = 0;
            DAT_TroopValueState::instance.attackInfo.createTribeAmount = 0;
            for (int k = 0; k <= 4; k++) {
                int const count = (char)DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore[param_1][k];
                Commands::MappersEnum const buildingType = DAT_AttackInfoDefinedData::instance.field_0xc8[k];
                int const engineers = DAT_AttackInfoDefinedData::instance.field_0x9ec[k];
                for (int n = 0; n < count; n++) {
                    DAT_TroopValueState::instance.attackInfo
                        .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                        .engineerBuildingType = buildingType;
                    DAT_TroopValueState::instance.attackInfo
                        .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                        .engineerCount = engineers;
                    DAT_TroopValueState::instance.attackInfo.createTribeAmount
                        = DAT_TroopValueState::instance.attackInfo.createTribeAmount + 1;
                    engineerTotal = engineerTotal + engineers;
                    if (DAT_TroopValueState::instance.attackInfo.createTribeAmount >= 250) {
                        break;
                    }
                }
            }
            int const count = (char)DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore[param_1][8];
            Commands::MappersEnum const buildingType
                = (Commands::MappersEnum)DAT_AttackInfoDefinedData::instance.field_0xe8;
            int const engineers = DAT_AttackInfoDefinedData::instance.field_0xa0c;
            for (int n = 0; n < count; n++) {
                if (DAT_TroopValueState::instance.attackInfo.createTribeAmount >= 250) {
                    break;
                }
                DAT_TroopValueState::instance.attackInfo
                    .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                    .engineerBuildingType = buildingType;
                DAT_TroopValueState::instance.attackInfo
                    .engineerBuildQueue[DAT_TroopValueState::instance.attackInfo.createTribeAmount]
                    .engineerCount = engineers;
                DAT_TroopValueState::instance.attackInfo.createTribeAmount
                    = DAT_TroopValueState::instance.attackInfo.createTribeAmount + 1;
                engineerTotal = engineerTotal + engineers;
            }
            DAT_TroopValueState::instance.attackInfo.tribeIDArraySize = 0;
            for (int tribeID = 1; tribeID < 1250; tribeID++) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState
                    && DAT_TribesState::instance.tribes[tribeID].owner == owner
                    && DAT_TribesState::instance.tribes[tribeID].attackWave == param_1
                    && DAT_TribesState::instance.tribes[tribeID].tribeType == AI::Tribes::AITT_ENGINEERS) {
                    DAT_TroopValueState::instance.attackInfo
                        .tribeIDArray[DAT_TroopValueState::instance.attackInfo.tribeIDArraySize] = tribeID;
                    DAT_TroopValueState::instance.attackInfo.tribeIDArraySize
                        = DAT_TroopValueState::instance.attackInfo.tribeIDArraySize + 1;
                }
            }
            if (!DAT_TroopValueState::instance.attackInfo.tribeIDArraySize) {
                return;
            }
            int engineerTribeID;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; i++) {
                engineerTribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                while (DAT_TribesState::instance.tribes[engineerTribeID].size && engineerTotal > 0) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(
                        engineerTribeID);
                    engineerTotal = engineerTotal - 1;
                }
            }
            int unitID = 0;
            for (int q = 0; q < DAT_TroopValueState::instance.attackInfo.createTribeAmount; q++) {
                int remaining = DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[q].engineerCount;
                int const tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.tribes[engineerTribeID].owner, 0);
                DAT_TribesState::instance.tribes[tribeID].tribeType = AI::Tribes::AITT_ENGINEERS;
                DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = 1040;
                DAT_TribesState::instance.tribes[tribeID].attackWave
                    = DAT_TribesState::instance.tribes[engineerTribeID].attackWave;
                DAT_TribesState::instance.tribes[tribeID].attackInfo_someCounter1
                    = DAT_TribesState::instance.tribes[engineerTribeID].attackInfo_someCounter1;
                for (; unitID < DAT_UnitsState::instance.maxUnitCount; unitID++) {
                    if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].owner == owner
                        && !DAT_UnitsState::instance.units[unitID].dying
                        && DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_E_ENGINEER
                        && !DAT_UnitsState::instance.units[unitID].tribeID) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            unitID, tribeID);
                        remaining = remaining - 1;
                        if (remaining <= 0) {
                            break;
                        }
                    }
                }
                if (unitID >= DAT_UnitsState::instance.maxUnitCount) {
                    return;
                }
                unitID = unitID + 1;
                if (unitID >= DAT_UnitsState::instance.maxUnitCount) {
                    return;
                }
                if (param_2) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::placeSiegeTentAtAttackAngle, this)(
                        tribeID, DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[q].engineerBuildingType);
                } else {
                    MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                        this)(tribeID,
                        DAT_TroopValueState::instance.attackInfo.engineerBuildQueue[q].engineerBuildingType, 0,
                        Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED);
                }
            }
        }

    }
}
}
