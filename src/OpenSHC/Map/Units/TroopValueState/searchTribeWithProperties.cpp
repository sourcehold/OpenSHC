#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005182A0
        BOOLEnum TroopValueState::searchTribeWithProperties(int param_1)
        {
            if (DAT_TroopValueState::instance.attackInfo.nof_tribes[param_1] == 0) {
                return FALSE;
            }
            int _owner = 0;
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].tribeState == 2
                    && DAT_TribesState::instance.tribes[_tribeID].owner
                    && DAT_TribesState::instance.tribes[_tribeID].owner
                        != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    _owner = DAT_TribesState::instance.tribes[_tribeID].owner;
                    break;
                }
            }
            if (!_owner) {
                DAT_TroopValueState::instance.attackInfo.nof_tribes[param_1] = 0;
                DAT_TroopValueState::instance.attackInfo.unknownByteArray02[param_1] = 0;
                return FALSE;
            }
            DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1] = (byte)_owner;
            DAT_TroopValueState::instance.attackInfo.attacker = (int)(char)(byte)_owner;
            DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 10000;
            DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 3;
            DAT_TroopValueState::instance.attackInfo.value10 = 10;
            return TRUE;
        }

    }
}
}
