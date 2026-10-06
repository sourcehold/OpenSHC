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
            int _playerID = this->units[unitID].owner;
            if (DAT_GameState::instance.playerDataArray[_playerID].totalEnemyUnitsCount > 0) {
                return TRUE;
            }
            if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                return (
                    BOOLEnum)(DAT_BuildingsState::instance.buildings[this->units[unitID].targetID_OR_targetBuildingID]
                                  .uid
                    == this->units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID);
            }
            int _shootTargetMicroX = this->units[unitID].shootTargetMicroX;
            int _shootTargetMicroY = DAT_UnitsState::instance.units[unitID].shootTargetMicroY;
            return (BOOLEnum)(MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                    checkEnemyBuildingOrDefensiveStructureWithin12Tiles,
                                  DAT_PathFindingState::ptr)(_playerID, _shootTargetMicroX / 8, _shootTargetMicroY / 8)
                != FALSE);
        }

    }
}
}
