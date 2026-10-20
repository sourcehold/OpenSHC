#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005233A0
        void TribesState::setRabbitSpawnXY(undefined4 x, undefined4 y)
        {
            /*
              0x117ef1c is one past rabbitSpawnXY[3], so the cursor and its magic end
              address are a plain four-entry loop.
             */
            for (int _slot = 0; _slot < 4; _slot = _slot + 1) {
                if (DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0] == 0) {
                    DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0] = (short)x;
                    DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][1] = (short)y;
                }
            }
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][0] = (short)x;
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][1] = (short)y;
        }

    }
}
}
