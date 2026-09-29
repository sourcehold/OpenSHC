#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E820
        void UnitsState::commitUnitLocation(int unitID)
        {
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].tunnelerFinishedDigging = 0;
            this->units[unitID].field105_0xe8 = 0;
            this->units[unitID].unknownMovementRelated_0x2d2 = 0;
            this->units[unitID].movementRelated = 8;
            this->units[unitID].unknownTestAgainst0_2 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
        }

    }
}
}
