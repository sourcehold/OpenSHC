#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC840
    void AICState::aiAddUnitToMoatDiggerTribe(int unitID)
    {
        int _owner = (int)DAT_UnitsState::instance.units[unitID].owner;
        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 5;
        int _tribe = (int)DAT_GameState::instance.playerDataArray[_owner].aiTribeIDs[10];
        if ((_tribe == 0) ||
            (DAT_TribesState::instance.tribes[_tribe].uid != DAT_GameState::instance.playerDataArray[_owner].aiTribeUIDs[10])) {
            _tribe = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(_owner);
            int _uid = DAT_TribesState::instance.tribes[_tribe].uid;
            DAT_GameState::instance.playerDataArray[_owner].aiTribeIDs[10] = (short)_tribe;
            DAT_GameState::instance.playerDataArray[_owner].aiTribeUIDs[10] = _uid;
        }
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, _tribe);
        DAT_TribesState::instance.tribes[_tribe].unitStance = Map::Units::Behavior::USE_DEFENSIVE;
    }
}
}
