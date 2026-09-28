#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459C10
    void GameStateStructures::assignSelectionToKey(int number, int tribeID)
    {
        int slotID = 0;
        for (int tribeIndex = 0; tribeIndex < DAT_TribesState::instance.tribes[tribeID].size; tribeIndex++) {
            int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                DAT_TribesState::ptr)(tribeID, tribeIndex);
            if ((DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL)
                || (DAT_UnitsState::instance.units[unitID].dying != 0)
                || (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_LORD)) {
                continue;
            }
            this->hotkeyTribes[number].units[slotID].id = unitID;
            this->hotkeyTribes[number].units[slotID].uid = DAT_UnitsState::instance.units[unitID].uid;
            slotID = slotID + 1;
            /*
              If unit already bound to other key, delete it from key array and shift the array elements after
              that to fill the hole.
             */
            for (int hotkeyID = 0; hotkeyID < 10; hotkeyID++) {
                if (hotkeyID == number) {
                    continue;
                }
                for (int slot = 0; slot < 2500; slot++) {
                    if (this->hotkeyTribes[hotkeyID].units[slot].id == -1) {
                        break;
                    }
                    if (this->hotkeyTribes[hotkeyID].units[slot].id != unitID) {
                        continue;
                    }
                    while (slot < 2499) {
                        this->hotkeyTribes[hotkeyID].units[slot].id
                            = this->hotkeyTribes[hotkeyID].units[slot + 1].id;
                        this->hotkeyTribes[hotkeyID].units[slot].uid
                            = this->hotkeyTribes[hotkeyID].units[slot + 1].uid;
                        if (this->hotkeyTribes[hotkeyID].units[slot].id == -1) {
                            break;
                        }
                        slot = slot + 1;
                    }
                    this->hotkeyTribes[hotkeyID].units[slot].id = -1;
                    this->hotkeyTribes[hotkeyID].units[slot].uid = -1;
                    break;
                }
            }
        }
    }
}
}
