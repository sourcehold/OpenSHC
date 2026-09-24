#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C1A0
        uint BuildingsState::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters(int playerID, int param_2)
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT || param_2 != 3) {
                return 0;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingOfType, this)(
                    playerID, BT_WOODCUTTERSHUT)
                != 0) {
                return 0;
            }
            return DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_WOOD]
                < this->buildingCosts[BT_WOODCUTTERSHUT].requiredWood;
        }

    }
}
}
