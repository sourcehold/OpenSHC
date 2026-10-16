#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::MapType2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BDE0
        BOOLEnum TroopValueState::getPlayerNot1AndHasKeep(int playerID)
        {
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                if (playerID != 1) {
                    return FALSE;
                }
            } else {
                if (playerID == 1) {
                    return FALSE;
                }
                if (DAT_GameState::instance.playerDataArray[playerID].keep.id < 1) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
