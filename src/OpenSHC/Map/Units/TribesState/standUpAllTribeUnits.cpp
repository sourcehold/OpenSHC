#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525370
        void TribesState::standUpAllTribeUnits(int param_1)
        {
            int iVar1;
            /*
              A cursor on the size field rather than on the tribe: diff_anchor's territory -
              the original's `lea eax, [eax + ebp + 0x5c]` points at Tribe::size and reads
              it as [eax], where a Tribe* reads it as [eax + 0x34].
             */
            short* _tribeSize = &this->tribes[param_1].size;
            int unitSelectionIndex = 0;
            if (0 < *_tribeSize) {
                do {
                    iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[iVar1].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[iVar1].dying == 0)) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(iVar1);
                        DAT_UnitsState::instance.units[iVar1].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[iVar1].rabbitMovementSlowdown = '\0';
                    }
                } while (unitSelectionIndex < *_tribeSize);
            }
        }

    }
}
}
