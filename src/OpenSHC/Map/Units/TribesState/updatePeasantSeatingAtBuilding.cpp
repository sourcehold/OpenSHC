#include "../../../Map.func.hpp"
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

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522210
        void TribesState::updatePeasantSeatingAtBuilding(int param_1, int param_2, int param_3)
        {
            int iVar4;
            int local_8;
            int sVar1 = DAT_BuildingsState::instance.buildings[param_1].owner;
            local_8 = 0;
            if (param_2 <= 1) {
                param_2 = 1;
            } else if (param_2 <= 3) {
                param_2 = ((byte)SEC_RNG::instance.currentNumber2 & 1) + 1;
            } else if (param_2 <= 7) {
                param_2 = ((byte)SEC_RNG::instance.currentNumber2 & 3) + 1;
            } else if (param_2 <= 0xf) {
                param_2 = ((byte)SEC_RNG::instance.currentNumber2 & 7) + 1;
            } else {
                param_2 = ((byte)SEC_RNG::instance.currentNumber2 & 0xf) + 1;
            }
            iVar4 = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                Unit* _unit = &DAT_UnitsState::instance.units[1];
                do {
                    if (_unit->logicalState == Map::Units::ULS_NORMAL && _unit->dying == 0 && _unit->owner == sVar1
                        && _unit->unitType == Map::Units::UT_PEASANT
                        && _unit->state.generic == Map::Units::States::US_STAND_UPUnk
                        && _unit->workplaceBuildingID_1 == param_1) {
                        local_8 = local_8 + 1;
                        /*
                          fixme: the short at Unit + 0x390 is declared as padding in the
                          generated header; it is the peasant's pending-sit flag.
                         */
                        *(short*)_unit->padding_0x390 = 0;
                        if (param_3 == 1) {
                            _unit->peasantAlwaysZero = 0;
                        }
                        if (local_8 == param_2) {
                            _unit->peasantAlwaysZero = 1;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(iVar4);
                        } else if (_unit->peasantAlwaysZero == 0) {
                            *(short*)_unit->padding_0x390 = 1;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(
                                iVar4);
                        }
                    }
                    iVar4 = iVar4 + 1;
                    _unit = _unit + 1;
                } while (iVar4 < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
