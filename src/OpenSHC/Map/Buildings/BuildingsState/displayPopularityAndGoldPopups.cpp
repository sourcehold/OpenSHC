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
            int buildingID, int param_2, int param_3, undefined4 param_4)
        {
            // Shows the gold, popularity or trade popup above keeps, campgrounds and marketplaces of other players
            // Matching note: the calls read the owner again through this alias; the original does not reuse playerID
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
                entityType = (EntityType)40;
                heightOffset = 120;
                break;
            case BT_CAMPGROUND:
                // Popularity popup
                entityType = (EntityType)41;
                heightOffset = 40;
                break;
            case BT_MARKETPLACE:
                heightOffset = 80;
                // Trade popups
                if (param_2 != 0) {
                    entityType = (EntityType)43;
                } else {
                    entityType = (EntityType)42;
                }
                break;
            default:
                return;
            }

            if (MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::playerHasEntityOfType,
                    DAT_EntityState::ptr)(owner, entityType)) {
                return;
            }
            // Matching note: the tile index is a local of its own: inline, MSVC folds the last addition into the load
            // address. x and y are read from the fields rather than through locals, which keeps x in ebx and the entity
            // type in edi as in the original
            int const halfSize = (int)this->buildings[buildingID].widthOrHeight / 2;
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

            if (entityType == (EntityType)40) {
                int const gold = DAT_GameState::instance.playerDataArray[playerID]
                                     .currentResources[OpenSHC::Game::Resources::RT_GOLD];
                DAT_EntityState::instance.entityArray[entityID].displayValue = gold;
                if (gold < 0) {
                    DAT_EntityState::instance.entityArray[entityID].displayValue = 0;
                }
            } else if (entityType == (EntityType)41) {
                DAT_EntityState::instance.entityArray[entityID].displayValue
                    = DAT_GameState::instance.playerDataArray[playerID].popularity / 100;
            } else if (entityType == (EntityType)42) {
                // Matching note: the two trade arms are separate in the original; one || test measured 93%
                DAT_EntityState::instance.entityArray[entityID].displayValue = param_3;
                DAT_EntityState::instance.entityArray[entityID].field_0xc0 = (short)param_4 * 2 + 141;
            } else if (entityType == (EntityType)43) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = param_3;
                DAT_EntityState::instance.entityArray[entityID].field_0xc0 = (short)param_4 * 2 + 141;
            }
        }

    }
}
}
