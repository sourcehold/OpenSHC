#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D40B0
    void AICState::aiReassignTunnelersToTribe(int param_1)
    {
        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            Map::Units::Unit* _pUnit = &DAT_UnitsState::instance.units[unitID];
            if ((((_pUnit->logicalState == Map::Units::ULS_NORMAL) && (_pUnit->owner == param_1))
                    && (_pUnit->dying == 0))
                && ((_pUnit->unitType == Map::Units::UT_TUNNELER && (_pUnit->aiUnitBehaviourType == 0xf)))) {
                if (_pUnit->tribeID != 0) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                        unitID, (int)_pUnit->tribeID);
                }
                MACRO_CALL_MEMBER(AICState_Func::addUnitToItsTribe, this)(unitID, 0xf);
            }
        }
    }
}
}
