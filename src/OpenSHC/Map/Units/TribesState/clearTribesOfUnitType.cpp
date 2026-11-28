#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525870
        void TribesState::clearTribesOfUnitType(int playerID, int unitType)
        {
            char clearedTribes[1250];
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(clearedTribes), '\0', clearedTribes);
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].owner == playerID
                    && DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID != 0) {
                    if (DAT_UnitsState::instance.units[unitID].unitType == unitType) {
                        MACRO_CALL_MEMBER(TribesState_Func::removeUnitFromThisTribeIfInTribe, this)(
                            unitID, DAT_UnitsState::instance.units[unitID].tribeID);
                        DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID = 0;
                        DAT_UnitsState::instance.unitCountOfSelection[playerID] -= 1;
                    }
                    clearedTribes[DAT_UnitsState::instance.units[unitID].tribeID] = 1;
                }
            }
            for (int tribeID = 1; tribeID < (int)sizeof(clearedTribes); ++tribeID) {
                if (this->tribes[tribeID].tribeState == 2) {
                    if (this->tribes[tribeID].selectionTargetUnitID == -1) {
                        MACRO_CALL_MEMBER(TribesState_Func::setTargetUnitForTribe, this)(tribeID);
                    }
                    MACRO_CALL_MEMBER(TribesState_Func::setWhetherTribeContainsAnyUnits, this)(tribeID);
                }
            }
        }

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
