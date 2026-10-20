#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Navigation::Algorithms::XYPair;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052A700
        int TribesState::moveTribeToIndexedNearbyTile(int param_1)
        {
            uint uVar3;
            int* piVar6;
            uint uVar7;
            int sVar1 = this->tribes[param_1].selectionTargetUnitID;
            uint uVar4 = (uint)DAT_UnitsState::instance.units[sVar1].y;
            uVar7 = (uint)DAT_UnitsState::instance.units[sVar1].x;
            int iVar2 = (int)this->tribes[param_1].someIndex;
            /*
              Only the remainder is named. The original divides once, with `cdq`, `mov ecx,
              0x28`, `idiv ecx`, and the unreachable arm returns the quotient that same
              instruction left in EAX; naming the quotient in a local of its own turns the
              division into a reciprocal multiply and costs a stack slot.
             */
            int iVar5 = iVar2 % 40;
            if (iVar5 <= 0) {
                iVar5 = 0;
            } else if (39 < iVar5) {
                return iVar2 / 40;
            }
            piVar6 = &DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[iVar5].y;
            do {
                uint const x1 = piVar6[-1] + uVar7;
                uint const y1 = *piVar6 + uVar4;
                uVar3 = uVar4;
                if (x1 <= 399 && y1 <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] != 0) {
                    iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribePathToDestinationClear, this)(
                        param_1, uVar7, uVar4, x1, y1);
                    uVar3 = 0;
                    if (iVar2) {
                        iVar2 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                            param_1, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
                        return iVar2;
                    }
                }
                piVar6 = piVar6 + 2;
            } while ((int)piVar6 < 0xb4df44);
            return (int)(uVar3);
        }

    }
}
}
