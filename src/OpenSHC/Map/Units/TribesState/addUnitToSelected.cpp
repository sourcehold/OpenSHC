#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522520
        void TribesState::addUnitToSelected(int unitID)
        {
            int const bitFlagsIndex = unitID / 16;
            int const bitMaskIndex = unitID % 16;
            ((short*)DAT_UnitsState::instance.selectedUnitsBitFlags)[bitFlagsIndex]
                |= DAT_UnitSelectionDefinedData::instance.BitMaskHelper[bitMaskIndex];
        }

    }
}
}
