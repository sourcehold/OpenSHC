#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524E20
        void TribesState::applyLadderDestructionToTribeUnits(int param_1)
        {
            int unitID;
            BOOLEnum BVar1;
            int unitSelectionIndex = 0;
            if (0 < this->tribes[param_1].size) {
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        param_1, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[unitID].dying == 0)) {
                        if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0) {}
                        if (DAT_UnitsState::instance.units[unitID].field303_0x413 != 0) {}
                        if (DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging == 2) {}
                        if (DAT_UnitsState::instance.units[unitID].state.generic
                            == Map::Units::States::US_MELEE_ATTACK) {}
                        bool bVar2 = this->tribes[param_1].unknownBool02 == 0;
                        BVar1 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::computeLadderClimbPath,
                            DAT_UnitsState::ptr)(unitID, (uint)(bVar2), 0, (int)(bVar2));
                        if (BVar1) {
                            DAT_UnitsState::instance.units[unitID].state.generic
                                = Map::Units::States::US_DEATH_02 | Map::Units::States::US_STAND_UPUnk;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[param_1].size);
            }
        }

    }
}
}
