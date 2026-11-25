#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522210
        void TribesState::updatePeasantSeatingAtBuilding(int buildingID, int peasantCountUnk, int resetAlwaysZeroUnk)
        {
            int const _owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
            int _matchingPeasantCount = 0;
            if (peasantCountUnk <= 1) {
                peasantCountUnk = 1;
            } else if (peasantCountUnk <= 3) {
                peasantCountUnk = (SEC_RNG::instance.currentNumber2 & 1) + 1;
            } else if (peasantCountUnk <= 7) {
                peasantCountUnk = (SEC_RNG::instance.currentNumber2 & 3) + 1;
            } else if (peasantCountUnk <= 15) {
                peasantCountUnk = (SEC_RNG::instance.currentNumber2 & 7) + 1;
            } else {
                peasantCountUnk = (SEC_RNG::instance.currentNumber2 & 15) + 1;
            }
            for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[unitID].dying
                    && DAT_UnitsState::instance.units[unitID].owner == _owner
                    && DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_PEASANT
                    && DAT_UnitsState::instance.units[unitID].state.generic == Map::Units::States::US_STAND_UPUnk
                    && DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1 == buildingID) {
                    ++_matchingPeasantCount;
                    DAT_UnitsState::instance.units[unitID].peasantSeatingRelated = 0;
                    if (resetAlwaysZeroUnk == 1) {
                        DAT_UnitsState::instance.units[unitID].peasantAlwaysZero = 0;
                    }
                    if (_matchingPeasantCount == peasantCountUnk) {
                        DAT_UnitsState::instance.units[unitID].peasantAlwaysZero = 1;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(unitID);
                    } else if (DAT_UnitsState::instance.units[unitID].peasantAlwaysZero == 0) {
                        DAT_UnitsState::instance.units[unitID].peasantSeatingRelated = 1;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(unitID);
                    }
                }
            }
        }

    }
}
}
