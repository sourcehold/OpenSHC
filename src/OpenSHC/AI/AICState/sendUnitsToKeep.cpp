#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD0C0
    void AICState::sendUnitsToKeep(undefined4 tribeID, int playerID)
    {
        int iVar1 = DAT_GameState::instance.playerDataArray[playerID].keep.id;
        if (0 < iVar1) {
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(tribeID, (int)(short)DAT_BuildingsState::instance.buildings[iVar1].x + 3, (int)(short)DAT_BuildingsState::instance.buildings[iVar1].y + 4, 0);
        }
    }
}
}
