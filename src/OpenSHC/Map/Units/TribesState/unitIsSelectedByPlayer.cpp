#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522550
        BOOLEnum TribesState::unitIsSelectedByPlayer(uint tribeID)
        {
            return ((int)DAT_UnitsState::instance.selectedUnitsBitFlags[(int)tribeID / 16]
                       & (int)DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)tribeID % 16])
                != 0;
        }

    }
}
}
