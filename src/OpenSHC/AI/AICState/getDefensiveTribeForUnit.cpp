#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeIndex.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCBE0
    int AICState::getDefensiveTribeForUnit(int playerID, int unitID)
    {
        int index = 0;
        for (; index < countof(DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray); index++) {
            if (DAT_UnitsState::instance.units[unitID].unitType
                    == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[index]
                || DAT_UnitsState::instance.units[unitID].unitTypeToChangeInto
                    == DAT_SkirmishDefinedData::instance.DefenseTribesUnitTypeArray[index])
                break;
        }

        int tribeIndex;
        if (index < 1)
            tribeIndex = OpenSHC::AI::Tribes::AITI_DEF_KNIGHTS;
        else if (index < 2)
            tribeIndex = OpenSHC::AI::Tribes::AITI_DEF_HORSE_ARCHERS;
        else if (index < 7)
            tribeIndex = OpenSHC::AI::Tribes::AITI_DEF_WALKING_RANGED;
        else if (index < 12)
            tribeIndex = OpenSHC::AI::Tribes::AITI_DEF_ASSASSIN_MACE_MONK_SLAVE_SPEAR;
        else if (index < 15)
            tribeIndex = OpenSHC::AI::Tribes::AITI_DEF_ARAB_SWORDSMAN_SWORDSMAN_PIKEMAN;
        else if (index < 20)
            tribeIndex = OpenSHC::AI::Tribes::AITI_DEF_SIEGE;
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
