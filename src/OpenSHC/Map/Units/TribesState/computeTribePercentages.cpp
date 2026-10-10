#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005270F0
        void TribesState::computeTribePercentages(int tribeID)
        {
            short sVar1;
            UnitStateShort UVar2;
            short _percentage;
            uint _unitID;
            BOOLEnum BVar3;
            int _tribeSize;
            int iVar4;
            int _countAttackingUnk;
            int _countDying;
            int _countMoving;
            int _countRangeUnk;
            int local_8;
            short _movementSpeed;
            UnitTypeShort _unitType;
            _percentage = this->tribes[tribeID].selectionTargetUnitID;
            iVar4 = 0;
            sVar1 = this->tribes[tribeID].size;
            this->tribes[tribeID].percentageDyingUnk = 0;
            this->tribes[tribeID].percentageMovingUnk = 0;
            this->tribes[tribeID].percentageAttackingUnk = 0;
            this->tribes[tribeID].field152_0x29c = 0;
            this->tribes[tribeID].percentageShootingUnk = 0;
            this->tribes[tribeID].field154_0x2a0 = 0;
            this->tribes[tribeID].percentageSomething = 0;
            this->tribes[tribeID].movementSpeed = DAT_UnitsState::instance.units[_percentage].movementSpeed;
            local_8 = 0;
            _countRangeUnk = 0;
            _countAttackingUnk = 0;
            _countMoving = 0;
            _countDying = 0;
            this->tribes[tribeID].unitType = DAT_UnitsState::instance.units[_percentage].unitType;
            if (0 < sVar1) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getSpecificUnitFromTribe, this)(
                        tribeID, iVar4);
                    iVar4 = iVar4 + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL) {
                        BVar3 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::isComputerManagedNonPeasant, DAT_UnitsState::ptr)(_unitID);
                        if (!BVar3) {
                            if (DAT_UnitsState::instance.units[_unitID].dying == 0) {
                                if (DAT_UnitsState::instance.units[_unitID].movementRelated != 8) {
                                    _countMoving = _countMoving + 1;
                                }
                                UVar2 = DAT_UnitsState::instance.units[_unitID].state.generic;
                                if (UVar2 == Map::Units::States::US_MELEE_ATTACK) {
                                    _countAttackingUnk = _countAttackingUnk + 1;
                                }
                                if (UVar2 == Map::Units::States::US_MELEE_ATTACK_WALL) {
                                    _countAttackingUnk = _countAttackingUnk + 1;
                                }
                                if (UVar2
                                    == (Map::Units::States::US_DEATH_02 | Map::Units::States::US_STAND_UPUnk
                                        | Map::Units::States::US_RELOAD_WEAPONUnk)) {
                                    local_8 = local_8 + 1;
                                }
                                if (DAT_UnitsState::instance.units[_unitID].field316_0x430 != 0
                                    && ((UVar2 == Map::Units::States::US_RELOAD_WEAPONUnk
                                            || (UVar2 == Map::Units::States::US_AIM_WEAPONUnk))
                                        || (UVar2 == Map::Units::States::US_FIRE_WEAPONUnk))) {
                                    _countRangeUnk = _countRangeUnk + 1;
                                }
                                _unitType = this->tribes[tribeID].unitType;
                                if (_unitType != (UnitType)0
                                    && DAT_UnitsState::instance.units[_unitID].unitType != _unitType) {
                                    this->tribes[tribeID].unitType = ((UnitType)0);
                                }
                                _movementSpeed = DAT_UnitsState::instance.units[_unitID].movementSpeed;
                                if (this->tribes[tribeID].movementSpeed < _movementSpeed) {
                                    this->tribes[tribeID].movementSpeed = _movementSpeed;
                                }
                            } else {
                                _countDying = _countDying + 1;
                            }
                        } else {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, this)(
                                _unitID, tribeID);
                        }
                    }
                } while (iVar4 < this->tribes[tribeID].size);
            }
            _tribeSize = (int)this->tribes[tribeID].size;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (short)((_countDying * 100) / _tribeSize);
            }
            this->tribes[tribeID].percentageDyingUnk = _percentage;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (short)((_countMoving * 100) / _tribeSize);
            }
            this->tribes[tribeID].percentageMovingUnk = _percentage;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (short)((_countAttackingUnk * 100) / _tribeSize);
            }
            this->tribes[tribeID].percentageAttackingUnk = _percentage;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (short)((_countRangeUnk * 100) / _tribeSize);
            }
            this->tribes[tribeID].percentageShootingUnk = _percentage;
            if (_tribeSize) {
                this->tribes[tribeID].percentageSomething = (short)((local_8 * 100) / _tribeSize);
            }
            this->tribes[tribeID].percentageSomething = 100;
        }

    }
}
}
