#include "../../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnknownStopwatch.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005202B0
        void TroopValueState::aiRecomputeAttacks(undefined4 param_1, int param_2)
        {
            int iVar3;
            int playerID = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_2];
            MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::start, DAT_UnknownStopwatch::ptr)();
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].currentPlayerID_OR_attackedPlayerID_OR_one
                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x13a10, '\0', (void*)((int)(DAT_TileMapState::instance.AIZoneLayer)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x13a10, '\0', (void*)((int)(DAT_TileMapState::instance.AIInfoLayer)));
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recountAttackTroopValue, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeAttackWaveTroopComposition, this)();
            int iVar2 = DAT_GameState::instance.mapAndTime.signpostEntryData[0].tile;
            iVar3
                = DAT_GameState::instance.mapAndTime
                      .signpostEntryData[DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[param_2]]
                      .tile;
            if (iVar3 < 1) {
                DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[param_2] = 0;
                iVar3 = iVar2;
            }
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeAIZoneLayer, DAT_PathFindingState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, 1,
                (int)((short)DAT_TileMapState::instance.PathConnectionLayer[iVar3]));
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
                DAT_PathFindingState::ptr)(60, 0, 0, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackZoneSearch, this)(param_2);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recomputeTargetedBuildingTilesArray, this)(
                DAT_TroopValueState::instance.attackInfo.attacker);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recomputeAttackInfo, this)(
                DAT_TroopValueState::instance.attackInfo.attacker,
                (int)(DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1]
                        .currentPlayerID_OR_attackedPlayerID_OR_one));
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeSiegeSpotScores, this)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID,
                DAT_TroopValueState::instance.attackInfo.attacker);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setScale3, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setTown2, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailablePeopleValueSlots, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailableLordValueSlots, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setGate2, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setWide3, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setMoat3, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailableHighValueSlots, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailableArcherValueSlots, this)(1);
            if (DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle < 1) {
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::calculateAttackVectorsToCampFireOfPlayer,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle = 1;
            }
            DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle
                = DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle + 1;
            if (1 < DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle) {
                DAT_TroopValueState::instance.attackInfo.attackVectorRecomputeThrottle = 0;
            }
            MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::stop, DAT_UnknownStopwatch::ptr)();
        }

    }
}
}
