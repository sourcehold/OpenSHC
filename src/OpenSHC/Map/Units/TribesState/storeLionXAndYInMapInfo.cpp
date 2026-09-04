#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Location/Point4ShortXY.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Location::Point4ShortXY;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523370
        void TribesState::storeLionXAndYInMapInfo(undefined4 x, undefined4 y)
        {
            for (int i = 0; i < 4; i++) {
                if (DAT_GameState::instance.mapAndTime.lionLocationsXY[i].x == 0) {
                    DAT_GameState::instance.mapAndTime.lionLocationsXY[i].x = x;
                    DAT_GameState::instance.mapAndTime.lionLocationsXY[i].y = y;
                }
            }
        }

    }
}
}
