#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005369F0
        BOOLEnum UnitsState::selectionHasUnmannedSiegeEngine(int unitID)
        {
            if (this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300 != 0) {
                return FALSE;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_S_CATAPULT:
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
            case OpenSHC::Map::Units::UT_S_TOWER:
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
            case OpenSHC::Map::Units::UT_S_SHIELD:
                return (BOOLEnum)(this->selectionEngineers != 0);
            }
            return FALSE;
        }

    }
}
}
