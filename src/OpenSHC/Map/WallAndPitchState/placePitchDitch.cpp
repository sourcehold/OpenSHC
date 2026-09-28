#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500DD0
    void WallAndPitchState::placePitchDitch(int pitchID)
    {
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
            if (this->countdown == 0) {
                this->countdown = 400;
                this->index = 0;
                this->counter = 0;
            }
            if (this->index < 100) {
                this->wallPlacementInfoArray[this->index].tile_OR_pitchID = pitchID;
                this->index = this->index + 1;
                this->counter = this->counter + 1;
                this->countdown = 400;
            }
        }
        return;
    }

}
}
