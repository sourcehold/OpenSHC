#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F550
        BOOLEnum UnitsState::ifAnyUnitOnSameTileIsLadder(int tile)
        {
            for (int unitID = DAT_TileMapState::instance.UnitLayer[tile]; unitID != 0;
                unitID = this->units[unitID].nextUnitOnTheSameTile) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_LADDER
                    && this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
