#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::Map::Units::States::UnitState;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFB20
    void AICState ::disbandAIPlayerSiegeUnits(int playerID)

    {

        Unit* _unit;

        int _unitIDCounter;

        UnitTypeShort _unitType;

        _unitIDCounter = 1;

        _unit = &DAT_UnitsState::instance.units[1];

        do {

            if ((((_unit->logicalState != OpenSHC::Map::Units::ULS_INVISIBLE) && (_unit->owner == playerID))
                    && (((_unitType = _unit->unitType,
                             _unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                                 || (((_unitType == OpenSHC::Map::Units::UT_S_TREBUCHET
                                          || (_unitType == OpenSHC::Map::Units::UT_S_TOWER))
                                     || (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM))))
                        || ((_unitType == OpenSHC::Map::Units::UT_S_SHIELD
                            || (_unitType == OpenSHC::Map::Units::UT_S_FBALLISTA))))))
                && ((_unit->unknownSiegeTentRelated02 == 3 && (_unit->aiUnitBehaviourType != 0x15)))) {

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                    (int)_unit->tribeID, OpenSHC::Map::Units::UIT_EXIT_SIEGE_EQUIPMENT, _unitIDCounter, _unit->uid, 0);

                /*
                        shouldn't logicalState be set to something too? */

                (_unit->state).generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }

            _unit = _unit + 0x248;

            _unitIDCounter = _unitIDCounter + 1;

        } while ((int)_unit < 0x165141a);

        return;
    }

}
}
