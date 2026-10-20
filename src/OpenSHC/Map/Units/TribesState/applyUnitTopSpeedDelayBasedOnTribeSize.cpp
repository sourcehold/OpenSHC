#include "../../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524EF0
        void TribesState::applyUnitTopSpeedDelayBasedOnTribeSize(int tribeID, BOOLEnum param_2)
        {
            short* _tribeSize = &this->tribes[tribeID].size;
            int _unitSelectionIndex = 0;
            /*
              The original places the big-tribe branch first: it tests the size and jumps
              away when it is below 40.
             */
            if (40 <= *_tribeSize) {
                if (0 < *_tribeSize) {
                    do {
                        /*
                          Set incremental delay on the first 199 units, then the same value
                          of 199 for the rest
                         */
                        int const _unitInSelection
                            = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                tribeID, _unitSelectionIndex);
                        int iVar1 = _unitSelectionIndex;
                        if (199 <= _unitSelectionIndex) {
                            iVar1 = 199;
                        }
                        DAT_UnitsState::instance.units[_unitInSelection].topSpeedDelayIndex = (short)iVar1;
                        _unitSelectionIndex = _unitSelectionIndex + 1;
                    } while (_unitSelectionIndex < *_tribeSize);
                }
                return;
            }
            /*
              For selections (tribes) of size 39 or less
             */
            this->someUnitIDArrayCount = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->someUnitIDMovementDistancePair), '\0', this->someUnitIDMovementDistancePair);
            if (0 < *_tribeSize) {
                /*
                  Of all units in the selection store unitID and optionally their
                  movementDistance into an array
                 */
                /*
                  The cursor walks the movementDistance member, not the pair: that is the
                  anchor the original picks (`lea ebx, [esi + 0xfa412]`, with the unit ID
                  stored at [ebx - 2]).
                 */
                short* _movementDistance = &this->someUnitIDMovementDistancePair[0].movementDistance;
                do {
                    int const _selectionUnit
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitSelectionIndex);
                    if ((DAT_UnitsState::instance.units[_selectionUnit].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_selectionUnit].dying == 0)) {
                        this->someUnitIDArrayCount = this->someUnitIDArrayCount + 1;
                        _movementDistance[-1] = (short)_selectionUnit;
                        if (!param_2) {
                            *_movementDistance = DAT_UnitsState::instance.units[_selectionUnit].movementDistance;
                        }
                    }
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                    _movementDistance = _movementDistance + 2;
                } while (_unitSelectionIndex < *_tribeSize);
            }
            int _foundUnsortedEntry;
            do {
                /*
                  Bubble sort of the array by movementDistance, low to high
                 */
                _foundUnsortedEntry = 0;
                int _pairIndex = 0;
                /*
                  One test, not two: the original subtracts one from the count and jumps on
                  the sign-or-zero (`sub edx, 1; test edx, edx; jle`), which the decompiler
                  split into an equality and a sign test.
                 */
                if (this->someUnitIDArrayCount - 1 <= 0) {
                    break;
                }
                /*
                  The cursor walks the *second* element of each pair, which is the anchor
                  the original picks (diff_anchor.py: `lea eax, [esi + 0xfa414]`, with the
                  current entry reached as [eax - 4] and [eax - 2]).
                 */
                UnitIDMovementDistancePair* _nextUnit = this->someUnitIDMovementDistancePair + 1;
                do {
                    UnitIDMovementDistancePair* pUVar2 = _nextUnit - 1;
                    short const _unitID = pUVar2->unitID;
                    short const _distance = pUVar2->movementDistance;
                    short const _nextDistance = _nextUnit->movementDistance;
                    if ((!param_2) && (_nextDistance < _distance)) {
                        _foundUnsortedEntry = 1;
                        pUVar2->unitID = _nextUnit->unitID;
                        _nextUnit->unitID = _unitID;
                        pUVar2->movementDistance = _nextDistance;
                        _nextUnit->movementDistance = _distance;
                    }
                    _pairIndex = _pairIndex + 1;
                    _nextUnit = _nextUnit + 1;
                } while (_pairIndex < this->someUnitIDArrayCount + -1);
            } while (_foundUnsortedEntry);
            int _delayIndex = 0;
            if (0 < this->someUnitIDArrayCount) {
                UnitIDMovementDistancePair* pUVar2 = this->someUnitIDMovementDistancePair;
                do {
                    DAT_UnitsState::instance.units[pUVar2->unitID].topSpeedDelayIndex = (short)_delayIndex;
                    _delayIndex = _delayIndex + 1;
                    pUVar2 = pUVar2 + 1;
                } while (_delayIndex < this->someUnitIDArrayCount);
            }
        }

    }
}
}
