#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BE60
        void TroopValueState::registerSpottedEnemyTile(int param_1)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                || 0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                        .id) {
                return;
            }
            int const unitID = DAT_TileMapState::instance.UnitLayer[param_1];
            if (unitID <= 0
                || DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                    == -1
                || DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
                return;
            }
            int const entityID = DAT_TileMapState::instance.EntityLayer[param_1];
            if (entityID && DAT_EntityState::instance.entityArray[entityID].entityType == Map::Entities::ET_FIRE) {
                return;
            }
            int freeSlot = -1;
            for (int slot = 0; slot < countof(DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles); ++slot) {
                int const tile = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[slot].tile;
                if (tile == param_1) {
                    return;
                }
                if (!tile && freeSlot == -1) {
                    freeSlot = slot;
                }
            }
            if (-1 < freeSlot) {
                DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[freeSlot].tile = param_1;
                DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[freeSlot].value = 100;
            }
        }

    }
}
}
