#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533FC0
        void UnitsState::despawnUnreachableUnit(int unitID)
        {
            if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                return;
            }
            if ((short)this->units[unitID].unitType >= 0x37 && (short)this->units[unitID].unitType <= 0x39) {
                return;
            }
            if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] & 0x100U) == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::someBinaryAlgFunctionPathFinding,
                    DAT_PathFindingState::ptr)(unitID)
                == 0) {
                return;
            }
            this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            this->units[unitID].disappearFadeAlphaCountdown = 0;
        }

    }
}
}
