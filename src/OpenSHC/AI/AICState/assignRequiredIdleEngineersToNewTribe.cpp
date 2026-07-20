#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC5A0
    int AICState::assignRequiredIdleEngineersToNewTribe(int playerID, int count)
    {
        Map::Units::States::UnitStateShort UVar1;
        int tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
        uint unitID = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            Map::Units::Unit* psVar2 = &DAT_UnitsState::instance.units[1];
            do {
                if (count < 1) {
                    return tribeID;
                }
                if (((((psVar2->logicalState == Map::Units::ULS_NORMAL) && (psVar2->owner == playerID)) &&
                    (psVar2->dying == 0)) &&
                    ((psVar2->unitType == Map::Units::UT_E_ENGINEER && (psVar2->aiUnitBehaviourType != 0x16)))) &&
                    ((psVar2->aiUnitBehaviourType != 10 && (psVar2->engineerRelatedUnk == 0))) &&
                    (((UVar1 = (psVar2->state).generic, UVar1 == 0x69 || (UVar1 == 2)) || (UVar1 == Map::Units::States::US_IDLEUnk)))) {
                    if (psVar2->tribeID != 0) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(unitID, (int)psVar2->tribeID);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
                    count = count + -1;
                }
                unitID = unitID + 1;
                psVar2 = psVar2 + 1;
            } while ((int)unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
        return tribeID;
    }
}
}
