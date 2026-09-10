#include "../UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053BB70
        void UnitsState::setupUnitSharingCurrentTilePosition(int unitID)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingTileIDs, this)(
                unitID, this->units[unitID].tile);
        }

    }
}
}
