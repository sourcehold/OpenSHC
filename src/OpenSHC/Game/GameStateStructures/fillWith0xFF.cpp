#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameStateStructures;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459BE0
    void GameStateStructures::fillWith0xFF()
    {
        // fixme: This could have just been a memset(-1) to the whole region
        for (int hotkeyEntry = 0; hotkeyEntry < 10; hotkeyEntry++) {
            for (int iVar2 = 0; iVar2 < 2500; iVar2++) {
                this->hotkeyTribes[hotkeyEntry].units[iVar2].id = -1;
                this->hotkeyTribes[hotkeyEntry].units[iVar2].uid = -1;
            }
        }
    }

}
}
