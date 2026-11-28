#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using Game::Player::PlayerData;
    using Map::Entities::EntityType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3150
    void LandscapeState::spawnCrowFromNearbyTree(int unitID)
    {
        BOOL playedSound = FALSE;
        for (int direction = 0; direction < 8; direction++) {
            int const y = DAT_UnitsState::instance.units[unitID].y;
            short const treeID = DAT_TileMapState::instance
                                     .OrganismLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction]
                                         + DAT_UnitsState::instance.units[unitID].tile];
            if (treeID == 0 || treeID >= this->maxTreeCount) {
                continue;
            }
            if (this->trees[treeID].state != 2 || this->trees[treeID].unknownDistanceRelatedToCrow == 0
                || this->trees[treeID].rng200till300 != 0) {
                continue;
            }
            int const playerID = DAT_UnitsState::instance.units[unitID].owner;
            int targetX = 0;
            int targetY = 0;
            int closestDistance = 10000;
            for (int keepPlayerID = 1; keepPlayerID < 9; keepPlayerID++) {
                if (keepPlayerID == playerID
                    || !DAT_GameState::instance.playerDataArray[keepPlayerID]
                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                        .id) {
                    continue;
                }
                int const distanceX = abs(DAT_UnitsState::instance.units[unitID].x
                    - DAT_GameState::instance.playerDataArray[keepPlayerID]
                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                        .xEntry);
                int const distanceY = abs(y
                    - DAT_GameState::instance.playerDataArray[keepPlayerID]
                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                        .yEntry);
                int const distance = distanceX > distanceY ? distanceX : distanceY;
                if (distance < closestDistance) {
                    targetX = SEC_RNG::instance.currentNumber2 % 5 - 2
                        + DAT_GameState::instance.playerDataArray[keepPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .xEntry;
                    targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 5 - 2
                        + DAT_GameState::instance.playerDataArray[keepPlayerID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .yEntry;
                    closestDistance = distance;
                }
            }
            if (closestDistance == 10000) {
                targetX = DAT_UnitsState::instance.units[unitID].x - 50 + SEC_RNG::instance.currentNumber2 % 100;
                targetY = (SEC_RNG::instance.currentNumber2 >> 8) % 100 - 50 + y;
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            }
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                DAT_UnitsState::instance.units[unitID].owner, 0, this->trees[treeID].xPosition * 8,
                this->trees[treeID].yPosition * 8,
                DAT_TileMapState::instance.HeightLayer[this->trees[treeID].tile] + 30, targetX * 8, targetY * 8, 250,
                Map::Entities::EntityTypeInt__ET_CROW, 0);
            this->trees[treeID].rng200till300 = SEC_RNG::instance.currentNumber2 % 100 + 200;
            if (!playedSound) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    this->trees[treeID].xPosition, this->trees[treeID].yPosition, DE::SHCDE::FX_CROW);
                playedSound = TRUE;
            }
        }
    }

}
}
