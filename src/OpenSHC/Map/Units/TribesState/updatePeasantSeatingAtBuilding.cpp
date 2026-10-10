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
            short sVar1;
            uint uVar2;
            short* psVar3;
            int iVar4;
            int local_8;
            sVar1 = DAT_BuildingsState::instance.buildings[param_1].owner;
            local_8 = 0;
            if (param_2 < 2) {
                param_2 = 1;
            } else if (param_2 < 4) {
                param_2 = ((byte)SEC_RNG::instance.currentNumber2 & 1) + 1;
            } else {
                if (param_2 < 8) {
                    uVar2 = (byte)SEC_RNG::instance.currentNumber2 & 3;
                } else {
                    if (param_2 < 0x10) {
                        param_2 = ((byte)SEC_RNG::instance.currentNumber2 & 7) + 1;
                        goto LAB_00522291;
                    }
                    uVar2 = (byte)SEC_RNG::instance.currentNumber2 & 0xf;
                }
                param_2 = uVar2 + 1;
            }
        LAB_00522291:
            iVar4 = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                psVar3 = &DAT_UnitsState::instance.units[1].dying;
                do {
                    if (psVar3[-0x10a] == Map::Units::ULS_NORMAL && *psVar3 == 0 && psVar3[-0x105] == sVar1
                        && psVar3[-0x109] == Map::Units::UT_PEASANT
                        && ((UnitStateUnion*)(psVar3 + 0x10))->generic == Map::Units::States::US_STAND_UPUnk
                        && psVar3[0x4c] == param_1) {
                        local_8 = local_8 + 1;
                        psVar3[0x78] = 0;
                        if (param_3 == 1) {
                            psVar3[0x77] = 0;
                        }
                        if (local_8 == param_2) {
                            psVar3[0x77] = 1;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(iVar4);
                        } else if (psVar3[0x77] == 0) {
                            psVar3[0x78] = 1;
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::sitDownIfStanding, DAT_UnitsState::ptr)(
                                iVar4);
                        }
                    }
                    iVar4 = iVar4 + 1;
                    psVar3 = psVar3 + 0x248;
                } while (iVar4 < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
