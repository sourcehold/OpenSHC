#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;
        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051BE60
        void TroopValueState::registerSpottedEnemyTile(int param_1)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            if (((((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                      && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .keep.id
                          < 1))
                     && (iVar2 = (int)(short)DAT_TileMapState::instance.UnitLayer[param_1], 0 < iVar2))
                    && ((DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_UnitsState::instance.units[iVar2].owner]
                            != -1
                        && (DAT_UnitsState::instance.units[iVar2].isSelectable_OR_matchTime != 0))))
                && ((DAT_TileMapState::instance.EntityLayer[param_1] == 0
                    || (DAT_EntityState::instance.entityArray[DAT_TileMapState::instance.EntityLayer[param_1]]
                            .entityType
                        != Map::Entities::ET_FIRE)))) {
                iVar2 = -1;
                iVar3 = 0;
                do {
                    iVar1 = this->attackInfo.spottedEnemyTiles[iVar3].tile;
                    if (iVar1 == param_1) {}
                    if ((!iVar1) && (iVar2 == -1)) {
                        iVar2 = iVar3;
                    }
                    iVar3 = iVar3 + 1;
                } while (iVar3 < 100);
                if (-1 < iVar2) {
                    this->attackInfo.spottedEnemyTiles[iVar2].tile = param_1;
                    this->attackInfo.spottedEnemyTiles[iVar2].value = 100;
                }
            }
        }

    }
}
}
