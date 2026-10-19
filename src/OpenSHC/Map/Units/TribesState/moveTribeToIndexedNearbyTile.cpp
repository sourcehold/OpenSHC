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
            uint x1;
            uint y1;
            short sVar1 = this->tribes[param_1].selectionTargetUnitID;
            uint uVar4 = (uint)DAT_UnitsState::instance.units[sVar1].y;
            uVar7 = (uint)DAT_UnitsState::instance.units[sVar1].x;
            int iVar2 = (int)this->tribes[param_1].someIndex;
            int iVar5 = iVar2 % 0x28;
            if (iVar5 <= 0) {
                iVar5 = 0;
            } else if (0x27 < iVar5) {
                return iVar2 / 0x28;
            }
            piVar6 = &DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[iVar5].y;
            do {
                x1 = ((XYPair*)(piVar6 + -1))->x + uVar7;
                y1 = *piVar6 + uVar4;
                uVar3 = uVar4;
                if (x1 < 400 && y1 < 400 && *(char*)(y1 * 400 + (int)DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400 + x1) != '\0') {
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
