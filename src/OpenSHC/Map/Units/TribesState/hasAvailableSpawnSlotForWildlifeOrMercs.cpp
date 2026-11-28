#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameModeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Slots 4..11 read [i*4 + 0x117F094] (0x52356C) = mapAndTime.signpostIDs[i - 4].
        // FUNCTION: STRONGHOLDCRUSADER 0x00523520
        BOOLEnum TribesState::hasAvailableSpawnSlotForWildlifeOrMercs()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                return FALSE;
            }
            if (DAT_GameState::instance.mapAndTime.wildlifeCount >= 160) {
                return FALSE;
            }
            for (int i = 0; i < 12; ++i) {
                if (i < 4) {
                    uint const spawnX = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][0];
                    uint const spawnY = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][1];
                    if (spawnX <= 399 && spawnY <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[spawnY * 400 + spawnX] != 0) {
                        return TRUE;
                    }
                } else if (DAT_GameState::instance.mapAndTime.signpostIDs[i - 4] != 0) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
