#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitHasBecomeIdle.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::States::UnitState;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x00530A90
    void __stdcall Units ::UpdateBurningAnimal2()

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

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = ((UnitState)2);

            return;
        }

        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;

        int iVar1 = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber;

        if (0x11 <= iVar1) {

            DAT_UnitHasBecomeIdle::instance = 1;

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;

            return;
        }

        bool bVar3 = DAT_UnitHasBecomeIdle::instance != 0;

        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = iVar1 + 1;

        if (bVar3) {

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
        }

        return;
    }

}
}