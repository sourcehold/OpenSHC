#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A4E0
        void BuildingsState::copyPlayerDataArrayValues(int fromPlayerID, int toPlayerID)
        {
            int found = 0;
            for (int buildingID = 1; buildingID < 2000; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == fromPlayerID) {
                    this->buildings[buildingID].owner = toPlayerID;
                    found = 1;
                    if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
                        this->buildings[buildingID].playerColorUnk = toPlayerID;
                    }
                }
            }
            if (found <= 0) {
                return;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].keep.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].keep.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].keep.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].keep.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].keep.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].keep.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].keep.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].keep.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].keep.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].keep.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].keep.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].marketplace.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].marketplace.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].marketplace.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].marketplace.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].marketplace.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].marketplace.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].marketplace.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].marketplace.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].marketplace.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].marketplace.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].marketplace.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].engineersGuild.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].engineersGuild.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].engineersGuild.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].engineersGuild.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].engineersGuild.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].engineersGuild.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].engineersGuild.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].engineersGuild.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].engineersGuild.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].engineersGuild.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].engineersGuild.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].tunnelersGuild.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].tunnelersGuild.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].tunnelersGuild.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].tunnelersGuild.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].tunnelersGuild.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].tunnelersGuild.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].tunnelersGuild.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].tunnelersGuild.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].tunnelersGuild.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].tunnelersGuild.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].tunnelersGuild.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].stockpile.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].stockpile.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].stockpile.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].stockpile.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].stockpile.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].stockpile.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].stockpile.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].stockpile.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].stockpile.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].stockpile.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].stockpile.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].armory.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].armory.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].armory.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].armory.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].armory.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].armory.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].armory.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].armory.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].armory.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].armory.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].armory.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].granary.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].granary.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].granary.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].granary.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].granary.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].granary.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].granary.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].granary.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].granary.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].granary.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].granary.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].barracks.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].barracks.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].barracks.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].barracks.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].barracks.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].barracks.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].barracks.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].barracks.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].barracks.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].barracks.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].barracks.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].mercenaryPost.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].mercenaryPost.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].mercenaryPost.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].mercenaryPost.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].mercenaryPost.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].mercenaryPost.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].mercenaryPost.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].mercenaryPost.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].mercenaryPost.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].mercenaryPost.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].mercenaryPost.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].campground.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].campground.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].campground.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].campground.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].campground.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].campground.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].campground.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].campground.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].campground.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].campground.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].campground.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].unknown6.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].unknown6.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].unknown6.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].unknown6.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].unknown6.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].unknown6.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].unknown6.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].unknown6.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].unknown6.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].unknown6.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].unknown6.id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID].oilSmelter.id
                = DAT_GameState::instance.playerDataArray[fromPlayerID].oilSmelter.id;
            DAT_GameState::instance.playerDataArray[toPlayerID].oilSmelter.xEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].oilSmelter.xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].oilSmelter.yEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].oilSmelter.yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].oilSmelter.tileEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].oilSmelter.tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID].oilSmelter.areaEntry
                = DAT_GameState::instance.playerDataArray[fromPlayerID].oilSmelter.areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID].oilSmelter.id = 0;
            }
        }

    }
}
}
