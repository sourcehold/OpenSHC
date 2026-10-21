#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A060
        void BuildingsState::displayPopularityAndGoldPopups(
            int buildingID, int param_2, int param_3, undefined4 param_4)
        {
            int const owner = this->buildings[buildingID].owner;
            if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            // EntityType has no constants for the popup types 40 to 43.
            int entityType;
            int heightOffset;
            switch (this->buildings[buildingID].buildingType) {
            case BT_MANORHOUSE:
            case BT_STONEKEEP:
            case BT_STRONGHOLD:
                entityType = 40;
                heightOffset = 120;
                break;
            case BT_CAMPGROUND:
                entityType = 41;
                heightOffset = 40;
                break;
            case BT_MARKETPLACE:
                heightOffset = 80;
                entityType = param_2 != 0 ? 43 : 42;
                break;
            default:
                return;
            }
            if (MACRO_CALL_MEMBER(Entities::EntityState_Func::playerHasEntityOfType, DAT_EntityState::ptr)(
                    this->buildings[buildingID].owner, (Entities::EntityType)entityType)
                != FALSE) {
                return;
            }
            int const half = (int)this->buildings[buildingID].widthOrHeight / 2;
            int const x = this->buildings[buildingID].x + half;
            int const y = this->buildings[buildingID].y + half;
            int const height = DAT_TileMapState::instance
                                   .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                + heightOffset;
            int const entityID = MACRO_CALL_MEMBER(Entities::EntityState_Func::spawnProjectileEntity,
                DAT_EntityState::ptr)(0, this->buildings[buildingID].owner, 0, x * 8, y * 8, height, 0, 0, 0,
                (Entities::EntityType)entityType, 0);
            if (entityID == 0) {
                return;
            }
            if (entityType == 40) {
                int const gold
                    = DAT_GameState::instance.playerDataArray[owner].currentResources[Game::Resources::RT_GOLD];
                DAT_EntityState::instance.entityArray[entityID].displayValue = gold;
                if (gold < 0) {
                    DAT_EntityState::instance.entityArray[entityID].displayValue = 0;
                }
            } else if (entityType == 41) {
                DAT_EntityState::instance.entityArray[entityID].displayValue
                    = DAT_GameState::instance.playerDataArray[owner].popularity / 100;
            } else if (entityType == 42) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = param_3;
                DAT_EntityState::instance.entityArray[entityID].field83_0xc0 = param_4 * 2 + 0x8d;
            } else if (entityType == 43) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = param_3;
                DAT_EntityState::instance.entityArray[entityID].field83_0xc0 = param_4 * 2 + 0x8d;
            }
        }

    }
}
}
