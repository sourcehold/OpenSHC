#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC840
    void AICState::aiAddUnitToMoatDiggerTribe(int unitID)
    {
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 5;
        int tribeID = DAT_GameState::instance.playerDataArray[owner].aiTribeIDs[10];
        if (tribeID == 0
            || DAT_TribesState::instance.tribes[tribeID].uid != DAT_GameState::instance.playerDataArray[owner].aiTribeUIDs[10]) {
            tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(owner);
            DAT_GameState::instance.playerDataArray[owner].aiTribeIDs[10] = tribeID;
            DAT_GameState::instance.playerDataArray[owner].aiTribeUIDs[10] = DAT_TribesState::instance.tribes[tribeID].uid;
        }
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, tribeID);
        DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_DEFENSIVE;
    }
}
}
