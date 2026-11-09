#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005233A0
        void TribesState::setRabbitSpawnXY(int x, int y)
        {
            for (int _slot = 0; _slot < (int)_countof(DAT_GameState::instance.mapAndTime.rabbitSpawnXY); ++_slot) {
                if (DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0] == 0) {
                    DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0] = x;
                    DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][1] = y;
                }
            }
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][0] = x;
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][1] = y;
        }

    }
}
}
