#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A060
        void BuildingsState::displayPopularityAndGoldPopups(
            int buildingID, BOOLEnum isSale, int amount, undefined4 resourceType)
        {
            // Shows the gold, popularity or trade popup above keeps, campgrounds and marketplaces of other players.
            // For a trade, amount is the traded amount and resourceType selects the icon.
            short const& owner = this->buildings[buildingID].owner;
            int const playerID = this->buildings[buildingID].owner;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }

            int heightOffset;
            EntityType entityType;
            switch (this->buildings[buildingID].buildingType) {
            case BT_MANORHOUSE:
            case BT_STONEKEEP:
            case BT_STRONGHOLD:
                // Gold popup
                entityType = OpenSHC::Map::Entities::ET_GOLD_POPUP;
                heightOffset = 120;
                break;
            case BT_CAMPGROUND:
                // Popularity popup
                entityType = OpenSHC::Map::Entities::ET_POPULARITY_POPUP;
                heightOffset = 40;
                break;
            case BT_MARKETPLACE:
                heightOffset = 80;
                // Trade popups
                if (isSale) {
                    entityType = OpenSHC::Map::Entities::ET_TRADE_SELL_POPUP;
                } else {
                    entityType = OpenSHC::Map::Entities::ET_TRADE_BUY_POPUP;
                }
                break;
            default:
                return;
            }

            if (MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::playerHasEntityOfType,
                    DAT_EntityState::ptr)(owner, entityType)) {
                return;
            }
            int const halfSize = this->buildings[buildingID].widthOrHeight / 2;
            int const tile
                = DAT_ViewportRenderState::instance.translationMatrix[this->buildings[buildingID].y + halfSize]
                      .addXgetTile
                + this->buildings[buildingID].x + halfSize;
            uint const entityID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, owner, 0,
                (this->buildings[buildingID].x + halfSize) * 8, (this->buildings[buildingID].y + halfSize) * 8,
                DAT_TileMapState::instance.HeightLayer[tile] + heightOffset, 0, 0, 0, entityType, 0);
            if (entityID == 0) {
                return;
            }

            if (entityType == OpenSHC::Map::Entities::ET_GOLD_POPUP) {
                int const gold = DAT_GameState::instance.playerDataArray[playerID]
                                     .currentResources[OpenSHC::Game::Resources::RT_GOLD];
                DAT_EntityState::instance.entityArray[entityID].displayValue = gold;
                if (gold < 0) {
                    DAT_EntityState::instance.entityArray[entityID].displayValue = 0;
                }
            } else if (entityType == OpenSHC::Map::Entities::ET_POPULARITY_POPUP) {
                DAT_EntityState::instance.entityArray[entityID].displayValue
                    = DAT_GameState::instance.playerDataArray[playerID].popularity / 100;
            } else if (entityType == OpenSHC::Map::Entities::ET_TRADE_BUY_POPUP) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = amount;
                DAT_EntityState::instance.entityArray[entityID].overlayGmPictureIndex = (short)resourceType * 2 + 141;
            } else if (entityType == OpenSHC::Map::Entities::ET_TRADE_SELL_POPUP) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = amount;
                DAT_EntityState::instance.entityArray[entityID].overlayGmPictureIndex = (short)resourceType * 2 + 141;
            }
        }

    }
}
}
