#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0054C610
        BOOLEnum UnitsState::moveToFreeTileNearby(int unitID)
        {
            if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] & 0x30U) != 0) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findDirectNeighbourWalkableTile,
                        DAT_PathFindingState::ptr)(this->units[unitID].x, this->units[unitID].y)
                    != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setPositionOfUnit, this)(unitID,
                        DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY,
                        DAT_TileMapState::instance.HeightLayer[DAT_PathFindingState::instance.ALG_ResultTile]);
                }
                return FALSE;
            }
            if ((short)DAT_TileMapState::instance.UnitLayer[this->units[unitID].tile] == unitID) {
                return FALSE;
            }
            if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].tile] & 0x100U) == 0) {
                /* not a wall tower or gatehouse */
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findPathableTileWithoutUnitWithBuildingAtXY,
                    DAT_PathFindingState::ptr)(-1, this->units[unitID].x, this->units[unitID].y);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findFreeTileOnDefensiveStructure,
                    DAT_PathFindingState::ptr)(-1, this->units[unitID].x, this->units[unitID].y);
            }
            if (DAT_PathFindingState::instance.ALG_ResultTile == 0) {
                return FALSE;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY, 0)
                == FALSE) {
                return FALSE;
            }
            this->units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
            return TRUE;
        }

    }
}
}
