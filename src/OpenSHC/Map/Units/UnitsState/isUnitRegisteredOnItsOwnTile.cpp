#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F4E0
        undefined4 UnitsState::isUnitRegisteredOnItsOwnTile(int unitID)
        {
            int _tile = this->units[unitID].tile;
            int _otherUnitID = (short)DAT_TileMapState::instance.UnitLayer[_tile];
            if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return 1;
            }
            if (this->units[unitID].unknownTestAgainst0_2 != 0) {
                return 1;
            }
            if (_tile == 0) {
                return 0;
            }
            while (_otherUnitID != 0) {
                if (_otherUnitID == unitID) {
                    return 1;
                }
                _otherUnitID = (short)this->units[_otherUnitID].nextUnitOnTheSameTile;
            }
            return 0;
        }

    }
}
}
