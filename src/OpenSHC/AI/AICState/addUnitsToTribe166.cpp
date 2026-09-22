#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC720
    void AICState::addUnitsToTribe166(int playerID)
    {
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].owner != playerID)
                continue;
            if (DAT_UnitsState::instance.units[unitID].logicalState != Map::Units::ULS_NORMAL)
                continue;
            if (DAT_UnitsState::instance.units[unitID].dying != 0)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 6)
                continue;

            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[166];
            if (DAT_UnitsState::instance.units[unitID].tribeID == tribeID)
                continue;

            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                unitID, DAT_UnitsState::instance.units[unitID].tribeID);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
        }
    }
}
}
