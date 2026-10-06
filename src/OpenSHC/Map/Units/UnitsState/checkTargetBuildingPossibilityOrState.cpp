#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533580
        BOOLEnum UnitsState::checkTargetBuildingPossibilityOrState(int unitID)
        {
            int _playerID = DAT_UnitsState::instance.units[unitID].owner;
            if (DAT_GameState::instance.playerDataArray[_playerID].totalEnemyUnitsCount > 0) {
                return TRUE;
            }
            if (DAT_UnitsState::instance.units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                return (BOOLEnum)(DAT_BuildingsState::instance
                                      .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                                      .uid
                    == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID);
            }
            int _shootTargetX = DAT_UnitsState::instance.units[unitID].shootTargetMicroX / 8;
            int _shootTargetY = DAT_UnitsState::instance.units[unitID].shootTargetMicroY / 8;
            return (BOOLEnum)(MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                    checkEnemyBuildingOrDefensiveStructureWithin12Tiles,
                                  DAT_PathFindingState::ptr)(_playerID, _shootTargetX, _shootTargetY)
                != FALSE);
        }

    }
}
}
