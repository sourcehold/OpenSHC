#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0054BFC0
        BOOLEnum UnitsState::updateClimbing(int unitID)
        {
            int _climbDataID = this->units[unitID].climbDataID;
            if (_climbDataID == 0) {
                return TRUE;
            }
            if (_climbDataID == 200) {
                return FALSE;
            }
            if (DAT_PathFindingState::instance.climbData[_climbDataID].climbDataRelated
                != this->units[unitID].climbDataRelated) {
                this->units[unitID].climbDataID = 0;
                return FALSE;
            }
            this->units[unitID].climbingState = -1;
            if (DAT_PathFindingState::instance.climbData[_climbDataID].type == 1) {
                int _ladderUnitID
                    = DAT_TileMapState::instance
                          .UnitLayer[DAT_PathFindingState::instance.climbData[_climbDataID].bottomTilePosition];
                for (; _ladderUnitID != 0; _ladderUnitID = this->units[_ladderUnitID].nextUnitOnTheSameTile) {
                    if (DAT_PathFindingState::instance.climbData[_climbDataID].unitID == _ladderUnitID) {
                        break;
                    }
                }
                if (_ladderUnitID == 0) {
                    return FALSE;
                }
                short _climbDirection = this->units[unitID].climbDirection;
                this->units[unitID].facingDirection = this->units[_ladderUnitID].facingDirection;
                this->units[unitID].usingTeleport = DAT_PathFindingState::instance.climbData[_climbDataID].type;
                this->units[unitID].field_0x35c = 0;
                this->units[unitID].climbingState = 0;
                if (_climbDirection == 0) {
                    this->units[unitID].climbingDirection = 0;
                } else {
                    this->units[unitID].climbingDirection = 1;
                }
                if (this->units[unitID].climbingDirection == 1) {
                    this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight - 40;
                }
                this->units[unitID].unknownStateCopyClimbRelated = this->units[unitID].state.generic;
                this->units[unitID].state.generic = (UnitState)104;
                this->units[unitID].animationCycleNumber = 0;
            } else if (DAT_PathFindingState::instance.climbData[_climbDataID].type == 7) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::exitLadder, this)(unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                    unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
            } else if (DAT_PathFindingState::instance.climbData[_climbDataID].type == 6) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::exitLadder, this)(unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                    unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
            } else if (DAT_PathFindingState::instance.climbData[_climbDataID].type == 5
                || DAT_PathFindingState::instance.climbData[_climbDataID].type == 4
                || DAT_PathFindingState::instance.climbData[_climbDataID].type == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::exitLadder, this)(unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                    unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
            }
            if (this->units[unitID].climbDirection == 0) {
                /* Climb up */
                this->units[unitID].mimicCurrentXPosition
                    = DAT_PathFindingState::instance.climbData[_climbDataID].topXPosition;
                this->units[unitID].mimicCurrentYPosition
                    = DAT_PathFindingState::instance.climbData[_climbDataID].topYPosition;
                return TRUE;
            }
            /* Climb down */
            this->units[unitID].mimicCurrentXPosition
                = DAT_PathFindingState::instance.climbData[_climbDataID].bottomXPosition;
            this->units[unitID].mimicCurrentYPosition
                = DAT_PathFindingState::instance.climbData[_climbDataID].bottomYPosition;
            return TRUE;
        }

    }
}
}
