#include "../GameStateStructures.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00455D40
    void GameStateStructures::clearMapAndTimeAndPlayerData()
    {
        for (int playerID = 0; playerID < 9; ++playerID) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->playerDataArray[playerID]), '\0', &this->playerDataArray[playerID]);
        }
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(DAT_GameState::instance.mapAndTime), '\0', &DAT_GameState::instance.mapAndTime);
    }

}
}
