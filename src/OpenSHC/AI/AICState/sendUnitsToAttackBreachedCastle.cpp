#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D30E0
    undefined4 AICState::sendUnitsToAttackBreachedCastle(int attackingPlayerIndex)
    {
        int vector = 0;
        if (DAT_GameState::instance.playerDataArray[attackingPlayerIndex].aiType == OpenSHC::AI::AIT_NULL) {
            return 1;
        }

        BOOLEnum sentUnitsToAttackLord = FALSE;
        int defendingLordID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
            DAT_UnitsState::ptr)(DAT_GameState::instance.playerDataArray[attackingPlayerIndex].attackedPlayerID);

        for (int i = 0; i < 11; i++) {
            int tribeType = DAT_SkirmishDefinedData::instance.MaxBreachTribes[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxBreachTribes[i].tribeCount;
            if (tribeType == 18 || tribeType == 14 || tribeType == 13) {
                continue;
            }

            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[attackingPlayerIndex].aiTribeIDs[tribeType + j];
                if (tribeID == 0) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[attackingPlayerIndex].aiTribeUIDs[j + tribeType]) {
                    continue;
                }

                int targetUnitID = (short)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
                DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;

                if (sentUnitsToAttackLord != FALSE || defendingLordID == 0 || tribeType == 186) {
                    if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::giveSomeRaidCommand, this)(tribeID, tribeType)
                        != 0) {
                        continue;
                    }

                    if (tribeType == 186) {
                        vector += 4;
                    }
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = OpenSHC::Map::Units::STBT_8;
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                    int attackedPlayerID
                        = DAT_GameState::instance.playerDataArray[attackingPlayerIndex].attackedPlayerID;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                        DAT_UnitsState::instance.units[targetUnitID].y,
                        DAT_GameState::instance.mapAndTime.attackVectors[attackedPlayerID][vector].x,
                        DAT_GameState::instance.mapAndTime.attackVectors[attackedPlayerID][vector].y);

                    if (DAT_DirectionAlgorithmState::instance.distanceHigh > 4) {
                        attackedPlayerID
                            = DAT_GameState::instance.playerDataArray[attackingPlayerIndex].attackedPlayerID;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, DAT_GameState::instance.mapAndTime.attackVectors[attackedPlayerID][vector].x,
                            DAT_GameState::instance.mapAndTime.attackVectors[attackedPlayerID][vector].y, 0, 0,
                            OpenSHC::Map::Units::Instructions::UMSE_0);
                    }
                    vector += 1;
                } else {
                    // Send units to attack lord
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            tribeID, DAT_UnitsState::instance.units[defendingLordID].x,
                            DAT_UnitsState::instance.units[defendingLordID].y, 0, 0,
                            OpenSHC::Map::Units::Instructions::UMSE_0)
                        == 0) {
                        return 0;
                    }
                    sentUnitsToAttackLord = TRUE;
                }
            }
        }

        return 1;
    }

}
}
