#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD0C0
    void AICState::sendUnitsToKeep(int tribeID, int playerID)
    {
        int keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
        if (keepID <= 0) {
            return;
        }

        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(tribeID,
            (short)DAT_BuildingsState::instance.buildings[keepID].x + 3,
            (short)DAT_BuildingsState::instance.buildings[keepID].y + 4, 0);
    }
}
}
