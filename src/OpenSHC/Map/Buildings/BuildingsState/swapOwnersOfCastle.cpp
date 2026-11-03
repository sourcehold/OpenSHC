#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Buildings::BuildingLogicalState;

        using OpenSHC::Game::Player::Enums::BEIE_ARMORY;
        using OpenSHC::Game::Player::Enums::BEIE_BARRACKS;
        using OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND;
        using OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD;
        using OpenSHC::Game::Player::Enums::BEIE_GRANARY;
        using OpenSHC::Game::Player::Enums::BEIE_KEEP;
        using OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE;
        using OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST;
        using OpenSHC::Game::Player::Enums::BEIE_OILSMELTER;
        using OpenSHC::Game::Player::Enums::BEIE_STOCKPILE;
        using OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD;
        using OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041A8D0
        void BuildingsState::swapOwnersOfCastle(int param_1, int param_2)
        {
            // Swaps all buildings of the players param_1 and param_2
            int swapped = 0;
            for (int i = 1; i < 2000; ++i) {
                if (this->buildings[i].logicalState != BLS_NORMAL) {
                    continue;
                }
                if (this->buildings[i].owner == param_1) {
                    this->buildings[i].owner = param_2;
                    swapped = 1;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        this->buildings[i].playerColorUnk = param_2;
                    }
                } else if (this->buildings[i].owner == param_2) {
                    this->buildings[i].owner = param_1;
                    swapped = 1;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        this->buildings[i].playerColorUnk = param_1;
                    }
                }
            }
            if (swapped <= 0) {
                return;
            }

            // Swap the special buildings as well
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_KEEP].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_KEEP].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_KEEP].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_KEEP].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_KEEP].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_KEEP].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_KEEP].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_KEEP].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_KEEP].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_KEEP].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MARKETPLACE].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MARKETPLACE].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MARKETPLACE].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MARKETPLACE].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MARKETPLACE].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MARKETPLACE].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MARKETPLACE].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MARKETPLACE].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MARKETPLACE].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MARKETPLACE].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ENGINEERSGUILD].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ENGINEERSGUILD].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ENGINEERSGUILD].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ENGINEERSGUILD].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ENGINEERSGUILD].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ENGINEERSGUILD].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ENGINEERSGUILD].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ENGINEERSGUILD].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ENGINEERSGUILD].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ENGINEERSGUILD].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_TUNNELERSGUILD].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_TUNNELERSGUILD].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_TUNNELERSGUILD].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_TUNNELERSGUILD].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_TUNNELERSGUILD].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_TUNNELERSGUILD].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_TUNNELERSGUILD].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_TUNNELERSGUILD].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_TUNNELERSGUILD].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_TUNNELERSGUILD].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_STOCKPILE].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_STOCKPILE].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_STOCKPILE].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_STOCKPILE].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_STOCKPILE].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_STOCKPILE].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_STOCKPILE].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_STOCKPILE].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_STOCKPILE].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_STOCKPILE].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ARMORY].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ARMORY].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ARMORY].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ARMORY].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ARMORY].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ARMORY].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ARMORY].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ARMORY].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_ARMORY].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_ARMORY].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_GRANARY].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_GRANARY].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_GRANARY].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_GRANARY].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_GRANARY].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_GRANARY].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_GRANARY].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_GRANARY].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_GRANARY].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_GRANARY].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_BARRACKS].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_BARRACKS].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_BARRACKS].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_BARRACKS].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_BARRACKS].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_BARRACKS].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_BARRACKS].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_BARRACKS].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_BARRACKS].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_BARRACKS].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MERCENARYPOST].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MERCENARYPOST].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MERCENARYPOST].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MERCENARYPOST].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MERCENARYPOST].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MERCENARYPOST].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MERCENARYPOST].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MERCENARYPOST].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_MERCENARYPOST].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_MERCENARYPOST].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_CAMPGROUND].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_CAMPGROUND].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_CAMPGROUND].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_CAMPGROUND].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_CAMPGROUND].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_CAMPGROUND].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_CAMPGROUND].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_CAMPGROUND].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_CAMPGROUND].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_CAMPGROUND].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_UNKNOWN6].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_UNKNOWN6].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_UNKNOWN6].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_UNKNOWN6].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_UNKNOWN6].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_UNKNOWN6].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_UNKNOWN6].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_UNKNOWN6].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_UNKNOWN6].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_UNKNOWN6].areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_OILSMELTER].id,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_OILSMELTER].id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_OILSMELTER].xEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_OILSMELTER].xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_OILSMELTER].yEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_OILSMELTER].yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_OILSMELTER].tileEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_OILSMELTER].tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                &DAT_GameState::instance.playerDataArray[param_2].buildingEntryInfos[BEIE_OILSMELTER].areaEntry,
                &DAT_GameState::instance.playerDataArray[param_1].buildingEntryInfos[BEIE_OILSMELTER].areaEntry);
        }

    }
}
}
