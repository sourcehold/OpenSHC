#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Logic1;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00534460
        BOOLEnum UnitsState::unitIsInMoat(int unitID)
        {
            return DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] >> 30 & TRUE;
        }

    }
}
}
