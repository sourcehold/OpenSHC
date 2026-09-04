#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522520
        void TribesState::addUnitToSelected(uint unitID)
        {
            int index;

            index = (int)unitID / 16;
            *(ushort*)(DAT_UnitsState::instance.selectedUnitsBitFlags + index * 2)
                |= DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16];
        }

    }
}
}
