#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F240
        void BuildingsState::destroySignpostData(int buildingID)
        {
            for (int i = 0; i < 8; ++i) {
                if (DAT_GameState::instance.mapAndTime.signpostIDs[i] == buildingID) {
                    DAT_GameState::instance.mapAndTime.signpostIDs[i] = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[i].x = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[i].y = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[i].tile = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[i].unknown = 0;
                }
            }
        }

    }
}
}
