#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F4E0
        BOOLEnum UnitsState::isUnitRegisteredOnItsOwnTile(int unitID)
        {
            int _tile = this->units[unitID].tile;
            int _otherUnitID = DAT_TileMapState::instance.UnitLayer[_tile];
            if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return TRUE;
            }
            if (this->units[unitID].unknownTestAgainst0_2 != 0) {
                return TRUE;
            }
            if (_tile == 0) {
                return FALSE;
            }
            for (; _otherUnitID != 0; _otherUnitID = this->units[_otherUnitID].nextUnitOnTheSameTile) {
                if (_otherUnitID == unitID) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
