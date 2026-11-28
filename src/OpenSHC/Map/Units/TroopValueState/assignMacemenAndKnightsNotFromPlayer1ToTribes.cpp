#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CCB0
        void TroopValueState::assignMacemenAndKnightsNotFromPlayer1ToTribes()
        {
            int const playerID = DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID;
            int macemenCount = 0;
            int knightCount = 0;
            for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; unitID++) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_INVISIBLE
                    || !MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                        DAT_UnitsState::instance.units[unitID].owner)) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_E_MACE) {
                    macemenCount = macemenCount + 1;
                } else if (DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_E_KNIGHT) {
                    knightCount = knightCount + 1;
                } else {
                    continue;
                }
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].tribeID);
            }
            int macemenLimit;
            if (macemenCount > 40) {
                macemenLimit = 10;
            } else if (macemenCount > 20) {
                macemenLimit = 8;
            } else {
                macemenLimit = 5;
            }
            int knightLimit;
            if (knightCount > 18) {
                knightLimit = 6;
            } else {
                knightLimit = (knightCount > 12) * 2 + 2;
            }
            if (macemenCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 0;
            } else if (macemenCount <= macemenLimit) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 1;
            } else {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = macemenCount / macemenLimit + 1;
                if (DAT_TroopValueState::instance.attackInfo.macemenTribeCount > 100) {
                    DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 100;
                }
            }
            if (knightCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 0;
            } else if (knightCount <= knightLimit) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 1;
            } else {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = knightCount / knightLimit + 1;
                if (DAT_TroopValueState::instance.attackInfo.knightTribeCount > 100) {
                    DAT_TroopValueState::instance.attackInfo.knightTribeCount = 100;
                }
            }
            int macemenUnitID = 0;
            for (int tribeIndex = 0; tribeIndex < DAT_TroopValueState::instance.attackInfo.macemenTribeCount;
                tribeIndex++) {
                int const tribeID
                    = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
                DAT_TroopValueState::instance.attackInfo.macemenTribeArray[tribeIndex] = tribeID;
                DAT_TribesState::instance.tribes[tribeID].tribeType = AI::Tribes::AITT_MACEMEN;
                for (int assigned = 0; assigned < macemenLimit;) {
                    macemenUnitID = macemenUnitID + 1;
                    if (DAT_UnitsState::instance.units[macemenUnitID].logicalState != Map::Units::ULS_INVISIBLE
                        && MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                            DAT_UnitsState::instance.units[macemenUnitID].owner)
                        && DAT_UnitsState::instance.units[macemenUnitID].unitType == Map::Units::UT_E_MACE) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            macemenUnitID, tribeID);
                        macemenCount = macemenCount - 1;
                        if (macemenCount <= 0) {
                            break;
                        }
                        assigned = assigned + 1;
                    }
                }
                if (macemenCount <= 0) {
                    break;
                }
            }
            int knightUnitID = 0;
            for (int tribeIndex = 0; tribeIndex < DAT_TroopValueState::instance.attackInfo.knightTribeCount;
                tribeIndex++) {
                int const tribeID
                    = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
                DAT_TroopValueState::instance.attackInfo.knightTribeArray[tribeIndex] = tribeID;
                DAT_TribesState::instance.tribes[tribeID].tribeType = AI::Tribes::AITT_KNIGHTS;
                for (int assigned = 0; assigned < knightLimit;) {
                    knightUnitID = knightUnitID + 1;
                    if (DAT_UnitsState::instance.units[knightUnitID].logicalState != Map::Units::ULS_INVISIBLE
                        && MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                            DAT_UnitsState::instance.units[knightUnitID].owner)
                        && DAT_UnitsState::instance.units[knightUnitID].unitType == Map::Units::UT_E_KNIGHT) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            knightUnitID, tribeID);
                        knightCount = knightCount - 1;
                        if (knightCount <= 0) {
                            return;
                        }
                        assigned = assigned + 1;
                    }
                }
                if (knightCount <= 0) {
                    break;
                }
            }
        }

    }
}
}
