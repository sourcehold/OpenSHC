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
#include "OpenSHC/Globals/DAT_UnknownStopwatch.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005202B0
        void TroopValueState::aiRecomputeAttacks(undefined4 param_1, int param_2)
        {
            int* piVar1;
            int iVar2;
            int iVar3;
            int playerID;
            playerID = (int)(char)this->attackInfo.attackWavePlayerIDArray[param_2];
            MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::start, DAT_UnknownStopwatch::ptr)();
            piVar1 = (int*)((int)this->attackInfo.hackValuesArray + playerID * 0x177bc + -0x10);
            *piVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x13a10, '\0', (void*)((int)(DAT_TileMapState::instance.AIZoneLayer)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x13a10, '\0', (void*)((int)(DAT_TileMapState::instance.AIInfoLayer)));
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recountAttackTroopValue, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeAttackWaveTroopComposition, this)();
            iVar2 = DAT_GameState::instance.mapAndTime.signpostEntryData[0].tile;
            iVar3 = DAT_GameState::instance.mapAndTime
                        .signpostEntryData[(&this->attackInfo.unknownSignpostRelatedArray)[param_2]]
                        .tile;
            if (iVar3 < 1) {
                (&this->attackInfo.unknownSignpostRelatedArray)[param_2] = 0;
                iVar3 = iVar2;
            }
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
                DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 1,
                (int)((int)((short)DAT_TileMapState::instance.PathConnectionLayer[iVar3])));
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
                DAT_PathFindingState::ptr)(60, 0, 0, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackZoneSearch, this)(param_2);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recomputeTargetedBuildingTilesArray, this)(
                this->attackInfo.attacker);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::recomputeAttackInfo, this)(
                this->attackInfo.attacker, (int)((int)(*piVar1)));
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::computeSiegeSpotScores, this)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, this->attackInfo.attacker);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setScale3, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setTown2, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailablePeopleValueSlots, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailableLordValueSlots, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setGate2, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setWide3, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::setMoat3, this)(1, playerID);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailableHighValueSlots, this)(1);
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::countAvailableArcherValueSlots, this)(1);
            if (this->attackInfo.attackVectorRecomputeThrottle < 1) {
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::calculateAttackVectorsToCampFireOfPlayer,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                this->attackInfo.attackVectorRecomputeThrottle = 1;
            }
            this->attackInfo.attackVectorRecomputeThrottle = this->attackInfo.attackVectorRecomputeThrottle + 1;
            if (1 < this->attackInfo.attackVectorRecomputeThrottle) {
                this->attackInfo.attackVectorRecomputeThrottle = 0;
            }
            MACRO_CALL_MEMBER(Util::Timing::Stopwatch_Func::stop, DAT_UnknownStopwatch::ptr)();
        }

    }
}
}
