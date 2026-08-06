#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFBC0
    int AICState::countSiegeEngineUnits(int playerID)
    {
        int _count = 0;
        Unit* _units = &DAT_UnitsState::instance.units[0];

        for (int i = 1; i < 2500; i += 1) {
            // Unit[1]
            if (_units[i].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE && _units[i].owner == playerID
                && _units[i].unknownSiegeTentRelated02 == 3 && _units[i].aiUnitBehaviourType != 0x15) {
                UnitTypeShort t = _units[i].unitType;
                if (t == OpenSHC::Map::Units::UT_S_CATAPULT || t == OpenSHC::Map::Units::UT_S_TREBUCHET
                    || t == OpenSHC::Map::Units::UT_S_TOWER || t == OpenSHC::Map::Units::UT_S_BATTERINGRAM
                    || t == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                    _count = _count + 1;
                }
            }

            // Compiler unrolled the loop because 2499 is divisible by 3?
            // // Unit[2]
            // if (_units[i + 1].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE && _units[i + 1].owner == playerID
            //     && _units[i + 1].unknownSiegeTentRelated02 == 3 && _units[i + 1].aiUnitBehaviourType != 0x15) {
            //     UnitTypeShort t = _units[i + 1].unitType;
            //     if (t == OpenSHC::Map::Units::UT_S_CATAPULT || t == OpenSHC::Map::Units::UT_S_TREBUCHET
            //         || t == OpenSHC::Map::Units::UT_S_TOWER || t == OpenSHC::Map::Units::UT_S_BATTERINGRAM
            //         || t == OpenSHC::Map::Units::UT_S_FBALLISTA) {
            //         _count = _count + 1;
            //     }
            // }

            // // Unit[3]
            // if (_units[i + 2].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE && _units[i + 2].owner == playerID
            //     && _units[i + 2].unknownSiegeTentRelated02 == 3 && _units[i + 2].aiUnitBehaviourType != 0x15) {
            //     UnitTypeShort t = _units[i + 2].unitType;
            //     if (t == OpenSHC::Map::Units::UT_S_CATAPULT || t == OpenSHC::Map::Units::UT_S_TREBUCHET
            //         || t == OpenSHC::Map::Units::UT_S_TOWER || t == OpenSHC::Map::Units::UT_S_BATTERINGRAM
            //         || t == OpenSHC::Map::Units::UT_S_FBALLISTA) {
            //         _count = _count + 1;
            //     }
            // }
        };

        return _count;
    }

}
}
