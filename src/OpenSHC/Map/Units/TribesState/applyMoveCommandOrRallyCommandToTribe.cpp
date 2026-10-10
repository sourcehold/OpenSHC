#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524340
        undefined4 TribesState::applyMoveCommandOrRallyCommandToTribe(
            int tribeID, undefined4 x1, undefined4 y1, undefined4 isRallying, int storeAsRallyPoint)
        {
            int _unitID;
            int _unitSelectionIndex = 0;
            BOOLEnum _allAssassins
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeAllAssassins, this)(tribeID);
            this->tribes[tribeID].someUnitID = 0;
            if (storeAsRallyPoint) {
                int _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                this->tribes[tribeID].isRallyingUnk = (short)isRallying;
                this->tribes[tribeID].rallyPointArray[0][0] = DAT_UnitsState::instance.units[_targetUnitID].x;
                this->tribes[tribeID].rallyPointArray[0][1] = DAT_UnitsState::instance.units[_targetUnitID].y;
                this->tribes[tribeID].rallyPointArray[1][0] = (short)x1;
                this->tribes[tribeID].rallyPointArray[1][1] = (short)y1;
                this->tribes[tribeID].currentRallyPointIndex = 1;
                this->tribes[tribeID].rallyPointCount = 2;
            }
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _unitSelectionIndex);
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[_unitID].dying == 0
                        && DAT_UnitsState::instance.units[_unitID].usingTeleport == 0
                        && DAT_UnitsState::instance.units[_unitID].field303_0x413 == 0
                        && DAT_UnitsState::instance.units[_unitID].state.generic != Map::Units::States::US_MELEE_ATTACK
                        && DAT_UnitsState::instance.units[_unitID].moveableUnk != 0
                        && DAT_UnitsState::instance.units[_unitID].moveRelatedFlag != 1) {
                        DAT_UnitsState::instance.units[_unitID].plannedDestinationX = (short)x1;
                        DAT_UnitsState::instance.units[_unitID].state.generic
                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                        DAT_UnitsState::instance.units[_unitID].targetingType
                            = Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                        DAT_UnitsState::instance.units[_unitID]._someX_2 = 0;
                        DAT_UnitsState::instance.units[_unitID]._someY_2 = 0;
                        DAT_UnitsState::instance.units[_unitID].plannedDestinationY = (short)y1;
                        DAT_UnitsState::instance.units[_unitID].moveDelay = 0;
                        DAT_UnitsState::instance.units[_unitID].moveInstructionSpeedDelayTracker = 0;
                        if (_allAssassins) {
                            DAT_PathFindingState::instance.allAssassinsUnk = 1;
                        }
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                            _unitID, (uint)((short)x1), (uint)((short)y1), 0);
                    }
                } while (_unitSelectionIndex < this->tribes[tribeID].size);
            }
            return (undefined4)(1);
        }

    }
}
}
