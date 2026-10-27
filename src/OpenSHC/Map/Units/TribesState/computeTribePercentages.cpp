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

        /*
          Its three `short` locals stay narrow: widening all three costs 0.9 points
          (42.8% -> 41.9%).
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x005270F0
        void TribesState::computeTribePercentages(int tribeID)
        {
            uint _unitID;
            BOOLEnum BVar3;
            /*
              The unit index is its own `int`: the original reaches it with a single
              `movsx eax, word ptr [esi + 0x5a]`, where sharing the `short` that later holds
              the percentages costs a `movzx` plus a `movsx`.
             */
            /*
              The tribe stays a subscript at each access. The original computes its address
              once in the prologue (`lea esi, [eax + ecx]`) and then reloads `this` from a
              stack slot for the call in the loop (`mov ecx, [esp + 0x24]`), where we hold
              `this` in a register and spill the loop counter instead - so a
              `TribesState*` base of our own looks like the way to free it. It is not:
              measured 47.2% -> 45.2%. MSVC commons the base out of the subscripts anyway
              and the explicit pointer only changes which register it picks.
             */
            int const _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
            /*
              An `int`, not a `short`. The original keeps each percentage in a 32-bit
              register and stores `ax` straight into the field - `idiv ecx` then
              `mov word ptr [esi + 0x2be], ax`. A `short` local makes MSVC truncate the
              division result and widen it back before every store, adding a
              `movzx eax, ax` at all four sites; the original has none.
             */
            int _percentage = 0;
            int iVar4 = 0;
            this->tribes[tribeID].percentageDyingUnk = 0;
            this->tribes[tribeID].percentageMovingUnk = 0;
            this->tribes[tribeID].percentageAttackingUnk = 0;
            this->tribes[tribeID].field150_0x29c = 0;
            this->tribes[tribeID].percentageShootingUnk = 0;
            this->tribes[tribeID].field152_0x2a0 = 0;
            this->tribes[tribeID].percentageSomething = 0;
            this->tribes[tribeID].movementSpeed = DAT_UnitsState::instance.units[_targetUnitID].movementSpeed;
            int local_8 = 0;
            int _countRangeUnk = 0;
            int _countAttackingUnk = 0;
            int _countMoving = 0;
            int _countDying = 0;
            this->tribes[tribeID].unitType = DAT_UnitsState::instance.units[_targetUnitID].unitType;
            /*
              The size is read in the test, not into a local. The original never loads it
              into a register: it compares the field in place against the zero it already
              has in bp for the seven word stores above - `cmp word ptr [esi + 0x5c], bp`.
              A local forces a load of its own.
             */
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getSpecificUnitFromTribe, this)(
                        tribeID, iVar4);
                    iVar4 = iVar4 + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL) {
                        BVar3 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::isComputerManagedNonPeasant, DAT_UnitsState::ptr)(_unitID);
                        if (!BVar3) {
                            /*
                              The dying tally is the fall-through. The original jumps 0xa
                              forward when the flag is clear (`je 0xa`) - exactly the
                              `add dword ptr [esp + 0x14], 1` and `jmp` that follow - so
                              the one-line increment sits under the test and the thirty
                              lines of tallying go in the far block.
                             */
                            if (DAT_UnitsState::instance.units[_unitID].dying != 0) {
                                _countDying = _countDying + 1;
                            } else {
                                if (DAT_UnitsState::instance.units[_unitID].movementRelated != 8) {
                                    _countMoving = _countMoving + 1;
                                }
                                UnitStateShort UVar2 = DAT_UnitsState::instance.units[_unitID].state.generic;
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
                                UnitTypeShort _unitType = this->tribes[tribeID].unitType;
                                if (_unitType != (UnitType)0
                                    && DAT_UnitsState::instance.units[_unitID].unitType != _unitType) {
                                    this->tribes[tribeID].unitType = ((UnitType)0);
                                }
                                short _movementSpeed = DAT_UnitsState::instance.units[_unitID].movementSpeed;
                                if (_movementSpeed > this->tribes[tribeID].movementSpeed) {
                                    this->tribes[tribeID].movementSpeed = _movementSpeed;
                                }
                            }
                        } else {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, this)(
                                _unitID, tribeID);
                        }
                    }
                } while (iVar4 < this->tribes[tribeID].size);
            }
            int _tribeSize = (int)this->tribes[tribeID].size;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (_countDying * 100) / _tribeSize;
            }
            this->tribes[tribeID].percentageDyingUnk = (short)_percentage;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (_countMoving * 100) / _tribeSize;
            }
            this->tribes[tribeID].percentageMovingUnk = (short)_percentage;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (_countAttackingUnk * 100) / _tribeSize;
            }
            this->tribes[tribeID].percentageAttackingUnk = (short)_percentage;
            if (!_tribeSize) {
                _percentage = 100;
            } else {
                _percentage = (_countRangeUnk * 100) / _tribeSize;
            }
            this->tribes[tribeID].percentageShootingUnk = (short)_percentage;
            /*
              The last percentage is the same shape as the four above it, not a guarded
              store followed by an unconditional 100 - which is what the import had, and
              it pinned the field at 100 whatever the tally was. The original tests the
              size once and duplicates the epilogue, storing to 0x2ca and returning in
              each arm (0x5272fc and 0x527315, each with its own `ret 4`), so it is
              written as an early return rather than through the shared `_percentage`.
             */
            if (!_tribeSize) {
                this->tribes[tribeID].percentageSomething = 100;
                return;
            }
            this->tribes[tribeID].percentageSomething = (short)((local_8 * 100) / _tribeSize);
        }

    }
}
}
