#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Navigation::Algorithms::XYPair;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052A640
        void TribesState::moveTribeToNearbyClearTile(int param_1)
        {
            int iVar3;
            int* piVar4;
            uint uVar5;
            uint x1;
            uint y1;
            short sVar1 = this->tribes[param_1].selectionTargetUnitID;
            uVar5 = (uint)DAT_UnitsState::instance.units[sVar1].x;
            uint uVar2 = (uint)DAT_UnitsState::instance.units[sVar1].y;
            piVar4 = &DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[0].y;
            while (true) {
                x1 = ((XYPair*)(piVar4 + -1))->x + uVar5;
                y1 = *piVar4 + uVar2;
                if (x1 < 400 && y1 < 400 && *(char*)(y1 * 400 + 0x21aec98 + x1) != '\0'
                    && (iVar3 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribePathToDestinationClear, this)(
                            param_1, uVar5, uVar2, x1, y1),
                        iVar3 != 0))
                    break;
                piVar4 = piVar4 + 2;
                if (0xb4df43 < (int)piVar4) {}
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                param_1, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
        }

    }
}
}
