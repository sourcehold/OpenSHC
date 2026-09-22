#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFB20
    void AICState::disbandAIPlayerSiegeUnits(int playerID)
    {
        for (int unitID = 1; unitID < 2500; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE)
                continue;
            if (DAT_UnitsState::instance.units[unitID].owner != playerID)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_CATAPULT
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_TREBUCHET
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_TOWER
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_BATTERINGRAM
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_SHIELD
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_FBALLISTA)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unknownSiegeTentRelated02 != 3)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType == 21)
                continue;

            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                DAT_UnitsState::instance.units[unitID].tribeID, OpenSHC::Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, unitID,
                DAT_UnitsState::instance.units[unitID].uid, 0);
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
    }

}
}
