#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CCB0
        void TroopValueState::assignMacemenAndKnightsNotFromPlayer1ToTribes()
        {
            int const playerID = DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID;
            int macemenCount = 0;
            int knightCount = 0;
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_INVISIBLE
                    || MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                           DAT_UnitsState::instance.units[unitID].owner)
                        == FALSE) {
                    continue;
                }
                if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_MACE) {
                    ++macemenCount;
                } else if (DAT_UnitsState::instance.units[unitID].unitType == UT_E_KNIGHT) {
                    ++knightCount;
                } else {
                    continue;
                }
                MACRO_CALL_MEMBER(TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].tribeID);
            }

            int macemenPerTribe;
            if (macemenCount > 40) {
                macemenPerTribe = 10;
            } else if (macemenCount > 20) {
                macemenPerTribe = 8;
            } else {
                macemenPerTribe = 5;
            }
            int knightsPerTribe;
            if (knightCount > 18) {
                knightsPerTribe = 6;
            } else {
                knightsPerTribe = knightCount > 12 ? 4 : 2;
            }

            if (macemenCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 0;
            } else if (macemenCount <= macemenPerTribe) {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 1;
            } else {
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount = macemenCount / macemenPerTribe + 1;
                if (DAT_TroopValueState::instance.attackInfo.macemenTribeCount > 100) {
                    DAT_TroopValueState::instance.attackInfo.macemenTribeCount = 100;
                }
            }
            if (knightCount <= 0) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 0;
            } else if (knightCount <= knightsPerTribe) {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = 1;
            } else {
                DAT_TroopValueState::instance.attackInfo.knightTribeCount = knightCount / knightsPerTribe + 1;
                if (DAT_TroopValueState::instance.attackInfo.knightTribeCount > 100) {
                    DAT_TroopValueState::instance.attackInfo.knightTribeCount = 100;
                }
            }

            // the unit scan continues across tribes and is not bounded by maxUnitCount (original behaviour)
            int unitID = 0;
            for (int tribeIdx = 0; tribeIdx < DAT_TroopValueState::instance.attackInfo.macemenTribeCount;) {
                int const tribeID = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
                DAT_TroopValueState::instance.attackInfo.macemenTribeArray[tribeIdx] = tribeID;
                DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_MACEMEN;
                for (int added = 0; added < macemenPerTribe;) {
                    ++unitID;
                    if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                        && MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                               DAT_UnitsState::instance.units[unitID].owner)
                            != FALSE
                        && DAT_UnitsState::instance.units[unitID].unitType == UT_E_MACE) {
                        MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
                        if (--macemenCount <= 0) {
                            break;
                        }
                        ++added;
                    }
                }
                if (macemenCount <= 0) {
                    break;
                }
                ++tribeIdx;
            }

            unitID = 0;
            for (int tribeIdx = 0; tribeIdx < DAT_TroopValueState::instance.attackInfo.knightTribeCount;) {
                int const tribeID = MACRO_CALL_MEMBER(TribesState_Func::createTribe, DAT_TribesState::ptr)(playerID, 0);
                DAT_TroopValueState::instance.attackInfo.knightTribeArray[tribeIdx] = tribeID;
                DAT_TribesState::instance.tribes[tribeID].tribeType = OpenSHC::AI::Tribes::AITT_KNIGHTS;
                for (int added = 0; added < knightsPerTribe;) {
                    ++unitID;
                    if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_INVISIBLE
                        && MACRO_CALL_MEMBER(TroopValueState_Func::getPlayerNot1AndHasKeep, this)(
                               DAT_UnitsState::instance.units[unitID].owner)
                            != FALSE
                        && DAT_UnitsState::instance.units[unitID].unitType == UT_E_KNIGHT) {
                        MACRO_CALL_MEMBER(TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
                        if (--knightCount <= 0) {
                            break;
                        }
                        ++added;
                    }
                }
                if (knightCount <= 0) {
                    break;
                }
                ++tribeIdx;
            }
        }

    }
}
}
