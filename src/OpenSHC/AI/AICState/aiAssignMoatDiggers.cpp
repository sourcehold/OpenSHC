#include "../AICState.func.hpp"

#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using namespace OpenSHC::Map::Units;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3F20
    void AICState::aiAssignMoatDiggers(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return;
        int aicIndex = aiType - 1;
        if (DAT_GameState::instance.playerDataArray[playerID].totalTroopsType0 <= 0)
            return;

        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_INVISIBLE)
                continue;
            if (DAT_UnitsState::instance.units[unitID].owner != playerID)
                continue;
            if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 0)
                continue;
            if (DAT_UnitsState::instance.units[unitID].dying != 0)
                continue;

            if (DAT_UnitsState::instance.units[unitID].unitType == UT_LORD
                || DAT_UnitsState::instance.units[unitID].unitType == UT_E_ENGINEER
                || DAT_UnitsState::instance.units[unitID].unitType == UT_TUNNELER
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_CATAPULT
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_TREBUCHET
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_MANGONEL
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_TOWER
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_BATTERINGRAM
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_SHIELD
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_BALLISTA
                || DAT_UnitsState::instance.units[unitID].unitType == UT_S_FBALLISTA)
                continue;

            if (this->aics[aicIndex].DefDiggingUnitMax == 0
                || DAT_UnitsState::instance.units[unitID].unitType == UT_E_ARCHER
                || DAT_UnitsState::instance.units[unitID].unitType == UT_E_XBOW
                || DAT_UnitsState::instance.units[unitID].someUnitStat4 == 0)
                MACRO_CALL_MEMBER(AICState_Func::assignUnitToATribe, this)(unitID);
            else
                MACRO_CALL_MEMBER(AICState_Func::aiAddUnitToMoatDiggerTribe, this)(unitID);
        }
    }
}
}
