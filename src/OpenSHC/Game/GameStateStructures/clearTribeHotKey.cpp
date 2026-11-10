#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

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
