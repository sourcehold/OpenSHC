#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00524E20
        void TribesState::applyLadderDestructionToTribeUnits(int tribeID)
        {
            int i = 0;
            if (this->tribes[tribeID].size > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, i);
                    ++i;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0
                            || DAT_UnitsState::instance.units[unitID].field_0x413 != 0
                            || DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging == 2
                            || DAT_UnitsState::instance.units[unitID].state.generic == States::US_MELEE_ATTACK) {
                            return;
                        }
                        BOOLEnum climbing;
                        if (this->tribes[tribeID].unknownBool02 != 0) {
                            climbing = MACRO_CALL_MEMBER(UnitsState_Func::computeLadderClimbPath, DAT_UnitsState::ptr)(
                                unitID, 0, 0, 0);
                        } else {
                            climbing = MACRO_CALL_MEMBER(UnitsState_Func::computeLadderClimbPath, DAT_UnitsState::ptr)(
                                unitID, 1, 0, 1);
                        }
                        if (climbing != FALSE) {
                            DAT_UnitsState::instance.units[unitID].state.generic
                                = States::US_DEATH_02 | States::US_STAND_UPUnk;
                        }
                    }
                } while (i < this->tribes[tribeID].size);
            }
        }

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
