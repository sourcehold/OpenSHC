#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525470
        void TribesState::removeAllTribeUnits(int tribeID)
        {
            int _index = 0;
            while (_index < this->tribes[tribeID].size) {
                int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, _index++);
                DAT_UnitsState::instance.units[_unitID].logicalState = Map::Units::ULS_REMOVE;
            }
        }

    }
}
}
