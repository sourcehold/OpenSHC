#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          called when pathfinding with walls   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4930
        int PathFindingState::setClimbBasedOnClosestClimbData(int unitID, int ladderWallGroup, int ladderArea)
        {
            int iVar1;
            int fromXPosition;
            ClimbData* _pClimbData;
            ClimbData* _pClimbData2;
            short _downOrUp1;
            int _climbDataID;
            int _climbData2;
            int _minDistance;
            short _downOrUp;
            int _distance;
            _minDistance = 1000;
            _climbData2 = 0;
            _downOrUp = 0;
            if (this->field63_0xc0 == 0) {
                return 200;
            }
            int _climbDataCounter = 1;
            if (1 < this->maxClimbDataCount) {
                _pClimbData = &this->climbData[1];
                _downOrUp = 0;
                do {
                    if ((_pClimbData->canBeUsed == 1) && (_pClimbData->isRecognizedByPathfinding != 0)) {
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::checkUnitHasPropertyBasedOnUnitType,
                            DAT_UnitsState::ptr)(unitID, _pClimbData->type);
                        if ((iVar1 != 0) && (_pClimbData->type == 1)) {
                            if (_pClimbData->area == ladderWallGroup) {
                                _downOrUp1 = 0;
                                if (_pClimbData->wallGroupAreaID == ladderArea) {
                                    iVar1 = _pClimbData->bottomYPosition;
                                    fromXPosition = _pClimbData->bottomXPosition;
                                LAB_004a49e1:
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                          setAxisBasedDistanceResult,
                                        DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                                        (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, iVar1);
                                    _distance = DAT_DirectionAlgorithmState::instance.distanceHigh
                                        + _pClimbData->numberOfUnitsUsing * 8;
                                    if (_distance < _minDistance) {
                                        _climbData2 = _climbDataCounter;
                                        _minDistance = _distance;
                                        _downOrUp = _downOrUp1;
                                        if (_downOrUp1 == 0) {
                                            this->climbX = _pClimbData->bottomXPosition;
                                            this->climbY = _pClimbData->bottomYPosition;
                                        } else {
                                            this->climbX = _pClimbData->topXPosition;
                                            this->climbY = _pClimbData->topYPosition;
                                        }
                                    }
                                }
                            } else if ((_pClimbData->area == ladderArea)
                                && (_downOrUp1 = 1, _pClimbData->wallGroupAreaID == ladderWallGroup)) {
                                iVar1 = _pClimbData->topYPosition;
                                fromXPosition = _pClimbData->topXPosition;
                                goto LAB_004a49e1;
                            }
                        }
                    }
                    _climbDataCounter = _climbDataCounter + 1;
                    _pClimbData = _pClimbData + 1;
                } while (_climbDataCounter < this->maxClimbDataCount);
            }
            DAT_UnitsState::instance.units[unitID].climbDirection = _downOrUp;
            if (_climbData2 == 0) {
                _pClimbData2 = &this->climbData[1];
                _climbDataID = 1;
                do {
                    if ((_pClimbData2->canBeUsed == 1) && (_pClimbData2->isRecognizedByPathfinding != 0)) {
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::checkUnitHasPropertyBasedOnUnitType,
                            DAT_UnitsState::ptr)(unitID, _pClimbData2->type);
                        if ((iVar1 != 0) && (0 < _pClimbData2->buildingArea)) {
                            if (_pClimbData2->area == ladderArea) {
                                this->climbX = this->climbData[_climbDataID].bottomXPosition;
                                this->climbY = this->climbData[_climbDataID].bottomYPosition;
                                return _climbDataID;
                            }
                            if (_pClimbData2->wallGroupAreaID == ladderArea) {
                                this->climbX = this->climbData[_climbDataID].topXPosition;
                                this->climbY = this->climbData[_climbDataID].topYPosition;
                                return _climbDataID;
                            }
                        }
                    }
                    _climbDataID = _climbDataID + 1;
                    _pClimbData2 = _pClimbData2 + 1;
                } while (_climbDataID < 200);
            }
            return _climbData2;
        }

    }
}
}
