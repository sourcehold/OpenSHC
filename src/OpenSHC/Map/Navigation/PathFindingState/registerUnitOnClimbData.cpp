#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Attempts to register unit param_2 on climb data slot param_1. Returns 0 if the climb system is   disabled
          (field63_0xc0 == 0), -1 if the slot is unusable or already at capacity (50 units), or 1   on success. On
          success increments numberOfUnitsUsing, stores the unit ID and UID in the first   free slot, and copies
          climbDataRelated to the unit (zeroed for climb types 3, 4, and 5).      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4C70
        undefined4 PathFindingState::registerUnitOnClimbData(int param_1, int param_2)
        {
            int iVar1;
            int* piVar2;
            if (this->field63_0xc0 == 0) {
                return (undefined4)(0);
            }
            if ((this->climbData[param_1].canBeUsed != 0)
                && (iVar1 = this->climbData[param_1].numberOfUnitsUsing, iVar1 < 0x32)) {
                this->climbData[param_1].numberOfUnitsUsing = iVar1 + 1;
                DAT_UnitsState::instance.units[param_2].climbDataRelated = this->climbData[param_1].climbDataRelated;
                if (this->climbData[param_1].type == 3) {
                    DAT_UnitsState::instance.units[param_2].climbDataRelated = 0;
                }
                if (this->climbData[param_1].type == 4) {
                    DAT_UnitsState::instance.units[param_2].climbDataRelated = 0;
                }
                if (this->climbData[param_1].type == 5) {
                    DAT_UnitsState::instance.units[param_2].climbDataRelated = 0;
                }
                iVar1 = 0;
                piVar2 = &this->climbData[param_1].unitID1;
                do {
                    if (*piVar2 == 0) {
                        (&this->climbData[param_1].unitID1)[iVar1] = param_2;
                        (&this->climbData[param_1].unitUID1)[iVar1] = DAT_UnitsState::instance.units[param_2].uid;
                        return (undefined4)(1);
                    }
                    iVar1 = iVar1 + 1;
                    piVar2 = piVar2 + 1;
                } while (iVar1 < 0x32);
                return (undefined4)(1);
            }
            return (undefined4)(0xffffffff);
        }

    }
}
}
