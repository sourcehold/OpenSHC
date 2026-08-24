#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Player::PlayerData;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x00458700
    int GameStateStructures::findNextPlayerWithMarketplace(int param_1)

    {
        int iVar1;
        PlayerData* piVar2;

        iVar1 = param_1 + 1;
        if (iVar1 < 9) {
            piVar2 = &this->playerDataArray[param_1 + 1];
            do {
                if (0 < piVar2->marketplace.id) {
                    return iVar1;
                }
                iVar1 = iVar1 + 1;
                piVar2 = (PlayerData*)((int)(piVar2 + 0x172) + 0x24);
            } while (iVar1 < 9);
        }
        return 0;
    }

}
}
