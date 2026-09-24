#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameStateStructures;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459BE0
    void GameStateStructures::fillWith0xFF()
    {
        for (int hotkeyID = 0; hotkeyID < 10; ++hotkeyID) {
            for (int i = 0; i < 2500; ++i) {
                this->hotkeyTribes[hotkeyID].units[i].id = -1;
                this->hotkeyTribes[hotkeyID].units[i].uid = -1;
            }
        }
    }

}
}
