#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A4D0
        int UnitsState::findActiveSiegeEngineForTribe(int playerID)
        {
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].owner != playerID) {
                    continue;
                }
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].isSelectable_OR_matchTime == 0) {
                    continue;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                    return unitID;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                    return unitID;
                }
            }
            return 0;
        }

    }
}
}
