#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC1C0
    void MapPropertiesState::spawnAttackWaveForPlayer(
        int playerID, int unitType1, int unitCount1, int unitType2, int unitCount2, undefined4 spawnParameterUnk)
    {
        int const signpostCount = DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter;
        int signpostIndex = 0;
        DAT_TroopValueState::instance.attackInfo.inv_count += 1;
        if (DAT_TroopValueState::instance.attackInfo.inv_count >= 50) {
            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
        }
        MACRO_CALL_MEMBER(Units::TroopValueState_Func::initializeAttackWaveSlot, DAT_TroopValueState::ptr)(
            DAT_TroopValueState::instance.attackInfo.inv_count, 0);
        DAT_TroopValueState::instance.attackInfo
            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = (byte)playerID;
        // fixme: an unknown unit type leaves these uninitialized (the original happens to hold the player ID)
        int tribeType;
        int unitType;
        int groupSizeDivisor;
        for (int group = 0; group < 2; ++group) {
            int requestedUnitType;
            int unitCount;
            if (group == 0) {
                requestedUnitType = unitType1;
                unitCount = unitCount1;
            } else {
                if (unitType2 <= 0) {
                    return;
                }
                requestedUnitType = unitType2;
                unitCount = unitCount2;
            }
            switch (requestedUnitType) {
            case 22:
                tribeType = 3;
                unitType = 22;
                groupSizeDivisor = 10;
                break;
            case 23:
                tribeType = 7;
                unitType = 23;
                groupSizeDivisor = 10;
                break;
            case 24:
                tribeType = 5;
                unitType = 24;
                groupSizeDivisor = 10;
                break;
            case 25:
                tribeType = 6;
                unitType = 25;
                groupSizeDivisor = 10;
                break;
            case 26:
                tribeType = 9;
                unitType = 26;
                groupSizeDivisor = 10;
                break;
            case 27:
                tribeType = 8;
                unitType = 27;
                groupSizeDivisor = 10;
                break;
            case 28:
                tribeType = 10;
                unitType = 28;
                groupSizeDivisor = 10;
                break;
            case 29:
                tribeType = 4;
                unitType = 29;
                groupSizeDivisor = 10;
                break;
            case 30:
                tribeType = 11;
                unitType = 30;
                groupSizeDivisor = 10;
                break;
            case 39:
                tribeType = 22;
                unitType = 39;
                groupSizeDivisor = 10;
                break;
            case 40:
                tribeType = 23;
                unitType = 40;
                groupSizeDivisor = 10;
                break;
            case 59:
                tribeType = 19;
                unitType = 59;
                groupSizeDivisor = 10;
                break;
            case 58:
                tribeType = 20;
                unitType = 58;
                groupSizeDivisor = 10;
                break;
            case 60:
                tribeType = 21;
                unitType = 60;
                groupSizeDivisor = 10;
                break;
            case 37:
                tribeType = 12;
                unitType = 37;
                groupSizeDivisor = 10;
                break;
            case 5:
                tribeType = 2;
                unitType = 5;
                groupSizeDivisor = 10;
                break;
            case 70:
                tribeType = 25;
                unitType = 70;
                groupSizeDivisor = 10;
                break;
            case 71:
                tribeType = 26;
                unitType = 71;
                groupSizeDivisor = 20;
                break;
            case 72:
                tribeType = 27;
                unitType = 72;
                groupSizeDivisor = 20;
                break;
            case 73:
                tribeType = 28;
                unitType = 73;
                groupSizeDivisor = 2;
                break;
            case 74:
                tribeType = 29;
                unitType = 74;
                groupSizeDivisor = 10;
                break;
            case 75:
                tribeType = 30;
                unitType = 75;
                groupSizeDivisor = 8;
                break;
            case 76:
                tribeType = 31;
                unitType = 76;
                groupSizeDivisor = 4;
                break;
            case 77:
                tribeType = 24;
                unitType = 77;
                groupSizeDivisor = 10;
                break;
            }
            int difficultyPercent = 100;
            switch (DAT_GameState::instance.mapAndTime.difficulty) {
            case 0:
                difficultyPercent = 50;
                break;
            case 2:
                difficultyPercent = 140;
                break;
            case 3:
                difficultyPercent = 200;
                break;
            }
            int remaining = difficultyPercent * unitCount / 100;
            if (tribeType == 22) {
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][0] += remaining;
            } else if (tribeType == 23) {
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][1] += remaining;
            } else if (tribeType == 19) {
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][2] += remaining;
            } else if (tribeType == 20) {
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][3] += remaining;
            } else if (tribeType == 21) {
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][4] += remaining;
            } else if (tribeType == 24) {
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][8] += remaining;
            } else {
                int groupSize = remaining / (remaining / groupSizeDivisor + 1);
                // a while loop: as a for loop with the subtraction as its step, the sub moves after the signpost update
                while (remaining > 0) {
                    if (groupSize > remaining) {
                        groupSize = remaining;
                    }
                    MACRO_CALL_MEMBER(Units::TribesState_Func::spawnUnitsForAITribe, DAT_TribesState::ptr)(
                        (AI::Tribes::AITribeType)tribeType,
                        DAT_GameState::instance.mapAndTime
                            .signpostsMapEdge[DAT_TroopValueState::instance.attackInfo
                                    .unknownSignpostRelatedArray[DAT_TroopValueState::instance.attackInfo.inv_count]]
                                             [signpostIndex]
                            .x,
                        DAT_GameState::instance.mapAndTime
                            .signpostsMapEdge[DAT_TroopValueState::instance.attackInfo
                                    .unknownSignpostRelatedArray[DAT_TroopValueState::instance.attackInfo.inv_count]]
                                             [signpostIndex]
                            .y,
                        playerID, (UnitType)unitType, groupSize, spawnParameterUnk);
                    remaining -= groupSize;
                    signpostIndex += 1;
                    if (signpostIndex >= signpostCount) {
                        signpostIndex = 0;
                    }
                }
            }
        }
    }

}
}
