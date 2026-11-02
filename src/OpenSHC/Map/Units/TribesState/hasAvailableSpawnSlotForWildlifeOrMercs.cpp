#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameModeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Slots 4..11 read [i*4 + 0x117F094] (machine code 0x52356C) = mapAndTime.signpostIDs[i - 4]
        // (0x117F0A4..0x117F0C0), not mercRecruitable as the header doc says.
        // FUNCTION: STRONGHOLDCRUSADER 0x00523520
        undefined4 TribesState::hasAvailableSpawnSlotForWildlifeOrMercs()
        {
            int i;
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                && (i = 0, DAT_GameState::instance.mapAndTime.wildlifeCount < 0xa0)) {
                do {
                    if (i < 4) {
                        uint const spawnX = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][0];
                        uint const spawnY = DAT_GameState::instance.mapAndTime.rabbitSpawnXY[i][1];
                        if (spawnX <= 399 && spawnY <= 399
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[spawnY * 400 + spawnX]
                                != 0) {
                            return 1;
                        }
                    } else if (DAT_GameState::instance.mapAndTime.signpostIDs[i - 4] != 0) {
                        return 1;
                    }
                    ++i;
                } while (i < 12);
            }
            return 0;
        }

    }
}
}
