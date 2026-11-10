#include "../Units.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00530A90
    void Units::UpdateBurningAnimal2()
    {
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].calculatedOwnerPlayerIndex = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].dying = 1;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].isSelected = 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].disappearFadeAlphaCountdown = 8;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
            == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_STATE_2Unk;
            return;
        }
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
        int const animationCycle = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber;
        if (animationCycle >= 17) {
            DAT_UnitHasBecomeIdle::instance = 1;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        bool const unitHadBecomeIdle = DAT_UnitHasBecomeIdle::instance != 0;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = animationCycle + 1;
        if (unitHadBecomeIdle) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
        }
    }
}
}
