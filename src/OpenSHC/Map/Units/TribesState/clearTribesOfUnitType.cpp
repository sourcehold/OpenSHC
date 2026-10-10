#include "../../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00525870
        void TribesState::clearTribesOfUnitType(int param_1, int param_2)
        {
            Unit* psVar1;
            int tribeID;
            uint unitID;
            short* psVar2;
            undefined1 local_4e8[1252];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_4e8;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                1250, '\0', (void*)((int)(local_4e8)));
            unitID = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                psVar1 = &DAT_UnitsState::instance.units[1];
                do {
                    if ((psVar1->owner == param_1) && (psVar1->ifSelectedThenPlayerID)) {
                        if ((short)psVar1->unitType == param_2) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromThisTribeIfInTribe, this)(
                                unitID, (int)(psVar1->tribeID));
                            psVar1->ifSelectedThenPlayerID = 0;
                            DAT_UnitsState::instance.unitCountOfSelection[param_1]
                                = DAT_UnitsState::instance.unitCountOfSelection[param_1] + -1;
                        }
                        local_4e8[psVar1->tribeID] = 1;
                    }
                    unitID = unitID + 1;
                    psVar1 = psVar1 + 0x248;
                } while ((int)unitID < DAT_UnitsState::instance.maxUnitCount);
            }
            tribeID = 1;
            psVar2 = &this->tribes[1].selectionTargetUnitID;
            do {
                if (psVar2[-0xd] == 2) {
                    if (*psVar2 == -1) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setTargetUnitForTribe, this)(tribeID);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(tribeID);
                }
                tribeID = tribeID + 1;
                psVar2 = psVar2 + 0x19a;
            } while (tribeID < 0x4e2);
            ;
        }

    }
}
}
