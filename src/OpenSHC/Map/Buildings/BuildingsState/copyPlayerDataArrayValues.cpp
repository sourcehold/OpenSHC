#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
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
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_CAMPGROUND]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_UNKNOWN6]
                    .id = 0;
            }
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                .id = DAT_GameState::instance.playerDataArray[fromPlayerID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                          .id;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                .xEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                              .xEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                .yEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                              .yEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                .tileEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                                 .tileEntry;
            DAT_GameState::instance.playerDataArray[toPlayerID]
                .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                .areaEntry = DAT_GameState::instance.playerDataArray[fromPlayerID]
                                 .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                                 .areaEntry;
            if (fromPlayerID != toPlayerID) {
                DAT_GameState::instance.playerDataArray[fromPlayerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_OILSMELTER]
                    .id = 0;
            }
        }

    }
}
}
