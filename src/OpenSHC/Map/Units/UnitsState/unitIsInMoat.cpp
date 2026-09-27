#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534460
        BOOLEnum UnitsState::unitIsInMoat(int unitID)
        {
            return (BOOLEnum)((uint)DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] >> 30 & 1);
        }

    }
}
}
