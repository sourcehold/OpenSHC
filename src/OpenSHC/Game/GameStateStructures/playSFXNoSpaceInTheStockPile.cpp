#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459B50
    void GameStateStructures::playSFXNoSpaceInTheStockPile(int playerID)
    {
        if (playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }
        DWORD const currentTime = timeGetTime();
        if (this->playerDataArray[playerID].lastTimeSFXNoPlaceInStockpile == 0
            || currentTime - timeGetTime() >= 10000) {
            // "No space in the stockpile"
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_space_warning5_wav_005a50b0);
            this->playerDataArray[playerID].lastTimeSFXNoPlaceInStockpile = currentTime;
        }
    }

}
}
