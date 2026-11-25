#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458700
    int GameStateStructures::findNextPlayerWithMarketplace(int playerID)
    {
        for (int nextPlayerID = playerID + 1; nextPlayerID < 9; ++nextPlayerID) {
            if (this->playerDataArray[nextPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                    .id
                > 0) {
                return nextPlayerID;
            }
        }
        return 0;
    }

}
}
