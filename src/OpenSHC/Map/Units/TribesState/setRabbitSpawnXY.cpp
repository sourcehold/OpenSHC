#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005233A0
        void TribesState::setRabbitSpawnXY(undefined4 x, undefined4 y)
        {
            short (*pasVar1)[2];
            pasVar1 = DAT_GameState::instance.mapAndTime.rabbitSpawnXY;
            do {
                if ((*pasVar1)[0] == 0) {
                    (*pasVar1)[0] = (short)x;
                    (*pasVar1)[1] = (short)y;
                }
                pasVar1 = pasVar1 + 1;
            } while ((int)pasVar1 < 0x117ef1c);
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][0] = (short)x;
            DAT_GameState::instance.mapAndTime.rabbitSpawnXY[0][1] = (short)y;
        }

    }
}
}
