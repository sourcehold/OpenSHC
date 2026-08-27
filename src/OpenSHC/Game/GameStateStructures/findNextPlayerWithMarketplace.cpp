#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Player/PlayerData.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::Player::PlayerData;

    // FUNCTION: STRONGHOLDCRUSADER 0x00458700
    int GameStateStructures::findNextPlayerWithMarketplace(int param_1)
    {
        for (int iVar1 = param_1 + 1; iVar1 < 9; iVar1++) {
            if (0 < this->playerDataArray[iVar1].marketplace.id) {
                return iVar1;
            }
        }
        return 0;
    }

}
}
