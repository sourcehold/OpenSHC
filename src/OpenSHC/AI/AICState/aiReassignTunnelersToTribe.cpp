#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D40B0
    void AICState::aiReassignTunnelersToTribe(int param_1)
    {
        uint unitID = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            Map::Units::Unit* psVar1 = &DAT_UnitsState::instance.units[1];
            do {
                if ((((psVar1->logicalState == Map::Units::ULS_NORMAL) && (psVar1->owner == param_1)) &&
                    (psVar1->dying == 0)) &&
                    ((psVar1->unitType == Map::Units::UT_TUNNELER && (psVar1->aiUnitBehaviourType == 0xf)))) {
                    if (psVar1->tribeID != 0) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(unitID, (int)psVar1->tribeID);
                    }
                    MACRO_CALL_MEMBER(AICState_Func::addUnitToItsTribe, this)(unitID, 0xf);
                }
                unitID = unitID + 1;
                psVar1 = psVar1 + 1;
            } while ((int)unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
    }
}
}
