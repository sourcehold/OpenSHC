#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004595D0
    int GameStateStructures::singlePlayerHasKeepAndGranaryCheck()
    {
        int currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if (DAT_GameCore::instance.gameMode_2 == GM_EDITOR) {
            return 1;
        }
        if (DAT_GameCore::instance.gameMode_2 == GM_SIEGE_THAT) {
            return 1;
        }
        if ((DAT_GameCore::instance.gameMode_2 == GM_BUILDERUnk
                || DAT_GameCore::instance.gameMode_2 == GM_CRUSADER_TUTORIAL)
            && currentPlayerSlotID == 2) {
            return 1;
        }
        if (this->mapAndTime.singlePlayerHasKeepAndGranary) {
            return 1;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY) {
            return 1;
        }
        if (this->playerDataArray[currentPlayerSlotID].keep.id == 0) {
            return 0;
        }
        if (this->playerDataArray[currentPlayerSlotID].granary.id == 0) {
            return -1;
        }
        this->mapAndTime.singlePlayerHasKeepAndGranary = TRUE;
        return 1;
    }

}
}
