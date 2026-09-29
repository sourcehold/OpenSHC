#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
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
            uint _rng = this->units[unitID].fixedRng;
            uint _rngMod4 = _rng % 4;
            if (unitID != INT_00ee1038::instance) {
                INT_00ee1038::instance = unitID;
                if (DAT_UnitPropertiesDefinedData::instance.field125_0x12260 == 0x19) {
                    DAT_UnitPropertiesDefinedData::instance.field125_0x12260 = 0;
                    DAT_UnitPropertiesDefinedData::instance.field126_0x12264 = 0x19;
                    DAT_UnitPropertiesDefinedData::instance.field127_0x12268 = 10;
                } else if (DAT_UnitPropertiesDefinedData::instance.field126_0x12264 == 0x19) {
                    DAT_UnitPropertiesDefinedData::instance.field125_0x12260 = 10;
                    DAT_UnitPropertiesDefinedData::instance.field126_0x12264 = 0;
                    DAT_UnitPropertiesDefinedData::instance.field127_0x12268 = 0x19;
                } else if (DAT_UnitPropertiesDefinedData::instance.field127_0x12268 == 0x19) {
                    DAT_UnitPropertiesDefinedData::instance.field125_0x12260 = 0x19;
                    DAT_UnitPropertiesDefinedData::instance.field126_0x12264 = 10;
                    DAT_UnitPropertiesDefinedData::instance.field127_0x12268 = 0;
                }
            }
            int _worstPopularityReason = -1;
            int _worstPopularityValue = 0;
            for (int i = 0; i < 0x20; ++i) {
                if (i <= 4 || (i >= 6 && i <= 10) || i == 0x14 || i >= 0x17) {
                    continue;
                }
                if ((&DAT_GameState::instance.mapAndTime.field3092_0x2654)[i] <= 0x27) {
                    continue;
                }
                if (_worstPopularityReason == -1
                    || (&DAT_GameState::instance.mapAndTime.field3092_0x2654)[i] < _worstPopularityValue) {
                    _worstPopularityReason = i;
                    _worstPopularityValue = (&DAT_GameState::instance.mapAndTime.field3092_0x2654)[i];
                }
            }
            if (_worstPopularityReason != -1) {
                if (DAT_UnitPropertiesDefinedData::instance.field124_0x1225c == _worstPopularityReason) {
                    DAT_00ee1034::instance = DAT_00ee1034::instance + 1;
                    if (DAT_00ee1034::instance > 1) {
                        (&DAT_GameState::instance.mapAndTime.field3092_0x2654)[_worstPopularityReason] = 0;
                    }
                } else {
                    DAT_00ee1034::instance = 0;
                    DAT_UnitPropertiesDefinedData::instance.field124_0x1225c = _worstPopularityReason;
                }
                switch (_worstPopularityReason) {
                case 5:
                    return _rngMod4 + 0x74;
                case 0xb:
                    return (MACRO_CALL(OpenSHC::Map::Units_Func::CurrentUnitHasHealer)() != FALSE) + 0x67;
                case 0xc:
                    return 0x79;
                case 0xd:
                    return 0x7a;
                case 0xe:
                    return 0x7c;
                case 0xf:
                    return 0x78;
                case 0x10:
                    return (_rng & 1) + 0x6c;
                case 0x11:
                    return (_rng & 1) + 0x6a;
                case 0x12:
                    return 0x69;
                case 0x13:
                    return 0x7b;
                case 0x15:
                    return _rngMod4 + 0x6e;
                case 0x16:
                    return (_rng & 1) + 0x72;
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
                    && DAT_GameCore::instance.missionNumber1to20 > 0xf)) {
                DAT_00ee1030::instance = 0;
            } else {
                DAT_00ee1030::instance = DAT_00ee1030::instance + 1;
                _candidateSpeechID = _rngMod4 + 0x62;
                _bestWeight = 0x50;
                if (DAT_00ee1030::instance > 2) {
                    _bestWeight = (4 - DAT_00ee1030::instance) * 0x14;
                    if (_bestWeight < 0x14) {
                        _bestWeight = 0x14;
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
                _candidateSpeechID = _rngMod4 + 0x3c;
            } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .rationsSetting
                == 1) {
                _weight = 0x14;
                _candidateSpeechID = _rngMod4 + 0x40;
            } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .rationsSetting
                == 4) {
                _weight = 0x14;
                _candidateSpeechID = _rngMod4 + 0x44;
            }
            if (_weight != 0) {
                _candidateCount = _candidateCount + 1;
                if (_bestSpeechID == -1
                    || _bestWeight < _weight + DAT_UnitPropertiesDefinedData::instance.field125_0x12260) {
                    _bestWeight = _weight + DAT_UnitPropertiesDefinedData::instance.field125_0x12260;
                    _bestSpeechID = _candidateSpeechID;
                }
            }
            int _taxesSetting
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .taxesSetting;
            if (_taxesSetting < 4 || _taxesSetting > 7) {
                _weight = 0;
                if (_taxesSetting == 0) {
                    _candidateSpeechID = _rngMod4 + 0x49;
                    _weight = 0x14;
                } else if (_taxesSetting == 1) {
                    _weight = 0xf;
                    _candidateSpeechID = _rngMod4 + 0x4d;
                } else if (_taxesSetting == 2) {
                    _weight = 10;
                    _candidateSpeechID = _rngMod4 + 0x51;
                } else if (_taxesSetting == 3) {
                    _weight = 5;
                    _candidateSpeechID = _rngMod4 + 0x55;
                } else if (_taxesSetting == 8) {
                    _weight = 0xf;
                    _candidateSpeechID = _rngMod4 + 0x59;
                } else if (_taxesSetting == 9 || _taxesSetting == 10 || _taxesSetting == 0xb) {
                    _candidateSpeechID = _rngMod4 + 0x5d;
                    _weight = 0x14;
                }
                if (_weight != 0) {
                    _candidateCount = _candidateCount + 1;
                    if (_bestSpeechID == -1
                        || _bestWeight < _weight + DAT_UnitPropertiesDefinedData::instance.field126_0x12264) {
                        _bestWeight = _weight + DAT_UnitPropertiesDefinedData::instance.field126_0x12264;
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
                if (_productivity < 0x3c) {
                    _weight = 0x19;
                    _candidateSpeechID = _rngMod4 + 0x12;
                } else if (_productivity < 0x46) {
                    _weight = 0x14;
                    _candidateSpeechID = _rngMod4 + 0xe;
                } else if (_productivity < 0x50) {
                    _weight = 0xf;
                    _candidateSpeechID = _rngMod4 + 10;
                } else if (_productivity < 0x5a) {
                    _weight = 10;
                    _candidateSpeechID = _rngMod4 + 6;
                } else {
                    _weight = 5;
                    _candidateSpeechID = _rngMod4 + 2;
                }
            }
            if (_productivity >= 0x65) {
                _candidateCount = _candidateCount + 1;
                if (this->units[unitID].productivityDiv100 == 0
                    || MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isWorkerAtProductionIdleState, this)(
                           unitID)
                        == 0) {
                    if (_productivity < 0x6e) {
                        _weight = 5;
                        _candidateSpeechID = _rngMod4 + 0x1b;
                    } else if (_productivity < 0x78) {
                        _weight = 10;
                        _candidateSpeechID = _rngMod4 + 0x1f;
                    } else if (_productivity < 0x82) {
                        _weight = 0xf;
                        _candidateSpeechID = _rngMod4 + 0x23;
                    } else if (_productivity < 0x8c) {
                        _weight = 0x14;
                        _candidateSpeechID = _rngMod4 + 0x27;
                    } else {
                        _weight = 0x19;
                        _candidateSpeechID = _rngMod4 + 0x2b;
                    }
                } else {
                    switch (this->units[unitID].productivityDiv100) {
                    case 1:
                        _weight = 10;
                        _candidateSpeechID = 0x16;
                        break;
                    case 2:
                        _weight = 0xf;
                        _candidateSpeechID = 0x17;
                        break;
                    case 3:
                        _weight = 0x14;
                        _candidateSpeechID = 0x18;
                        break;
                    case 4:
                        _weight = 0x19;
                        _candidateSpeechID = 0x19;
                        break;
                    default:
                        _weight = 0x19;
                        _candidateSpeechID = 0x1a;
                    }
                }
            }
            if (_productivity >= 0x65 || _weight != 0) {
                if (_bestSpeechID == -1
                    || _bestWeight < DAT_UnitPropertiesDefinedData::instance.field127_0x12268 + _weight) {
                    _bestSpeechID = _candidateSpeechID;
                }
            }
            if (_candidateCount == 1 && SEC_RNG::instance.currentNumber1 % 3 == 0) {
                _bestSpeechID = 1;
            } else if (_bestSpeechID == -1) {
                return 1;
            }
            if (_candidateSpeechID < 0x62) {
                DAT_00ee1030::instance = 0;
            }
            return _bestSpeechID;
        }

    }
}
}
