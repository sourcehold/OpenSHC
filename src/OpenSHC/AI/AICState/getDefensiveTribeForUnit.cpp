#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCBE0
    int AICState::getDefensiveTribeForUnit(int playerID, int unitID)
    {
        int index;
        for (index = 0; index < 20; index++) {
            if (DAT_UnitsState::instance.units[unitID].unitType
                    == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[index]
                || DAT_UnitsState::instance.units[unitID].unitTypeToChangeInto
                    == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[index])
                break;
        }

        int tribeIndex;
        if (index < 1)
            tribeIndex = 180;
        else if (index < 2)
            tribeIndex = 181;
        else if (index < 7)
            tribeIndex = 182;
        else if (index < 12)
            tribeIndex = 183;
        else if (index < 15)
            tribeIndex = 184;
        else if (index < 20)
            tribeIndex = 185;
        else
            return 0;

        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeIndex];
        if (tribeID != 0
            && DAT_TribesState::instance.tribes[tribeID].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[tribeIndex])
            return tribeID;

        tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeIndex] = tribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[tribeIndex]
            = DAT_TribesState::instance.tribes[tribeID].uid;
        return tribeID;
    }
}
}
