#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C190
        void BuildingsState::processWallBuildingLoss(int playerID, int highCount, int lowCount, int zero)
        {
            if (DAT_GameCore::instance.solitaryAllBuildingsAreFree != 0) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == 1) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == 6) {
                DAT_TileMapState::instance.wallPlacementCost = highCount;
                MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                    playerID, Game::Resources::RT_STONE, highCount, zero);
                return;
            }
            int const total
                = lowCount + highCount * 2 + DAT_GameState::instance.playerDataArray[playerID].partialStoneCounter;
            if (zero == 0) {
                DAT_GameState::instance.playerDataArray[playerID].partialStoneCounter = total & 3;
            }
            int const stoneCost = total / 4;
            DAT_TileMapState::instance.wallPlacementCost = stoneCost;
            MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                playerID, Game::Resources::RT_STONE, stoneCost, zero);
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID && zero == 0 && stoneCost != 0) {
                DAT_WallAndPitchState::instance.counter = stoneCost;
                DAT_WallAndPitchState::instance.flag = 0;
            }
        }

    }
}
}
