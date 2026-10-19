#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005240D0
        int TribesState::getFirstUnitInTribeThatIsOnXTerrain(int selectionID)
        {
            int _unitID;
            int iVar1 = (int)this->tribes[selectionID].size;
            int _unitSelectionIndex = 0;
            if (0 < iVar1) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        selectionID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[_unitID].dying == 0
                        && (DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[_unitID].tile]
                            & 0x40000000U)) {
                        return _unitID;
                    }
                } while (_unitSelectionIndex < iVar1);
            }
            return 0;
        }

    }
}
}
