#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525470
        void TribesState::removeAllTribeUnits(int param_1)
        {
            int iVar2;
            int iVar1 = 0;
            if (0 < this->tribes[param_1].size) {
                do {
                    iVar2 = iVar1 + 1;
                    iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, iVar1);
                    DAT_UnitsState::instance.units[iVar1].logicalState = Map::Units::ULS_REMOVE;
                    iVar1 = iVar2;
                } while (iVar2 < this->tribes[param_1].size);
            }
        }

    }
}
}
