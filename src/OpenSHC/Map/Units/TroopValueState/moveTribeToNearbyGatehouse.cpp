#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D450
        BOOLEnum TroopValueState::moveTribeToNearbyGatehouse(int param_1)
        {
            int const unitID = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            int gatehouseID = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::getGatehouseNearSomethingUnk,
                DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 80);
            if (!gatehouseID) {
                gatehouseID = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::getGatehouseNearSomethingUnk,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[param_1].owner,
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 200);
                if (!gatehouseID) {
                    return FALSE;
                }
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                param_1, Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(param_1,
                DAT_BuildingsState::instance.buildings[gatehouseID].someX,
                DAT_BuildingsState::instance.buildings[gatehouseID].someY, 0, 0, Map::Units::Instructions::UMSE_0);
            return TRUE;
        }

    }
}
}
