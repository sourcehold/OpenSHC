#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/AI/Tribes/AITribeType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518A10
        void TroopValueState::assignBehaviorTypeAndLinkSupportTribe(
            int param_1, int param_2, SomeTribeBehaviorType param_3, undefined4 param_4, undefined4 param_5)
        {
            if (param_2 <= 0) {
                param_2 = 2;
            }
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].owner == param_2) {
                    DAT_TribesState::instance.tribes[_tribeID].tribeID = 0;
                }
            }
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.tribeIDArraySize; i = i + 1) {
                int _tribeID = DAT_TroopValueState::instance.attackInfo.tribeIDArray[i];
                if (11 <= DAT_TroopValueState::instance.attackInfo.tribeRelatedArrayValue0UpTo12[i]) {
                    continue;
                }
                int _supportTribeID = (int)DAT_TribesState::instance.tribes[_tribeID].supportTribeID;
                if (_supportTribeID
                    && DAT_TribesState::instance.tribes[_tribeID].uid2
                        == DAT_TribesState::instance.tribes[_supportTribeID].uid) {
                    continue;
                }
                DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType = (undefined2)param_3;
                DAT_TribesState::instance.tribes[_tribeID].someUpdateUpperLimit
                    = ((short)i + 1) * (short)param_5 + (short)param_4;
                DAT_TribesState::instance.tribes[_tribeID].attackInfo_someCounter1
                    = (short)DAT_TroopValueState::instance.attackInfo.someCounter1;
                DAT_TribesState::instance.tribes[_tribeID].unknownAttackRelatedUpdateCounter = 0;
                _supportTribeID = 0;
                for (int _candidate = 1; _candidate < 1250; _candidate = _candidate + 1) {
                    if (DAT_TribesState::instance.tribes[_candidate].tribeState != 0
                        && DAT_TribesState::instance.tribes[_candidate].tribeState != 3
                        && DAT_TribesState::instance.tribes[_candidate].owner
                            == DAT_TribesState::instance.tribes[_tribeID].owner
                        && DAT_TribesState::instance.tribes[_candidate].tribeID == 0
                        && (DAT_TribesState::instance.tribes[_candidate].tribeType == ((AITribeType)0x16)
                            || (DAT_TribesState::instance.tribes[_candidate].tribeType == ((AITribeType)0x17)))) {
                        _supportTribeID = _candidate;
                        break;
                    }
                }
                if (!_supportTribeID) {
                    for (int _candidate = 1; _candidate < 1250; _candidate = _candidate + 1) {
                        if (DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] == 4) {
                            break;
                        }
                        if (DAT_TribesState::instance.tribes[_candidate].tribeState != 0
                            && DAT_TribesState::instance.tribes[_candidate].tribeState != 3
                            && DAT_TribesState::instance.tribes[_candidate].owner
                                == DAT_TribesState::instance.tribes[_tribeID].owner
                            && DAT_TribesState::instance.tribes[_candidate].tribeID == 0
                            && (DAT_TribesState::instance.tribes[_candidate].tribeType == AI::Tribes::AITT_ARCHERS
                                || (DAT_TribesState::instance.tribes[_candidate].tribeType
                                    == AI::Tribes::AITT_CROSSBOWMEN))) {
                            _supportTribeID = _candidate;
                            break;
                        }
                    }
                }
                if (_supportTribeID) {
                    DAT_TribesState::instance.tribes[_tribeID].supportTribeID = (short)_supportTribeID;
                    DAT_TribesState::instance.tribes[_tribeID].uid2
                        = DAT_TribesState::instance.tribes[_supportTribeID].uid;
                    DAT_TribesState::instance.tribes[_supportTribeID].tribeID = (short)_tribeID;
                }
            }
        }

    }
}
}
