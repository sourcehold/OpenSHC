#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518180
        void TroopValueState::initializeAttackWaveSlot(int param_1, int param_2)
        {
            int iVar1;
            int iVar2;
            this->attackInfo.value3Array01[param_1] = 0;
            this->attackInfo.attackWaveTicker[param_1] = 0;
            this->attackInfo.someIntArray2[param_1 + -1] = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                10, '\0', (void*)((int)(this->attackInfo.someSinglePlayerScore + param_1)));
            this->attackInfo.aiTickPhase = 0;
            this->attackInfo.counter = 0x10;
            this->attackInfo.field_0x20e00 = 0xffffffff;
            this->attackInfo.field128057_0x469d8 = 0;
            this->attackInfo.buildingDamageEventCount = 0;
            this->attackInfo.enemyUnitsInsideCastleCount = 0;
            this->attackInfo.playerInfo[0].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[0].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[1].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[1].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[2].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[2].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[3].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[3].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[4].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[4].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[5].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[5].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[6].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[6].field_0x3ea8 = 0;
            this->attackInfo.playerInfo[7].field22_0x3ea4 = 0;
            this->attackInfo.playerInfo[7].field_0x3ea8 = 0;
            iVar1 = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry, DAT_GameState::ptr)();
            iVar2 = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::countActiveSignposts, DAT_GameState::ptr)();
            if ((param_2 <= iVar2) && (param_2)) {
                (&this->attackInfo.unknownSignpostRelatedArray)[param_1] = param_2 + -1;
                this->attackInfo.field128056_0x469d4 = param_2 + -1;
            }
            (&this->attackInfo.unknownSignpostRelatedArray)[param_1] = iVar1;
            this->attackInfo.field128056_0x469d4 = iVar1;
        }

    }
}
}
