#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F240
        void BuildingsState::destroySignpostData(int buildingID)
        {
            for (int slot = 0; slot < 8; ++slot) {
                if (DAT_GameState::instance.mapAndTime.signpostIDs[slot] == buildingID) {
                    DAT_GameState::instance.mapAndTime.signpostIDs[slot] = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[slot].x = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[slot].y = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[slot].tile = 0;
                    DAT_GameState::instance.mapAndTime.signpostEntryData[slot].unknown = 0;
                }
            }
        }

    }
}
}
