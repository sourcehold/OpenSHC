#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ED300
    void AIVState::aiPlaceBrazier(PlayerID playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[AIVUT_BRAZIER] <= 0) {
            return;
        }
        for (int i = 0; i < 10; ++i) {
            int const tile = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[AIVUT_BRAZIER][i];
            if (tile <= 0) {
                continue;
            }
            int const entityID = DAT_TileMapState::instance.EntityLayer[tile];
            if (entityID != 0 && DAT_EntityState::instance.entityArray[entityID].entityType == Map::Entities::ET_BRAZIER) {
                continue;
            }
            uint const height
                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tile);
            if ((int)height <= 0) {
                continue;
            }
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                playerID, playerID,
                (tile
                    - DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                          .addXgetTile)
                    * 8,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] * 8, height, 0, 0, 0,
                Map::Entities::ET_BRAZIER, 0);
        }
    }

}
}
