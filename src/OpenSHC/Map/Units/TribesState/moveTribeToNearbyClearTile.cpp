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

        // FUNCTION: STRONGHOLDCRUSADER 0x0052A640
        void TribesState::moveTribeToNearbyClearTile(int param_1)
        {
            int sVar1 = this->tribes[param_1].selectionTargetUnitID;
            uint uVar5 = (uint)DAT_UnitsState::instance.units[sVar1].x;
            uint uVar2 = (uint)DAT_UnitsState::instance.units[sVar1].y;
            /*
              The import walked a cursor over the candidate offsets and left the loop's exit
              test as `if (0xb4df43 < (int)piVar4) {}`, so it fell out of the `while (true)`
              only through the `break` and then issued a move order with whatever x1/y1 the
              last candidate had left behind. The original returns without an order when no
              candidate is reachable. 0xb4df44 is one past field1608_0xcc4[39].y, so the
              loop runs over all 40 entries.
             */
            for (int _candidate = 0; _candidate < 40; _candidate = _candidate + 1) {
                uint const x1 = DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[_candidate].x + uVar5;
                uint const y1 = DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[_candidate].y + uVar2;
                if (x1 <= 399 && y1 <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] != 0
                    && MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribePathToDestinationClear, this)(
                           param_1, uVar5, uVar2, x1, y1)
                        != 0) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                        param_1, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
                    return;
                }
            }
        }

    }
}
}
