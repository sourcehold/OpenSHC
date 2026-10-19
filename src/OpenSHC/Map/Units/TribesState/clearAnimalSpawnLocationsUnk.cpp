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
            short* psVar1;
            psVar1 = &DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY[0].y;
            do {
                ((Point4ShortXY*)(psVar1 + -1))->x = 0;
                *psVar1 = 0;
                psVar1[0x1d7] = 0;
                psVar1[0x1d8] = 0;
                psVar1[0xe9f] = 0;
                psVar1[0xea0] = 0;
                psVar1[0xea9] = 0;
                psVar1[0xeaa] = 0;
                psVar1 = psVar1 + 2;
            } while ((int)psVar1 < 0x117d1de);
            DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor = 0;
        }

    }
}
}
