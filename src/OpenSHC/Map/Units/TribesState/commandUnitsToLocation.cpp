#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00526F00
        undefined4 TribesState::commandUnitsToLocation(
            int tribeID, uint destinationX, uint destinationY, undefined4 matchUnitSpeeds)
        {
            int _unitID;
            UnitTypeShort _unitType;
            int _selectionUnitID = 0;
            bool bVar1 = true;
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _selectionUnitID);
                    _selectionUnitID = _selectionUnitID + 1;
                    if ((DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                        short _goToRallyPoint = DAT_UnitsState::instance.units[_unitID].goToRallyPoint;
                        DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 0;
                        if (!_goToRallyPoint && DAT_UnitsState::instance.units[_unitID].isSelectable_OR_matchTime != 0
                            && (MACRO_CALL_MEMBER(
                                    Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(destinationX, (int)(destinationY),
                                    (int)(DAT_UnitsState::instance.units[_unitID].x),
                                    (int)(DAT_UnitsState::instance.units[_unitID].y)),
                                4 < DAT_DirectionAlgorithmState::instance.distanceHigh)
                            && (DAT_UnitsState::instance.units[_unitID].movementType_OR_targetUnitID == 0
                                || (DAT_UnitsState::instance
                                        .units[DAT_UnitsState::instance.units[_unitID]
                                                .targetedUnitID__OR__engineerMannedSiegeEngineRef]
                                        .logicalState
                                    != Map::Units::ULS_NORMAL))
                            && (((_goToRallyPoint = DAT_UnitsState::instance.units[_unitID].shootTargetedUnit,
                                     _goToRallyPoint == 0
                                         || (this->tribes[DAT_CurrentTribeID::instance].countdown2 <= 0))
                                    || (DAT_UnitsState::instance.units[_unitID].unitType == Map::Units::UT_A_HARCHER))
                                || (DAT_UnitsState::instance.units[_unitID].targetUID
                                    != DAT_UnitsState::instance.units[_goToRallyPoint].uid))
                            && DAT_UnitsState::instance.units[_unitID].state.generic
                                != Map::Units::States::US_MELEE_ATTACK
                            && ((char)matchUnitSpeeds != '\0'
                                || (((_unitType = DAT_UnitsState::instance.units[_unitID].unitType,
                                         _unitType != Map::Units::UT_S_FBALLISTA
                                             && (_unitType != Map::Units::UT_S_CATAPULT))
                                    && ((_unitType != Map::Units::UT_S_SHIELD
                                        && ((_unitType != Map::Units::UT_S_TOWER
                                            && (_unitType != Map::Units::UT_S_BATTERINGRAM))))))))
                            && (DAT_UnitsState::instance.units[_unitID].engineerRelatedUnk == 0
                                || ((DAT_UnitsState::instance.units[_unitID].resourceToDeposit != 0
                                    && (DAT_UnitsState::instance.units[_unitID].field252_0x3c4 == 0))))) {
                            DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 0;
                            bVar1 = false;
                        } else {
                            DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 1;
                        }
                    }
                } while (_selectionUnitID < this->tribes[tribeID].size);
                if (!bVar1) {
                    if ((char)matchUnitSpeeds != '\0') {
                        this->tribes[tribeID].freeUnitSpeeds = 0;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(
                        tribeID, destinationX, destinationY, 0, 0, Map::Units::Instructions::UMSE_0);
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
