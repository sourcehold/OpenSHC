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
                    /*
                      A post-increment: the original copies the index out before bumping it
                      (`mov eax, esi`, `push eax`, then `add esi, 1` before the call at
                      0x525499), which is what the decompiler printed as a spare variable
                      carrying the old value across the call.
                     */
                    int const _unitID
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            param_1, _index++);
                    DAT_UnitsState::instance.units[_unitID].logicalState = Map::Units::ULS_REMOVE;
                } while (_index < (int)*_size);
            }
        }

    }
}
}
