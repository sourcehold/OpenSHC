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

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A4E0
        void BuildingsState::copyPlayerDataArrayValues(int playerID, int playerID2)
        {
            // Transfers all buildings of playerID to playerID2
            int changed = 0;
            for (int i = 1; i < 2000; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].owner == playerID) {
                    this->buildings[i].owner = playerID2;
                    changed = 1;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        this->buildings[i].playerColorUnk = playerID2;
                    }
                }
            }
            if (changed <= 0) {
                return;
            }

            // Move the special buildings over as well
            DAT_GameState::instance.playerDataArray[playerID2].keep.id
                = DAT_GameState::instance.playerDataArray[playerID].keep.id;
            DAT_GameState::instance.playerDataArray[playerID2].keep.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].keep.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].keep.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].keep.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].keep.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].keep.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].keep.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].keep.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].keep.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].marketplace.id
                = DAT_GameState::instance.playerDataArray[playerID].marketplace.id;
            DAT_GameState::instance.playerDataArray[playerID2].marketplace.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].marketplace.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].marketplace.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].marketplace.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].marketplace.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].marketplace.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].marketplace.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].marketplace.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].marketplace.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].engineersGuild.id
                = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
            DAT_GameState::instance.playerDataArray[playerID2].engineersGuild.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].engineersGuild.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].engineersGuild.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].engineersGuild.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].tunnelersGuild.id
                = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.id;
            DAT_GameState::instance.playerDataArray[playerID2].tunnelersGuild.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].tunnelersGuild.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].tunnelersGuild.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].tunnelersGuild.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].tunnelersGuild.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].stockpile.id
                = DAT_GameState::instance.playerDataArray[playerID].stockpile.id;
            DAT_GameState::instance.playerDataArray[playerID2].stockpile.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].stockpile.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].stockpile.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].stockpile.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].stockpile.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].stockpile.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].stockpile.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].stockpile.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].stockpile.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].armory.id
                = DAT_GameState::instance.playerDataArray[playerID].armory.id;
            DAT_GameState::instance.playerDataArray[playerID2].armory.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].armory.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].armory.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].armory.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].armory.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].armory.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].armory.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].armory.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].armory.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].granary.id
                = DAT_GameState::instance.playerDataArray[playerID].granary.id;
            DAT_GameState::instance.playerDataArray[playerID2].granary.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].granary.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].granary.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].granary.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].granary.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].granary.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].granary.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].granary.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].granary.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].barracks.id
                = DAT_GameState::instance.playerDataArray[playerID].barracks.id;
            DAT_GameState::instance.playerDataArray[playerID2].barracks.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].barracks.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].barracks.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].barracks.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].barracks.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].barracks.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].barracks.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].barracks.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].barracks.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].mercenaryPost.id
                = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id;
            DAT_GameState::instance.playerDataArray[playerID2].mercenaryPost.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].mercenaryPost.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].mercenaryPost.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].mercenaryPost.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].campground.id
                = DAT_GameState::instance.playerDataArray[playerID].campground.id;
            DAT_GameState::instance.playerDataArray[playerID2].campground.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].campground.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].campground.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].campground.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].campground.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].campground.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].unknown6.id
                = DAT_GameState::instance.playerDataArray[playerID].unknown6.id;
            DAT_GameState::instance.playerDataArray[playerID2].unknown6.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].unknown6.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].unknown6.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].unknown6.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].unknown6.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].unknown6.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].unknown6.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].unknown6.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].unknown6.id = 0;
            }
            DAT_GameState::instance.playerDataArray[playerID2].oilSmelter.id
                = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.id;
            DAT_GameState::instance.playerDataArray[playerID2].oilSmelter.xEntry
                = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.xEntry;
            DAT_GameState::instance.playerDataArray[playerID2].oilSmelter.yEntry
                = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.yEntry;
            DAT_GameState::instance.playerDataArray[playerID2].oilSmelter.tileEntry
                = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.tileEntry;
            DAT_GameState::instance.playerDataArray[playerID2].oilSmelter.areaEntry
                = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.areaEntry;
            if (playerID != playerID2) {
                DAT_GameState::instance.playerDataArray[playerID].oilSmelter.id = 0;
            }
        }

    }
}
}
