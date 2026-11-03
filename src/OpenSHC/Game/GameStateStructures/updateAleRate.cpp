#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458D50
    void GameStateStructures::updateAleRate()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_KEEP].id > 0
                && this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_CAMPGROUND].id > 0) {
                this->playerDataArray[playerID].aleRate = 36;
            }
        }
    }

}
}
