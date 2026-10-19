#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523520
        undefined4 TribesState::hasAvailableSpawnSlotForWildlifeOrMercs()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                || 0xa0 <= DAT_GameState::instance.mapAndTime.wildlifeCount) {
                return (undefined4)(0);
            }
            for (int _slot = 0; _slot < 0xc; _slot = _slot + 1) {
                if (_slot < 4) {
                    uint const _x = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0];
                    uint const _y = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][1];
                    if (_x <= 399 && _y <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_y * 400 + _x] != 0) {
                        return (undefined4)(1);
                    }
                } else if (DAT_GameState::instance.mapAndTime.mercRecruitable[_slot + 4] != 0) {
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
