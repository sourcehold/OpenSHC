#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        /*
          The size is read through a pointer the original takes once
          (`lea ebx, [eax + edi + 0x5c]`) and re-reads at the bottom of the loop; the
          decompiler's shuffle through a single variable is an artefact of the index and
          the unit id sharing no register.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00525470
        void TribesState::removeAllTribeUnits(int param_1)
        {
            int _index = 0;
            short* const _size = &this->tribes[param_1].size;
            if (0 < *_size) {
                do {
                    int const _unitID
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            param_1, _index);
                    _index = _index + 1;
                    DAT_UnitsState::instance.units[_unitID].logicalState = Map::Units::ULS_REMOVE;
                } while (_index < (int)*_size);
            }
        }

    }
}
}
