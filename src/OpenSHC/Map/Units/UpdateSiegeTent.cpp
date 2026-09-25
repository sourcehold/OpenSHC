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
    void Units::UpdateSiegeTent()
    {
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
        int frame = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng + 1 & 3;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = frame;
        if (frame >= 4) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 2;
        }
        // the tent turns into a siege engine after 500 ticks
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber += 1;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber <= 500) {
            return;
        }
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
            = OpenSHC::Map::Units::ULS_TRANSITIONING;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng % 4 < 2) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                = OpenSHC::Map::Units::UT_S_CATAPULT;
        } else {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                = OpenSHC::Map::Units::UT_S_TREBUCHET;
        }
        // face the keep of player 1
        int keepY = DAT_GameState::instance.playerDataArray[1].keep.yEntry;
        int keepX = DAT_GameState::instance.playerDataArray[1].keep.xEntry;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state_2 = 6;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
            keepX, keepY);
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
            = DAT_DirectionAlgorithmState::instance.orientation;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field248_0x3bc = 0;
    }

}
}
