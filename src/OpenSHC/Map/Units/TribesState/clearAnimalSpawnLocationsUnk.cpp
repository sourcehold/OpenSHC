#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Location/Point4ShortXY.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {
        using Map::Location::Point4ShortXY;

        // FUNCTION: STRONGHOLDCRUSADER 0x005232E0
        void TribesState::clearAnimalSpawnLocationsUnk()
        {
            /*
              The import walked a cursor over deerSpawnLocationsXY and reached the other
              three arrays through offsets from it (0x3ae to lionLocationsXY, 0x1d3e to
              rabbitSpawnXY, 0x1d52 to camelSpawnXY), ending on the absolute address
              0x117d1de. All four hold four XY pairs.
             */
            for (int _slot = 0; _slot < 4; _slot = _slot + 1) {
                DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[_slot].x = 0;
                DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[_slot].y = 0;
                DAT_GameState::instance.mapAndTime.lionLocationsXY[_slot].x = 0;
                DAT_GameState::instance.mapAndTime.lionLocationsXY[_slot].y = 0;
                DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0] = 0;
                DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][1] = 0;
                DAT_GameState::instance.mapAndTime.camelSpawnXY[_slot].x = 0;
                DAT_GameState::instance.mapAndTime.camelSpawnXY[_slot].y = 0;
            }
            DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor = 0;
        }

    }
}
}
