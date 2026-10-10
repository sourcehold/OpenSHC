#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525130
        void TribesState::applyMovementDistanceToUnitsInTribe(int param_1)
        {
            int iVar1;
            int unitSelectionIndex = 0;
            if (0 < this->tribes[param_1].size) {
                do {
                    iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[iVar1].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[iVar1].dying == 0)) {
                        DAT_UnitsState::instance.units[iVar1].movementDistance
                            = DAT_TileMapState::instance.CertainPathLayer[DAT_UnitsState::instance.units[iVar1].tile];
                    }
                } while (unitSelectionIndex < this->tribes[param_1].size);
            }
        }

    }
}
}
