#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2790
    void AICState::aiAssignUnitToDefensiveTribe(int unitID)
    {
        int _playerID = (int)DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_GameState::instance.playerDataArray[_playerID].aiType != AITA_NULL) {
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 2;
            int _tribeID = MACRO_CALL_MEMBER(AICState_Func::getDefensiveTribeForUnit, this)(_playerID, unitID);
            if (_tribeID != 0) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, _tribeID);
            }
        }
    }
}
}
