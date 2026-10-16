#include "../../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005200A0
        void TroopValueState::aiRecomputeAttacks2(int param_1, int param_2)
        {
            int* piVar1;
            int iVar2;
            BOOLEnum BVar3;
            int iVar4;
            int playerID;
            playerID = (int)(char)DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_2];
            BVar3 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::canKeepReachSignpostZone,
                DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, playerID, param_2);
            MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::start, DAT_UnknownStopwatch::ptr)();
            piVar1 = (int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc + -0x10);
            *piVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x13a10, '\0', (void*)((int)(DAT_TileMapState::instance.AIZoneLayer)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x13a10, '\0', (void*)((int)(DAT_TileMapState::instance.AIInfoLayer)));
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recountAttackTroopValue, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeAttackWaveTroopComposition, this)();
            iVar2 = DAT_GameState::instance.mapAndTime.signpostEntryData[0].tile;
            DAT_TroopValueState::instance.attackInfo.field127625_0x42744 = 0;
            iVar4 = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[(
                            &DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray)[param_2]]
                        .tile;
            if (iVar4 < 1) {
                (&DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray)[param_2] = 0;
                iVar4 = iVar2;
            }
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeAIZoneLayer, DAT_PathFindingState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)((int)((uint)(BVar3))),
                (int)((int)((short)DAT_TileMapState::instance.PathConnectionLayer[iVar4])));
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
                DAT_PathFindingState::ptr)(90, 0, 0, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackZoneSearch, this)(param_2);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recomputeTargetedBuildingTilesArray, this)(
                DAT_TroopValueState::instance.attackInfo.attacker);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recomputeAttackInfo, this)(
                DAT_TroopValueState::instance.attackInfo.attacker, (int)((int)(*piVar1)));
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
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::expandAIZoneLayerStage1, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::expandAIZoneLayerStage2, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::expandAIZoneLayerStage3, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::clearAIInfoLayerOutsideStartZone, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::scanForArcherPoints, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::pruneStaleArcherPoints, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::scanForSupportPoints, this)();
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::pruneStaleSupportPoints, this)();
            if (param_1) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::scanForSiegeTentPoints, this)();
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::pruneStaleTentPoints, this)();
            }
            MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::stop, DAT_UnknownStopwatch::ptr)();
        }

    }
}
}
