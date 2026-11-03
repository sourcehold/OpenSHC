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
        void TribesState::moveTribeToNearbyClearTile(int tribeID)
        {
            int const _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
            uint const x0 = DAT_UnitsState::instance.units[_targetUnitID].x;
            uint const y0 = DAT_UnitsState::instance.units[_targetUnitID].y;
            for (int candidate = 0; candidate < 40; ++candidate) {
                uint const x1 = DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[candidate].x + x0;
                uint const y1 = DAT_UnitSelectionDefinedData::instance.field1608_0xcc4[candidate].y + y0;
                if (x1 <= 399 && y1 <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] != 0
                    && MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribePathToDestinationClear, this)(
                           tribeID, x0, y0, x1, y1)
                        != 0) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                        tribeID, x1, y1, 0, 0, Map::Units::Instructions::UMSE_0);
                    return;
                }
            }
        }

    }
}
}
