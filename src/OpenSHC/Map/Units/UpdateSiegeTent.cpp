#include "../Units.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005307B0
    void Units::UpdateSiegeTent()
    {
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
        int const frame = (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng + 1) & 3;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = frame;
        // fixme: never true after the & 3, but the original compares and stores it
        if (frame >= 4) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber = 2;
        }
        // the tent turns into a siege engine after 500 ticks
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber++;
        if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber <= 500) {
            return;
        }
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
            = OpenSHC::Map::Units::ULS_TRANSITIONING;
        // state_2 is stored in both arms: one store after the if turns the type store into a select
        if ((DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fixedRng & 2) != 0) {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                = OpenSHC::Map::Units::UT_S_TREBUCHET;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state_2
                = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
        } else {
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeToChangeInto
                = OpenSHC::Map::Units::UT_S_CATAPULT;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state_2
                = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
        }
        // face the keep of player 1 (y is read before x)
        int const keepY = DAT_GameState::instance.playerDataArray[1]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .yEntry;
        int const keepX = DAT_GameState::instance.playerDataArray[1]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .xEntry;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, keepX, keepY);
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
            = DAT_DirectionAlgorithmState::instance.orientation;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x3bc = 0;
    }

}
}
