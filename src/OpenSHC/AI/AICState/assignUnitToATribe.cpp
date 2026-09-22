#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2660
    void AICState::assignUnitToATribe(int unitID)
    {
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_GameState::instance.playerDataArray[owner].aiType == AITA_NULL)
            return;

        AIVUnitType aivUnitType = MACRO_CALL_MEMBER(AICState_Func::getUnitTypeIndexForUnitID, this)(unitID,
            DAT_GameState::instance.playerDataArray[owner].aivCurrentPauseIndex == 1
                    && DAT_GameState::instance.playerDataArray[owner].aivPauses[1] > 0
                ? 1
                : 0);
        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 1;
        if (DAT_GameState::instance.playerDataArray[owner].aivUnitLocationSlotLocationCount[aivUnitType] <= 0) {
            if (MACRO_CALL_MEMBER(AICState_Func::unitIDIsRangedOrArmored, this)(unitID) != 0) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    unitID, MACRO_CALL_MEMBER(AICState_Func::createTribeForUnitType, this)(owner, 0));
                return;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                unitID, MACRO_CALL_MEMBER(AICState_Func::createTribeForUnitType, this)(owner, 1));
            return;
        }
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
            unitID, MACRO_CALL_MEMBER(AICState_Func::smallestTribeOfUnitType, this)(owner, aivUnitType));
    }
}
}
