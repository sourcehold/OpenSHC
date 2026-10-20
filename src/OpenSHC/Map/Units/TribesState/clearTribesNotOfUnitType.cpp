#include "../../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525970
        void TribesState::clearTribesNotOfUnitType(int playerID, int unitType)
        {
            Unit* psVar1;
            uint unitID;
            undefined1 _clearedTribes[1252];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)_clearedTribes;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                1250, '\0', (void*)((int)(_clearedTribes)));
            unitID = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                psVar1 = &DAT_UnitsState::instance.units[1];
                do {
                    if (psVar1->owner == playerID && psVar1->ifSelectedThenPlayerID
                        && (short)psVar1->unitType != unitType) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromThisTribeIfInTribe, this)(
                            unitID, (int)(psVar1->tribeID));
                        psVar1->ifSelectedThenPlayerID = 0;
                        DAT_UnitsState::instance.unitCountOfSelection[playerID]
                            = DAT_UnitsState::instance.unitCountOfSelection[playerID] + -1;
                        _clearedTribes[psVar1->tribeID] = 1;
                    }
                    unitID = unitID + 1;
                    psVar1 = psVar1 + 1;
                } while ((int)unitID < DAT_UnitsState::instance.maxUnitCount);
            }
            for (int _tribeID2 = 1; _tribeID2 < 1250; _tribeID2 = _tribeID2 + 1) {
                Tribe& _tribe = this->tribes[_tribeID2];
                if (_tribe.tribeState == 2) {
                    if (_tribe.selectionTargetUnitID == -1) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setTargetUnitForTribe, this)(_tribeID2);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(_tribeID2);
                }
            }
            ;
        }

    }
}
}
