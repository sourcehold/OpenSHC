#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
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

        using Game::GameMode;
        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BE60
        void TroopValueState::registerSpottedEnemyTile(int param_1)
        {
            int _freeSlot;
            int _entityID;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].keep.id
                    <= 0
                && (_freeSlot = (int)(short)DAT_TileMapState::instance.UnitLayer[param_1], 0 < _freeSlot)
                && DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_UnitsState::instance.units[_freeSlot].owner]
                    != -1
                && DAT_UnitsState::instance.units[_freeSlot].isSelectable_OR_matchTime != 0
                && (_entityID = (int)(short)DAT_TileMapState::instance.EntityLayer[param_1],
                    !_entityID
                        || (DAT_EntityState::instance.entityArray[_entityID].entityType != Map::Entities::ET_FIRE))) {
                _freeSlot = -1;
                for (int _slot = 0; _slot < 100; _slot = _slot + 1) {
                    int const _tile = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[_slot].tile;
                    if (_tile == param_1) {
                        return;
                    }
                    if ((!_tile) && (_freeSlot == -1)) {
                        _freeSlot = _slot;
                    }
                }
                if (-1 < _freeSlot) {
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[_freeSlot].tile = param_1;
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[_freeSlot].value = 100;
                }
            }
        }

    }
}
}
