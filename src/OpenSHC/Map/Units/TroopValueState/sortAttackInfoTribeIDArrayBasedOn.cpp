#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/AI/Tribes/AITribeTypeInt.hpp"
#include "OpenSHC/Globals/DAT_AttackInfoDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518380
        void TroopValueState::sortAttackInfoTribeIDArrayBasedOn(
            int attackWave, int shrinkSize, int tribeSizeSumLimit, SomeTribeBehaviorType someTribeTypeIdentifier)
        {
            int iVar1;
            Tribe* psVar1;
            int* piVar2;
            const AI::Tribes::AITribeTypeInt* _tribeTypePriority;
            int iVar3;
            int _currentTribeType;
            int _nextValue;
            int _lookupValue3;
            int _tribeID;
            int _currentValue;
            int _tribeType;
            int _tribeSizeSum;
            int _index;
            int _nextTribeType;
            int _counter2;
            int _index2;
            int _current;
            int _next;
            int _swapped;
            if (someTribeTypeIdentifier == 1010) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field251_0x21c;
            } else if (someTribeTypeIdentifier == 1011) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x44c;
            } else if (someTribeTypeIdentifier == 1012) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field255_0x35c;
            } else if (someTribeTypeIdentifier == 1018) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x4ec;
            } else if (someTribeTypeIdentifier == 1040) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field256_0x3ac;
            } else if (someTribeTypeIdentifier == 1045) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field257_0x3fc;
            } else if (someTribeTypeIdentifier == 7) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x12c;
            } else if (someTribeTypeIdentifier == 5) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x17c;
            } else if (someTribeTypeIdentifier == 1014) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field252_0x26c;
            } else if (someTribeTypeIdentifier == 1047) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x99c;
            } else if (someTribeTypeIdentifier == 1043) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field253_0x2bc;
            } else if (someTribeTypeIdentifier == 1044) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field254_0x30c;
            } else if (someTribeTypeIdentifier == 1013) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x53c;
            } else if (someTribeTypeIdentifier == 1019) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x58c;
            } else if (someTribeTypeIdentifier == 1025) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x5dc;
            } else if (someTribeTypeIdentifier == 1021) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x62c;
            } else if (someTribeTypeIdentifier == 1046) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x67c;
            } else if (someTribeTypeIdentifier == 1020) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field1059_0x7bc;
            } else if (someTribeTypeIdentifier == 1049) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field1060_0x80c;
            } else if (someTribeTypeIdentifier == 1050) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x71c;
            } else if (someTribeTypeIdentifier == 1051) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x71c;
            } else if (someTribeTypeIdentifier == 1048) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x85c;
            } else if (someTribeTypeIdentifier == 1054) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x8fc;
            } else if (someTribeTypeIdentifier == 1042) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x8ac;
            } else if (someTribeTypeIdentifier == 1016) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x6cc;
            } else if (someTribeTypeIdentifier == 1017) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field1058_0x76c;
            } else if (someTribeTypeIdentifier == 1015) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x49c;
            } else if (someTribeTypeIdentifier == 1041) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x94c;
            } else if (someTribeTypeIdentifier == 1023) {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x1cc;
            } else {
                _tribeTypePriority = DAT_AttackInfoDefinedData::instance.field_0x17c;
            }
            piVar2 = this->attackInfo.tribeRelatedArrayValue0UpTo12;
            do {
                piVar2[-100] = 0;
                *piVar2 = 0xc;
                piVar2 = piVar2 + 1;
            } while ((int)piVar2 < 0x17a9b98);
            _index = 0;
            _tribeID = 1;
            this->attackInfo.tribeIDArraySize = 0;
            psVar1 = &DAT_TribesState::instance.tribes[1];
            do {
                if (((((psVar1->tribeState) && (psVar1->tribeState != 3))
                         && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[psVar1->owner] == -1))
                        && ((psVar1->attackWave == attackWave
                            && (psVar1->attackInfo_someCounter1 != this->attackInfo.someCounter1))))
                    && ((psVar1->tribeBehaviorType != 1040 && (psVar1->tribeBehaviorType != 1045)))) {
                    this->attackInfo.tribeIDArray[_index] = _tribeID;
                    _index = this->attackInfo.tribeIDArraySize + 1;
                    this->attackInfo.tribeIDArraySize = _index;
                }
                psVar1 = psVar1 + 0x19a;
                _tribeID = _tribeID + 1;
            } while ((int)psVar1 < 0x17623a0);
            if ((0 < shrinkSize) && (0 < tribeSizeSumLimit)) {
                do {
                    /*
                      This is a sorting algorithm
                     */
                    _index2 = 0;
                    _swapped = 0;
                    if (_index + -1 < 1)
                        break;
                    do {
                        _current = this->attackInfo.tribeIDArray[_index2];
                        _next = this->attackInfo.tribeIDArray[_index2 + 1];
                        _currentTribeType = (int)(short)DAT_TribesState::instance.tribes[_current].tribeType;
                        _nextTribeType = (int)(short)DAT_TribesState::instance.tribes[_next].tribeType;
                        _currentValue = 0;
                        piVar2 = (int*)(_tribeTypePriority + 2);
                        do {
                            if (piVar2[-2] == _currentTribeType)
                                break;
                            if (piVar2[-1] == _currentTribeType) {
                                _currentValue = _currentValue + 1;
                                break;
                            }
                            if (*piVar2 == _currentTribeType) {
                                _currentValue = _currentValue + 2;
                                break;
                            }
                            if (piVar2[1] == _currentTribeType) {
                                _currentValue = _currentValue + 3;
                                break;
                            }
                            if (piVar2[2] == _currentTribeType) {
                                _currentValue = _currentValue + 4;
                                break;
                            }
                            if (piVar2[3] == _currentTribeType) {
                                _currentValue = _currentValue + 5;
                                break;
                            }
                            _currentValue = _currentValue + 6;
                            piVar2 = piVar2 + 6;
                        } while (_currentValue < 12);
                        _nextValue = 0;
                        piVar2 = (int*)(_tribeTypePriority + 2);
                        do {
                            if (piVar2[-2] == _nextTribeType)
                                break;
                            if (piVar2[-1] == _nextTribeType) {
                                _nextValue = _nextValue + 1;
                                break;
                            }
                            if (*piVar2 == _nextTribeType) {
                                _nextValue = _nextValue + 2;
                                break;
                            }
                            if (piVar2[1] == _nextTribeType) {
                                _nextValue = _nextValue + 3;
                                break;
                            }
                            if (piVar2[2] == _nextTribeType) {
                                _nextValue = _nextValue + 4;
                                break;
                            }
                            if (piVar2[3] == _nextTribeType) {
                                _nextValue = _nextValue + 5;
                                break;
                            }
                            _nextValue = _nextValue + 6;
                            piVar2 = piVar2 + 6;
                        } while (_nextValue < 0xc);
                        if (_nextValue < _currentValue) {
                            _swapped = 1;
                            this->attackInfo.tribeIDArray[_index2] = _next;
                            this->attackInfo.tribeIDArray[_index2 + 1] = _current;
                        }
                        _index2 = _index2 + 1;
                    } while (_index2 < this->attackInfo.tribeIDArraySize + -1);
                    _index = this->attackInfo.tribeIDArraySize;
                } while (_swapped);
                _counter2 = 0;
                if (0 < _index) {
                    do {
                        _tribeType
                            = (int)(short)DAT_TribesState::instance.tribes[this->attackInfo.tribeIDArray[_counter2]]
                                  .tribeType;
                        _lookupValue3 = 0;
                        piVar2 = (int*)(_tribeTypePriority + 2);
                        do {
                            if (piVar2[-2] == _tribeType)
                                break;
                            if (piVar2[-1] == _tribeType) {
                                _lookupValue3 = _lookupValue3 + 1;
                                break;
                            }
                            if (*piVar2 == _tribeType) {
                                _lookupValue3 = _lookupValue3 + 2;
                                break;
                            }
                            if (piVar2[1] == _tribeType) {
                                _lookupValue3 = _lookupValue3 + 3;
                                break;
                            }
                            if (piVar2[2] == _tribeType) {
                                _lookupValue3 = _lookupValue3 + 4;
                                break;
                            }
                            if (piVar2[3] == _tribeType) {
                                _lookupValue3 = _lookupValue3 + 5;
                                break;
                            }
                            _lookupValue3 = _lookupValue3 + 6;
                            piVar2 = piVar2 + 6;
                        } while (_lookupValue3 < 0xc);
                        this->attackInfo.tribeRelatedArrayValue0UpTo12[_counter2] = _lookupValue3;
                        _counter2 = _counter2 + 1;
                        _index = this->attackInfo.tribeIDArraySize;
                    } while (_counter2 < this->attackInfo.tribeIDArraySize);
                }
                _tribeSizeSum = 0;
                iVar3 = 0;
                if (0 < _index) {
                    do {
                        iVar1 = this->attackInfo.tribeIDArray[iVar3];
                        if (tribeSizeSumLimit < _tribeSizeSum) {
                            this->attackInfo.tribeRelatedArrayValue0UpTo12[iVar3] = 0xc;
                            _index = this->attackInfo.tribeIDArraySize;
                        }
                        iVar3 = iVar3 + 1;
                        _tribeSizeSum = _tribeSizeSum + DAT_TribesState::instance.tribes[iVar1].size;
                    } while (iVar3 < _index);
                }
                if (shrinkSize < _index) {
                    this->attackInfo.tribeIDArraySize = shrinkSize;
                }
            }
        }

    }
}
}
