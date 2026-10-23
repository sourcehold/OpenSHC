#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C190
        void BuildingsState::processWallBuildingLoss(int playerID, int highCount, int lowCount, int zero)
        {
            if (DAT_GameCore::instance.solitaryAllBuildingsAreFree != FALSE
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                DAT_TileMapState::instance.wallPlacementCost = highCount;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                    playerID, OpenSHC::Game::Resources::RT_STONE, highCount, zero);
                return;
            }

            // A low wall costs a quarter stone and a high wall half a stone, the remainder is kept for the next
            // placement. Note that partialStoneCounter is accessed as an int.
            int total = lowCount + highCount * 2
                + *(int*)&DAT_GameState::instance.playerDataArray[playerID].partialStoneCounter;
            if (zero == 0) {
                *(int*)&DAT_GameState::instance.playerDataArray[playerID].partialStoneCounter = total & 3;
            }
            int amount = total / 4;
            DAT_TileMapState::instance.wallPlacementCost = amount;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                playerID, OpenSHC::Game::Resources::RT_STONE, amount, zero);
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID && zero == 0 && amount != 0) {
                DAT_WallAndPitchState::instance.counter = amount;
                DAT_WallAndPitchState::instance.flag = zero;
            }
        }

    }
}
}
