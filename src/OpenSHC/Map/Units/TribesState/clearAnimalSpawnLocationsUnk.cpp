#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Location/Point4ShortXY.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005232E0
        void TribesState::clearAnimalSpawnLocationsUnk()
        {
            for (int _slot = 0; _slot < 4; ++_slot) {
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
