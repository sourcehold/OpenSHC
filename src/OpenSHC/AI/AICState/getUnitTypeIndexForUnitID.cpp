#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC390
    AIVUnitType AICState::getUnitTypeIndexForUnitID(int unitID, int allowSlaveSlotForRanged)
    {
        UnitTypeShort unitType = DAT_UnitsState::instance.units[unitID].unitType;
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        UnitTypeInt effectiveUnitType;
        if (unitType == OpenSHC::Map::Units::UT_PEASANT) {
            effectiveUnitType = DAT_UnitsState::instance.units[unitID].unitTypeToChangeInto;
        } else {
            effectiveUnitType = unitType;
        }

        // 6 is the Caliph's AIC index: he fields slaves rather than the ranged units listed below
        if (DAT_GameState::instance.playerDataArray[owner].aiType - 1 != 6 && allowSlaveSlotForRanged != 0
            && DAT_GameState::instance.playerDataArray[owner].aivUnitLocationSlotLocationCount[0xd] > 0) {
            if (effectiveUnitType == OpenSHC::Map::Units::UT_E_ARCHER) {
                return OpenSHC::AI::AIVUT_SLAVE;
            }
            if (effectiveUnitType == OpenSHC::Map::Units::UT_E_XBOW) {
                return OpenSHC::AI::AIVUT_SLAVE;
            }
            if (effectiveUnitType == OpenSHC::Map::Units::UT_A_ARCHER) {
                return OpenSHC::AI::AIVUT_SLAVE;
            }
            if (effectiveUnitType == OpenSHC::Map::Units::UT_A_SLINGER) {
                return OpenSHC::AI::AIVUT_SLAVE;
            }
            if (effectiveUnitType == OpenSHC::Map::Units::UT_A_FIRETHROWER) {
                return OpenSHC::AI::AIVUT_SLAVE;
            }
        }

        for (int someUnitTypeIndex = 0; someUnitTypeIndex < 0x14; someUnitTypeIndex++) {
            if (DAT_SkirmishDefinedData::instance.SomeAIUnitTypeArray[someUnitTypeIndex] == effectiveUnitType) {
                return (AIVUnitType)someUnitTypeIndex;
            }
        }
        return OpenSHC::AI::AIVUT_NONE;
    }

}
}
