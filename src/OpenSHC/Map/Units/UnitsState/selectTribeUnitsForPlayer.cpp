#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00536190
        void UnitsState::selectTribeUnitsForPlayer(int playerID, int tribeID)
        {
            for (int indexInTribe = 0; indexInTribe < DAT_TribesState::instance.tribes[tribeID].size; ++indexInTribe) {
                int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                    DAT_TribesState::ptr)(tribeID, indexInTribe);
                this->units[unitID].ifSelectedThenPlayerID = (short)playerID;
                this->unitCountOfSelection[playerID] = this->unitCountOfSelection[playerID] + 1;
            }
        }

    }
}
}
