#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
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
            int playerID = this->buildings[buildingID].owner;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }

            int heightOffset;
            EntityType entityType;
            switch (this->buildings[buildingID].buildingType) {
            case BT_MANORHOUSE:
            case BT_STONEKEEP:
            case BT_STRONGHOLD:
                entityType = (EntityType)0x28;
                heightOffset = 120;
                break;
            case BT_CAMPGROUND:
                entityType = (EntityType)0x29;
                heightOffset = 40;
                break;
            case BT_MARKETPLACE:
                heightOffset = 80;
                entityType = param_2 != 0 ? (EntityType)0x2b : (EntityType)0x2a;
                break;
            default:
                return;
            }

            if (MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::playerHasEntityOfType,
                    DAT_EntityState::ptr)(this->buildings[buildingID].owner, entityType)
                != FALSE) {
                return;
            }
            int x = (short)this->buildings[buildingID].x;
            int halfSize = (int)this->buildings[buildingID].widthOrHeight / 2;
            int y = (short)this->buildings[buildingID].y + halfSize;
            uint entityID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                DAT_EntityState::ptr)(0, this->buildings[buildingID].owner, 0, (x + halfSize) * 8, y * 8,
                DAT_TileMapState::instance
                        .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x + halfSize]
                    + heightOffset,
                0, 0, 0, entityType, 0);
            if (entityID == 0) {
                return;
            }

            if (entityType == (EntityType)0x28) {
                int gold = DAT_GameState::instance.playerDataArray[playerID]
                               .currentResources[OpenSHC::Game::Resources::RT_GOLD];
                DAT_EntityState::instance.entityArray[entityID].displayValue = gold;
                if (gold < 0) {
                    DAT_EntityState::instance.entityArray[entityID].displayValue = 0;
                }
            } else if (entityType == (EntityType)0x29) {
                DAT_EntityState::instance.entityArray[entityID].displayValue
                    = DAT_GameState::instance.playerDataArray[playerID].popularity / 100;
            } else if (entityType == (EntityType)0x2a) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = param_3;
                DAT_EntityState::instance.entityArray[entityID].field83_0xc0 = (short)param_4 * 2 + 141;
            } else if (entityType == (EntityType)0x2b) {
                DAT_EntityState::instance.entityArray[entityID].displayValue = param_3;
                DAT_EntityState::instance.entityArray[entityID].field83_0xc0 = (short)param_4 * 2 + 141;
            }
        }

    }
}
}
