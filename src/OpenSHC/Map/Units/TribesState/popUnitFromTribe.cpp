#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525B70
        int TribesState::popUnitFromTribe(int tribeID)
        {
            int const unitID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, 0);
            if (unitID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, this)(unitID, tribeID);
            }
            return unitID;
        }

    }
}
}
