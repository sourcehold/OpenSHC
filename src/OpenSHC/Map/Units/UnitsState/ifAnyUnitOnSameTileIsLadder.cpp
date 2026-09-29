#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F550
        BOOLEnum UnitsState::ifAnyUnitOnSameTileIsLadder(int tile)
        {
            for (int unitID = (short)DAT_TileMapState::instance.UnitLayer[tile]; unitID != 0;
                unitID = (short)this->units[unitID].nextUnitOnTheSameTile) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_LADDER
                    && this->units[unitID].state.generic == (UnitState)3) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
