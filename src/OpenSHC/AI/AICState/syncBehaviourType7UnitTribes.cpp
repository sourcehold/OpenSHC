#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC7B0
    void AICState::syncBehaviourType7UnitTribes(int param_1)
    {
        int tribeID;
        uint unitID = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            Map::Units::Unit* pUVar1 = &DAT_UnitsState::instance.units[1];
            do {
                if ((((pUVar1->owner == param_1) && (pUVar1->logicalState == Map::Units::ULS_NORMAL)) &&
                    (pUVar1->dying == 0)) && (pUVar1->aiUnitBehaviourType == 7)) {
                    tribeID = (int)DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs[0xa7];
                    if (pUVar1->tribeID != tribeID) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(unitID, (int)pUVar1->tribeID);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
                    }
                }
                unitID = unitID + 1;
                pUVar1 = pUVar1 + 1;
            } while ((int)unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
    }
}
}
