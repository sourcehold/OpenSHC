#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459B50
    void GameStateStructures::playSFXNoSpaceInTheStockPile(int playerID)
    {
        if (playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }
        DWORD currentTime = timeGetTime();
        if ((this->playerDataArray[playerID].lastTimeSFXNoPlaceInStockpile == 0)
            || (currentTime - timeGetTime() > 9999)) {
            /*
              "No space in the stockpile"
             */
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("space_warning5.wav");
            this->playerDataArray[playerID].lastTimeSFXNoPlaceInStockpile = currentTime;
        }
    }
}
}
