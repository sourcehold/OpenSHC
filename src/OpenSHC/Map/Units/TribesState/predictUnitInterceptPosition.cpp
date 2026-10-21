#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521500
        void TribesState::predictUnitInterceptPosition(
            int targetUnitID, int unitID, int* unitCurrentX, int* unitCurrentY)
        {
            UnitTypeShort UVar1;
            uint _currentIndexInPathPlan;
            int local_8;
            short _targetTribeMinSpeed;
            int _unitID = unitID;
            int _unitAddressOffset = unitID * 0x490;
            *unitCurrentX = (int)DAT_UnitsState::instance.units[unitID].x;
            int _yOffb = (int)DAT_UnitsState::instance.units[unitID].y;
            *unitCurrentY = _yOffb;
            /*
              The import had this guard with an empty body; the original jumps straight to
              the epilogue, so everything below runs only for a unit that has finished
              digging.
             */
            if (DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging != 2) {
                return;
            }
            _targetTribeMinSpeed
                = this->tribes[DAT_UnitsState::instance.units[targetUnitID].tribeID].minimumMovementSpeed;
            int _targetTribeMinSpeedBounded = (int)_targetTribeMinSpeed;
            if (_targetTribeMinSpeed < 2) {
                _targetTribeMinSpeedBounded = 1;
            }
            int _tribeMinSpeed = this->tribes[DAT_UnitsState::instance.units[unitID].tribeID].minimumMovementSpeed;
            int iVar3 = _targetTribeMinSpeedBounded * 4;
            int _tribeMinSpeedBounded = (int)_tribeMinSpeed;
            if (_tribeMinSpeed < 2) {
                _tribeMinSpeedBounded = 1;
            }
            int iVar4 = (int)DAT_UnitsState::instance.units[targetUnitID].x;
            int iVar2 = (int)DAT_UnitsState::instance.units[targetUnitID].y;
            if (DAT_UnitsState::instance.units[targetUnitID].stateBasedSpeed <= 0) {
                UVar1 = DAT_UnitsState::instance.units[targetUnitID].unitType;
                if ((UVar1 == Map::Units::UT_E_KNIGHT)
                    && (DAT_UnitsState::instance.units[targetUnitID].isMatchingSpeed == false)) {
                    iVar3 = iVar3 / 3;
                } else if (UVar1 == Map::Units::UT_E_SWORD)
                    goto LAB_005215e9;
            } else {
            LAB_005215e9:
                iVar3 = iVar3 / 2;
            }
            if (DAT_UnitsState::instance.units[unitID].stateBasedSpeed <= 0) {
                UVar1 = DAT_UnitsState::instance.units[unitID].unitType;
                if ((UVar1 == Map::Units::UT_E_KNIGHT)
                    && (DAT_UnitsState::instance.units[unitID].isMatchingSpeed == false)) {
                    unitID = iVar3 / 3;
                    goto LAB_0052163b;
                }
                unitID = iVar3;
                if (UVar1 != Map::Units::UT_E_SWORD)
                    goto LAB_0052163b;
            }
            /*
              reused parameter!
             */
            unitID = iVar3 / 2;
        LAB_0052163b:
            int _unitCurrentX_2 = *unitCurrentX;
            uint _xOff_2 = _unitCurrentX_2 - iVar4;
            uint _yOff_2 = _yOffb - iVar2;
            int _xOff_2b = (_xOff_2 ^ (int)_xOff_2 >> 0x1f) - ((int)_xOff_2 >> 0x1f);
            int _yOff_2b = (_yOff_2 ^ (int)_yOff_2 >> 0x1f) - ((int)_yOff_2 >> 0x1f);
            if (_yOff_2b < _xOff_2b) {
                _yOff_2b = _xOff_2b;
            }
            /*
              Flat guards. Nesting the loop inside one `&&` chain puts the merged exit at
              the end of the function; the original reaches it directly from each test.
              This is the same shape that took trySpawnAdditionalWildlifeForTribe from
              87.2% to a full match, and it drops two comma operators from inside an `&&`.
             */
            if ((_yOff_2b + -2) * unitID < 0) {
                return;
            }
            _currentIndexInPathPlan = (int)DAT_UnitsState::instance.units[_unitID].currentIndexInPathPlan;
            local_8 = _tribeMinSpeedBounded * 4;
            if ((int)DAT_UnitsState::instance.units[_unitID].totalSizeOfPathPlan
                <= (int)_currentIndexInPathPlan) {
                return;
            }
            {
                do {
                    /*
                      get current value in pathPlan, each byte contains two move instructions
                     */
                    uint _pathPlanPair
                        = (uint) * (char*)((int)_currentIndexInPathPlan / 2 + 0x138864a + _unitAddressOffset);
                    if (!(_currentIndexInPathPlan & 1)) {
                        /*
                          if index is even, retain the lowest 4 bits
                         */
                        _pathPlanPair = _pathPlanPair & 0xf;
                    } else {
                        /*
                          if index is odd retain the highest 4 bits
                         */
                        _pathPlanPair = (int)_pathPlanPair >> 4;
                    }
                    *unitCurrentX = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_pathPlanPair]
                                        .int_.xOffset
                        + _unitCurrentX_2;
                    *unitCurrentY = *unitCurrentY
                        + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                            + _pathPlanPair * 8 + 4);
                    _unitCurrentX_2 = *unitCurrentX;
                    uint _xOff = _unitCurrentX_2 - iVar4;
                    uint _yOff = *unitCurrentY - iVar2;
                    iVar3 = (_xOff ^ (int)_xOff >> 0x1f) - ((int)_xOff >> 0x1f);
                    _yOffb = (_yOff ^ (int)_yOff >> 0x1f) - ((int)_yOff >> 0x1f);
                    if (_yOffb < iVar3) {
                        _yOffb = iVar3;
                    }
                    if ((_yOffb + -2) * unitID < local_8) {
                        return;
                    }
                    local_8 = local_8 + _tribeMinSpeedBounded * 4;
                    _currentIndexInPathPlan = _currentIndexInPathPlan + 1;
                } while (
                    (int)_currentIndexInPathPlan < (int)DAT_UnitsState::instance.units[_unitID].totalSizeOfPathPlan);
            }
        }

    }
}
}
