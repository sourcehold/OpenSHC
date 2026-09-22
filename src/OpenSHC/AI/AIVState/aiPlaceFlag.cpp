#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ED240
    void AIVState::aiPlaceFlag(PlayerID playerID)
    {
        Map::Entities::EntityType const flagType = (Map::Entities::EntityType)DAT_AICState::instance
                                                       .aics[DAT_GameState::instance.playerDataArray[playerID].aiType - 1]
                                                       .flagType;
        if (DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[AIVUT_FLAG] <= 0) {
            return;
        }
        for (int i = 0; i < 10; ++i) {
            int const tile = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[AIVUT_FLAG][i];
            if (tile <= 0) {
                continue;
            }
            int const entityID = DAT_TileMapState::instance.EntityLayer[tile];
            if (entityID != 0 && DAT_EntityState::instance.entityArray[entityID].entityType == flagType) {
                continue;
            }
            int const height
                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getTotalHeightAt, DAT_TileMapState::ptr)(tile, playerID);
            if (height <= 0) {
                continue;
            }
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                playerID, playerID,
                (tile
                    - DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                          .addXgetTile)
                        * 8
                    + 4,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] * 8 + 4, height, 0, 0, 0,
                flagType, 0);
        }
    }

}
}
