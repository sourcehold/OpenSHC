#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/State/UnitSelectionHotKeyEntry.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::State::UnitSelectionHotKeyEntry;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459BB0
    void GameStateStructures::clearTribeHotKey(int hotkeyID)
    {
        for (int iVar2 = 0; iVar2 < 2500; iVar2++) {
            this->hotkeyTribes[hotkeyID].units[iVar2].id = -1;
            this->hotkeyTribes[hotkeyID].units[iVar2].uid = -1;
        }
    }

}
}
