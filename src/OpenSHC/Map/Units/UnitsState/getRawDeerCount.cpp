#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537840
        int UnitsState::getRawDeerCount()
        {
            int _deerCount = 0;
            for (int unitID = 1; unitID < 2500; ++unitID) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                    _deerCount = _deerCount + 1;
                }
            }
            return _deerCount;
        }

    }
}
}
