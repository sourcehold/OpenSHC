#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525470
        void TribesState::removeAllTribeUnits(int tribeID)
        {
            int _index = 0;
            short* const _size = &this->tribes[tribeID].size;
            while (_index < (int)*_size) {
                int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, _index++);
                DAT_UnitsState::instance.units[_unitID].logicalState = Map::Units::ULS_REMOVE;
            }
        }

    }
}
}
