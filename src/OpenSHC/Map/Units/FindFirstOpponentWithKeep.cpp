#include "../Units.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/MapType2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0051BE20
    int Units::FindFirstOpponentWithKeep()
    {
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
            && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
            return 1;
        }
        for (int playerID = 2; playerID < 6; ++playerID) {
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                    .id
                > 0) {
                return playerID;
            }
        }
        return 0;
    }

}
}
