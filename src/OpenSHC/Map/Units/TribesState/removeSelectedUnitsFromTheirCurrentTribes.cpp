#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525790
        void TribesState::removeSelectedUnitsFromTheirCurrentTribes(int playerID)
        {
            char unitRemovedFromTribeByID[1250];
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(unitRemovedFromTribeByID), '\0', unitRemovedFromTribeByID);
            for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].ifSelectedThenPlayerID == playerID) {
                    int const tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
                    if (tribeID > 0) {
                        MACRO_CALL_MEMBER(TribesState_Func::removeUnitFromThisTribeIfInTribe, this)(unitID, tribeID);
                        unitRemovedFromTribeByID[tribeID] = 1;
                    }
                }
            }
            for (int tribeID = 1; tribeID < (int)sizeof(unitRemovedFromTribeByID); ++tribeID) {
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
