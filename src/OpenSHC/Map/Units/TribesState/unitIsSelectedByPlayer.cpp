#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522550
        BOOLEnum TribesState::unitIsSelectedByPlayer(uint unitID)
        {
            return (DAT_UnitsState::instance.selectedUnitsBitFlags[(int)unitID / 16]
                       & DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16])
                != 0;
        }

    }
}
}
