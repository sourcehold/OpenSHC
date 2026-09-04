#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */

        // FUNCTION: STRONGHOLDCRUSADER 0x00534460
        BOOLEnum UnitsState::unitIsInMoat(int unitID)

        {
            return (uint)DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] >> 0x1e & TRUE;
        }

    }
}
}
