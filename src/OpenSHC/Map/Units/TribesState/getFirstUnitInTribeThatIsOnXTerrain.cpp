#include "../TribesState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005240D0
        int TribesState::getFirstUnitInTribeThatIsOnXTerrain(int selectionID)
        {
            int const _size = this->tribes[selectionID].size;
            int _unitSelectionIndex = 0;
            while (_unitSelectionIndex < _size) {
                int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    selectionID, _unitSelectionIndex);
                _unitSelectionIndex = _unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[_unitID].dying
                    && (DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[_unitID].tile]
                        & LogicHelpers::L_MOAT)) {
                    return _unitID;
                }
            }
            return 0;
        }

    }
}
}
