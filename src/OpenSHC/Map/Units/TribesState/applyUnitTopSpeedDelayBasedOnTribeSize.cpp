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
            int _unitInSelection;
            int _selectionUnit;
            UnitIDMovementDistancePair* _nextUnit;
            int _delayIndex;
            int iVar1;
            UnitIDMovementDistancePair* pUVar2;
            short* _ptrMovementDistance;
            int _unitSelectionIndex;
            short _distance;
            int _foundUnsortedEntry;
            short _nextUnitID;
            short* _tribeSize;
            short _unitID;
            _tribeSize = &this->tribes[tribeID].size;
            _unitSelectionIndex = 0;
            if (*_tribeSize < 40) {
                /*
                  For selections (tribes) of size 40 or less
                 */
                this->someUnitIDArrayCount = 0;
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    4004, '\0', (void*)((int)(this->someUnitIDMovementDistancePair)));
                if (0 < *_tribeSize) {
                    /*
                      Of all units in the selection store unitID and optionally their   movementDistance into an array
                     */
                    _ptrMovementDistance = &this->someUnitIDMovementDistancePair[0].movementDistance;
                    do {
                        _selectionUnit
                            = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                                tribeID, _unitSelectionIndex);
                        if ((DAT_UnitsState::instance.units[_selectionUnit].logicalState
                                == Map::Units::ULS_NORMAL)
                            && (DAT_UnitsState::instance.units[_selectionUnit].dying == 0)) {
                            this->someUnitIDArrayCount = this->someUnitIDArrayCount + 1;
                            /*
                              sets unitID
                             */
                            ((UnitIDMovementDistancePair*)(_ptrMovementDistance + -1))->unitID = (short)_selectionUnit;
                            if (!param_2) {
                                *_ptrMovementDistance = DAT_UnitsState::instance.units[_selectionUnit].movementDistance;
                            }
                        }
                        _unitSelectionIndex = _unitSelectionIndex + 1;
                        _ptrMovementDistance = _ptrMovementDistance + 2;
                    } while (_unitSelectionIndex < *_tribeSize);
                }
                do {
                    /*
                      Do a sort of the array, sort by distance value (low to high)
                     */
                    _foundUnsortedEntry = 0;
                    /*
                      fixme:reuse: WARNING reuse of parameter
                     */
                    tribeID = 0;
                    if (this->someUnitIDArrayCount == 1 || this->someUnitIDArrayCount + -1 < 0)
                        break;
                    pUVar2 = this->someUnitIDMovementDistancePair;
                    do {
                        _nextUnit = pUVar2 + 1;
                        _distance = pUVar2->unitID;
                        _unitID = pUVar2->movementDistance;
                        _nextUnitID = pUVar2[1].movementDistance;
                        if ((!param_2) && (_nextUnitID < _unitID)) {
                            _foundUnsortedEntry = 1;
                            pUVar2->unitID = _nextUnit->unitID;
                            _nextUnit->unitID = _distance;
                            pUVar2->movementDistance = _nextUnitID;
                            pUVar2[1].movementDistance = _unitID;
                        }
                        tribeID = tribeID + 1;
                        pUVar2 = _nextUnit;
                    } while (tribeID < this->someUnitIDArrayCount + -1);
                } while (_foundUnsortedEntry);
                _delayIndex = 0;
                if (0 < this->someUnitIDArrayCount) {
                    pUVar2 = this->someUnitIDMovementDistancePair;
                    do {
                        DAT_UnitsState::instance.units[pUVar2->unitID].topSpeedDelayIndex = (short)_delayIndex;
                        _delayIndex = _delayIndex + 1;
                        pUVar2 = pUVar2 + 1;
                    } while (_delayIndex < this->someUnitIDArrayCount);
                }
            } else if (0 < *_tribeSize) {
                do {
                    /*
                      Set incremental delay on first 199 units, then set same value of 199
                     */
                    _unitInSelection
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                            tribeID, _unitSelectionIndex);
                    iVar1 = _unitSelectionIndex;
                    if (199 < _unitSelectionIndex) {
                        iVar1 = 199;
                    }
                    DAT_UnitsState::instance.units[_unitInSelection].topSpeedDelayIndex = (short)iVar1;
                    _unitSelectionIndex = _unitSelectionIndex + 1;
                } while (_unitSelectionIndex < *_tribeSize);
            }
        }

    }
}
}
