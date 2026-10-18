#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518180
        void TroopValueState::initializeAttackWaveSlot(int param_1, int param_2)
        {
            int _randomSignpost;
            DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 0;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 0;
            DAT_TroopValueState::instance.attackInfo.someIntArray2[param_1 + -1] = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore[param_1]), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore + param_1)));
            DAT_TroopValueState::instance.attackInfo.aiTickPhase = 0;
            DAT_TroopValueState::instance.attackInfo.counter = 0x10;
            DAT_TroopValueState::instance.attackInfo.archerPointCountPrev = 0xffffffff;
            DAT_TroopValueState::instance.attackInfo.delayedWaveAssignmentCount = 0;
            DAT_TroopValueState::instance.attackInfo.buildingDamageEventCount = 0;
            DAT_TroopValueState::instance.attackInfo.enemyUnitsInsideCastleCount = 0;
            for (int _player = 0; _player < 8; ++_player) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[_player].field22_0x3ea4 = 0;
                DAT_TroopValueState::instance.attackInfo.playerInfo[_player].field_0x3ea8 = 0;
            }
            _randomSignpost = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry, DAT_GameState::ptr)();
            int _activeSignposts
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::countActiveSignposts, DAT_GameState::ptr)();
            if ((param_2 <= _activeSignposts) && (param_2)) {
                DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[param_1] = param_2 + -1;
                DAT_TroopValueState::instance.attackInfo.field121388_0x469d4 = param_2 + -1;
                return;
            }
            DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray[param_1] = _randomSignpost;
            DAT_TroopValueState::instance.attackInfo.field121388_0x469d4 = _randomSignpost;
        }

    }
}
}
