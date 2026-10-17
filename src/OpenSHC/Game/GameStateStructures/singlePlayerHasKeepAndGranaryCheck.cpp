#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004595D0
    int GameStateStructures::singlePlayerHasKeepAndGranaryCheck()
    {
        int currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return 1;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            return 1;
        }
        if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL))
            && (currentPlayerSlotID == 2)) {
            return 1;
        }
        if (this->mapAndTime.singlePlayerHasKeepAndGranary != FALSE) {
            return 1;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
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
