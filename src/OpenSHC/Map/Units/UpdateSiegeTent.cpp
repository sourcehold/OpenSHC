#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x005307B0
    void __stdcall Units ::UpdateSiegeTent()

    {

        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;

        int uVar5 = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng + 1 & 3;

        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = uVar5;

        if (4 <= uVar5) {

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 2;
        }

        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber
            = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber + 1;

        if (500 < DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber) {

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_TRANSITIONING;

            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng % 4 < 2) {

                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                    = OpenSHC::Map::Units::UT_S_CATAPULT;
            } else {

                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                    = OpenSHC::Map::Units::UT_S_TREBUCHET;
            }

            int iVar4 = DAT_GameState::instance.playerDataArray[1].keep.yEntry;

            int iVar3 = DAT_GameState::instance.playerDataArray[1].keep.xEntry;

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state_2 = 6;

            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(
                (int)DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                (int)((int)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y)), iVar3, iVar4);

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = DAT_DirectionAlgorithmState::instance.orientation;

            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field265_0x3bc = 0;
        }

        return;
    }

}
}
