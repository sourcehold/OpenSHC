#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00ee1030.hpp"
#include "OpenSHC/Globals/DAT_00ee1034.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/INT_00ee1038.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053DDD0
        int UnitsState::selectWorkerSpeechOrMoraleStateID(int unitID)
        {
            int _blockingState
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getWorkerBlockingStateIfStuck, this)(unitID);
            if (_blockingState != 0) {
                return _blockingState;
            }
            int _rng = this->units[unitID].fixedRng;
            int _rngMod4 = _rng % 4;
            if (unitID != INT_00ee1038::instance) {
                INT_00ee1038::instance = unitID;
                if (DAT_UnitPropertiesDefinedData::instance.field_0x12260 == 25) {
                    DAT_UnitPropertiesDefinedData::instance.field_0x12260 = 0;
                    DAT_UnitPropertiesDefinedData::instance.field_0x12264 = 25;
                    DAT_UnitPropertiesDefinedData::instance.field_0x12268 = 10;
                } else if (DAT_UnitPropertiesDefinedData::instance.field_0x12264 == 25) {
                    DAT_UnitPropertiesDefinedData::instance.field_0x12260 = 10;
                    DAT_UnitPropertiesDefinedData::instance.field_0x12264 = 0;
                    DAT_UnitPropertiesDefinedData::instance.field_0x12268 = 25;
                } else if (DAT_UnitPropertiesDefinedData::instance.field_0x12268 == 25) {
                    DAT_UnitPropertiesDefinedData::instance.field_0x12260 = 25;
                    DAT_UnitPropertiesDefinedData::instance.field_0x12264 = 10;
                    DAT_UnitPropertiesDefinedData::instance.field_0x12268 = 0;
                }
            }
            int _worstPopularityReason = -1;
            int _worstPopularityValue = 0;
            for (int i = 0; i < 32; ++i) {
                if (i < 5) {
                    continue;
                }
                if (i > 5 && (i < 11 || i == 20 || i > 22)) {
                    continue;
                }
                if (DAT_GameState::instance.mapAndTime.scenarioEventTimers[i] < 40) {
                    continue;
                }
                if (_worstPopularityReason == -1
                    || DAT_GameState::instance.mapAndTime.scenarioEventTimers[i] < _worstPopularityValue) {
                    _worstPopularityReason = i;
                    _worstPopularityValue = DAT_GameState::instance.mapAndTime.scenarioEventTimers[i];
                }
            }
            if (_worstPopularityReason != -1) {
                if (DAT_UnitPropertiesDefinedData::instance.field_0x1225c == _worstPopularityReason) {
                    DAT_00ee1034::instance = DAT_00ee1034::instance + 1;
                    if (DAT_00ee1034::instance > 1) {
                        DAT_GameState::instance.mapAndTime.scenarioEventTimers[_worstPopularityReason] = 0;
                    }
                } else {
                    DAT_00ee1034::instance = 0;
                    DAT_UnitPropertiesDefinedData::instance.field_0x1225c = _worstPopularityReason;
                }
                switch (_worstPopularityReason) {
                case 5:
                    return _rngMod4 + 116;
                case 11:
                    return (MACRO_CALL(OpenSHC::Map::Units_Func::CurrentUnitHasHealer)() != FALSE) + 103;
                case 12:
                    return 121;
                case 13:
                    return 122;
                case 14:
                    return 124;
                case 15:
                    return 120;
                case 16:
                    return (_rng & 1) + 108;
                case 17:
                    return (_rng & 1) + 106;
                case 18:
                    return 105;
                case 19:
                    return 123;
                case 21:
                    return _rngMod4 + 110;
                case 22:
                    return (_rng & 1) + 114;
                }
            }
            int _bestSpeechID = -1;
            int _candidateCount = 0;
            int _bestWeight = 0;
            int _candidateSpeechID = 0;
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .totalEnemyUnitsCount
                    < 10
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER
                || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                    && DAT_GameCore::instance.missionNumber1to20 >= 16)) {
                DAT_00ee1030::instance = 0;
            } else {
                DAT_00ee1030::instance = DAT_00ee1030::instance + 1;
                _candidateSpeechID = _rngMod4 + 98;
                _bestWeight = 80;
                if ((int)DAT_00ee1030::instance > 2) {
                    _bestWeight = (4 - DAT_00ee1030::instance) * 20;
                    if (_bestWeight < 20) {
                        _bestWeight = 20;
                    }
                }
                _candidateCount = 100;
                _bestSpeechID = _candidateSpeechID;
            }
            int _weight = 0;
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .rationsSetting
                == 0) {
                _weight = 10;
                _candidateSpeechID = _rngMod4 + 60;
            } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .rationsSetting
                == 1) {
                _weight = 20;
                _candidateSpeechID = _rngMod4 + 64;
            } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .rationsSetting
                == 4) {
                _weight = 20;
                _candidateSpeechID = _rngMod4 + 68;
            }
            if (_weight != 0) {
                _candidateCount = _candidateCount + 1;
                if (_bestSpeechID == -1
                    || _weight + DAT_UnitPropertiesDefinedData::instance.field_0x12260 > _bestWeight) {
                    _bestWeight = _weight + DAT_UnitPropertiesDefinedData::instance.field_0x12260;
                    _bestSpeechID = _candidateSpeechID;
                }
            }
            int _taxesSetting
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .taxesSetting;
            if (_taxesSetting <= 3 || _taxesSetting >= 8) {
                _weight = 0;
                if (_taxesSetting == 0) {
                    _candidateSpeechID = _rngMod4 + 73;
                    _weight = 20;
                } else if (_taxesSetting == 1) {
                    _weight = 15;
                    _candidateSpeechID = _rngMod4 + 77;
                } else if (_taxesSetting == 2) {
                    _weight = 10;
                    _candidateSpeechID = _rngMod4 + 81;
                } else if (_taxesSetting == 3) {
                    _weight = 5;
                    _candidateSpeechID = _rngMod4 + 85;
                } else if (_taxesSetting == 8) {
                    _weight = 15;
                    _candidateSpeechID = _rngMod4 + 89;
                } else if (_taxesSetting == 9 || _taxesSetting == 10 || _taxesSetting == 11) {
                    _candidateSpeechID = _rngMod4 + 93;
                    _weight = 20;
                }
                if (_weight != 0) {
                    _candidateCount = _candidateCount + 1;
                    if (_bestSpeechID == -1
                        || _weight + DAT_UnitPropertiesDefinedData::instance.field_0x12264 > _bestWeight) {
                        _bestWeight = _weight + DAT_UnitPropertiesDefinedData::instance.field_0x12264;
                        _bestSpeechID = _candidateSpeechID;
                    }
                }
            }
            int _productivity
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .fearFactorProductivityUnk;
            _weight = 0;
            if (_productivity < 100) {
                _candidateCount = _candidateCount + 1;
                if (_productivity < 60) {
                    _weight = 25;
                    _candidateSpeechID = _rngMod4 + 18;
                } else if (_productivity < 70) {
                    _weight = 20;
                    _candidateSpeechID = _rngMod4 + 14;
                } else if (_productivity < 80) {
                    _weight = 15;
                    _candidateSpeechID = _rngMod4 + 10;
                } else if (_productivity < 90) {
                    _weight = 10;
                    _candidateSpeechID = _rngMod4 + 6;
                } else {
                    _weight = 5;
                    _candidateSpeechID = _rngMod4 + 2;
                }
            }
            if (_productivity > 100) {
                _candidateCount = _candidateCount + 1;
                if (this->units[unitID].productivityDiv100 == 0
                    || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isWorkerAtProductionIdleState, this)(
                           unitID)
                        == 0) {
                    if (_productivity < 110) {
                        _weight = 5;
                        _candidateSpeechID = _rngMod4 + 27;
                    } else if (_productivity < 120) {
                        _weight = 10;
                        _candidateSpeechID = _rngMod4 + 31;
                    } else if (_productivity < 130) {
                        _weight = 15;
                        _candidateSpeechID = _rngMod4 + 35;
                    } else if (_productivity < 140) {
                        _weight = 20;
                        _candidateSpeechID = _rngMod4 + 39;
                    } else {
                        _weight = 25;
                        _candidateSpeechID = _rngMod4 + 43;
                    }
                } else {
                    switch (this->units[unitID].productivityDiv100) {
                    case 1:
                        _weight = 10;
                        _candidateSpeechID = 22;
                        break;
                    case 2:
                        _weight = 15;
                        _candidateSpeechID = 23;
                        break;
                    case 3:
                        _weight = 20;
                        _candidateSpeechID = 24;
                        break;
                    case 4:
                        _weight = 25;
                        _candidateSpeechID = 25;
                        break;
                    default:
                        _weight = 25;
                        _candidateSpeechID = 26;
                    }
                }
            }
            if (_productivity > 100 || _weight != 0) {
                if (_bestSpeechID == -1
                    || DAT_UnitPropertiesDefinedData::instance.field_0x12268 + _weight > _bestWeight) {
                    _bestSpeechID = _candidateSpeechID;
                }
            }
            if (_candidateCount == 1 && SEC_RNG::instance.currentNumber1 % 3 == 0) {
                _bestSpeechID = 1;
            } else if (_bestSpeechID == -1) {
                return 1;
            }
            if (_candidateSpeechID < 98) {
                DAT_00ee1030::instance = 0;
            }
            return _bestSpeechID;
        }

    }
}
}
