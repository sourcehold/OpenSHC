#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode2;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C9F0
        void BuildingsState::subtractPitchAndMoatFromStartingGoldInSiegeThatMode()
        {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                return;
            }

            int pitchDitchCount = 0;
            for (int i = 1; i < 4000; ++i) {
                if (DAT_TileMapState::instance.pitchDitches[i].owner != 0) {
                    ++pitchDitchCount;
                }
            }

            // Only the tiles placed since the last call are paid
            int stone;
            int gold;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, this)(
                OpenSHC::Commands::M_MAPPER_MOAT, &stone, &gold);
            int moatTileCount = DAT_TileMapState::instance.moatTileCount;
            int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[playerID].startResources[OpenSHC::Game::Resources::RT_GOLD]
                -= (moatTileCount - DAT_GameState::instance.playerDataArray[playerID].moatTileCount) * gold;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, this)(
                OpenSHC::Commands::M_MAPPER_PITCH_DITCH, &stone, &gold);
            DAT_GameState::instance.playerDataArray[playerID].startResources[OpenSHC::Game::Resources::RT_GOLD]
                -= (pitchDitchCount - DAT_GameState::instance.playerDataArray[playerID].pitchDitchTileCount) * gold;
            DAT_GameState::instance.playerDataArray[playerID].pitchDitchTileCount = pitchDitchCount;
            DAT_GameState::instance.playerDataArray[playerID].moatTileCount = moatTileCount;
        }

    }
}
}
