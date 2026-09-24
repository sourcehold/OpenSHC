#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/State/UnitSelectionHotKeyEntry.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::State::UnitSelectionHotKeyEntry;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459BB0
    void GameStateStructures::clearTribeHotKey(int hotkeyID)
    {
        for (int i = 0; i < 2500; ++i) {
            this->hotkeyTribes[hotkeyID].units[i].id = -1;
            this->hotkeyTribes[hotkeyID].units[i].uid = -1;
        }
    }

}
}
