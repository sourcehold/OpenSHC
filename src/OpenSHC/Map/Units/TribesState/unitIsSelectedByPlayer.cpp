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
            uint uVar1 = tribeID & 0x8000000f;
            if ((int)uVar1 < 0) {
                uVar1 = (uVar1 - 1 | 0xfffffff0) + 1;
            }
            return (uint)((DAT_UnitSelectionDefinedData::instance.BitMaskHelper[uVar1]
                & *(ushort*)(DAT_UnitsState::instance.selectedUnitsBitFlags + ((int)tribeID / 16) * 2)));
        }

    }
}
}
