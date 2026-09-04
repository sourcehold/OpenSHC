#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005233E0
        void TribesState::setCamelSpawnXY(undefined4 x, undefined4 y)
        {
            for (int i = 0; i < 4; i++) {
                if (DAT_GameState::instance.mapAndTime.camelSpawnXY[i][0] == 0) {
                    DAT_GameState::instance.mapAndTime.camelSpawnXY[i][0] = x;
                    DAT_GameState::instance.mapAndTime.camelSpawnXY[i][1] = y;
                }
            }
        }

    }
}
}
