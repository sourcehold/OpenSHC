#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522F70
        void TribesState::spawnUnitsForAITribe(
            undefined4 param_1, int param_2, int param_3, int param_4, UnitType param_5, int param_6, int param_7)
        {
            int unitID;
            if (((0 < param_2) || (0 < param_3)) && 0 < param_6) {
                /*
                  The Y scaling is computed first: the original has `lea ebx, [edx*8]` for
                  param_3 and `lea ebp, [ecx*8]` for param_2, which is the opposite register
                  pairing from declaring X first.
                 */
                int microYPosition = param_3 * 8;
                int microXPosition = param_2 * 8;
                param_2 = param_6;
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        param_4, param_4, microXPosition, microYPosition, 8, param_5);
                    if (unitID) {
                        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = param_7;
                        UnitTypeShort UVar1 = DAT_UnitsState::instance.units[unitID].unitType;
                        /*
                          The call is written out in both arms. The original pushes the
                          behaviour constant straight from each one - `push 0x14`,
                          `jmp 0x2`, `push 0x11` - and shares the `push eax` and the call
                          after them, which is what MSVC produces when it tail-merges two
                          call sites. Assigning a local and calling once makes it
                          materialise the value instead (`mov ecx, 0x14` / `mov ecx, 0x11`
                          and a `push ecx`), five bytes more, and that is what every
                          branch displacement in this function was out by. Declaring the
                          local at its use rather than at function scope does not change
                          it; the two call sites do.
                         */
                        if (UVar1 == Map::Units::UT_E_ARCHER || UVar1 == Map::Units::UT_E_XBOW
                            || UVar1 == Map::Units::UT_A_ARCHER || UVar1 == Map::Units::UT_A_SLINGER
                            || UVar1 == Map::Units::UT_A_HARCHER || UVar1 == Map::Units::UT_A_FIRETHROWER) {
                            MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(
                                unitID, 0x11);
                        } else {
                            MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(
                                unitID, 0x14);
                        }
                    }
                    param_2 = param_2 + -1;
                } while (param_2);
            }
        }

    }
}
}
