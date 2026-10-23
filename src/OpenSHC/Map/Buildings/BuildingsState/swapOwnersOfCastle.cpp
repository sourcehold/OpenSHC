#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Buildings::BuildingLogicalState;

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
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].keep.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].keep.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].keep.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].keep.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].keep.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].keep.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].keep.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].keep.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].keep.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].keep.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].marketplace.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].marketplace.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].marketplace.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].marketplace.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].marketplace.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].marketplace.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].marketplace.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].marketplace.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].marketplace.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].marketplace.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].stockpile.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].stockpile.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].stockpile.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].stockpile.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].stockpile.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].stockpile.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].stockpile.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].stockpile.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].stockpile.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].stockpile.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].armory.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].armory.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].armory.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].armory.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].armory.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].armory.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].armory.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].armory.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].armory.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].armory.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].granary.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].granary.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].granary.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].granary.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].granary.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].granary.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].granary.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].granary.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].granary.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].granary.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].barracks.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].barracks.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].barracks.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].barracks.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].barracks.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].barracks.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].barracks.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].barracks.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].barracks.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].barracks.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].campground.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].campground.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].campground.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].campground.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].campground.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].campground.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].campground.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].campground.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].campground.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].campground.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)((int*)&DAT_GameState::instance.playerDataArray[param_2].unknown6.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].unknown6.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].unknown6.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].unknown6.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].unknown6.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].unknown6.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].unknown6.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].unknown6.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].unknown6.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].unknown6.areaEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.id,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.id);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.xEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.xEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.yEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.yEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.tileEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.tileEntry);
            MACRO_CALL(OpenSHC::IO_Func::SwapInts)(
                (int*)&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.areaEntry,
                (int*)&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.areaEntry);
        }

    }
}
}
