#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00457E80
    int GameStateStructures::getWallTilesThatCanBeBuilt(int playerID, int wallMaterial)
    {
        int wallTiles = 0;
        if (!DAT_GameCore::instance.solitaryAllBuildingsAreFree && DAT_GameCore::instance.gameMode_2 != GM_EDITOR) {
            if (DAT_GameCore::instance.gameMode_2 == GM_SIEGE_THAT) {
                return this->playerDataArray[playerID].startResources[Resources::RT_STONE];
            }
            if (wallMaterial == Resources::RT_STONE) {
                wallTiles = this->playerDataArray[playerID].currentResources[Resources::RT_STONE] * 2;
                if (this->playerDataArray[playerID].partialStoneCounter != 0) {
                    --wallTiles;
                }
            } else if (wallMaterial == Resources::RT_WOOD) {
                wallTiles = this->playerDataArray[playerID].currentResources[Resources::RT_WOOD] * 2;
                // this is the only leftover of the partial wood stuff from SH1
                if (this->playerDataArray[playerID].partialWoodCounter != 0) {
                    --wallTiles;
                }
            }
            if (wallTiles > 250) {
                return 250;
            }
        } else {
            wallTiles = 100;
        }
        return wallTiles;
    }

}
}
