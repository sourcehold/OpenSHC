#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00536CF0
        void UnitsState::clearOrDeselectUnitFromSelection(int playerID, uint unitID, int unitType)
        {
            if (unitID == 0xffffffff) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearTribesOfUnitType, DAT_TribesState::ptr)(
                    playerID, unitType);
                return;
            }
            if (unitID == 0xfffffffe) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearTribesNotOfUnitType,
                    DAT_TribesState::ptr)(playerID, unitType);
                return;
            }
            if (unitID == 0) {
                this->unitCountOfSelection[playerID] = 0;
                for (DAT_CurrentUnitSlotID::instance = 1;
                    (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                    DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner == playerID) {
                        this->units[DAT_CurrentUnitSlotID::instance].ifSelectedThenPlayerID = 0;
                    }
                }
                return;
            }
            if (this->units[unitID].tribeID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                    unitID, this->units[unitID].tribeID);
            }
            if (this->units[unitID].ifSelectedThenPlayerID == 0) {
                return;
            }
            this->units[unitID].ifSelectedThenPlayerID = 0;
            this->unitCountOfSelection[playerID] = this->unitCountOfSelection[playerID] - 1;
        }

    }
}
}
