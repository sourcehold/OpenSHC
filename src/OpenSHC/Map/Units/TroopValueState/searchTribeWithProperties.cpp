#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

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
            Tribe* piVar1;
            int _tribeID;
            int _owner;
            if (DAT_TroopValueState::instance.attackInfo.nof_tribes[param_1] == 0) {
                return FALSE;
            }
            _tribeID = 1;
            piVar1 = &DAT_TribesState::instance.tribes[1];
            while (piVar1->tribeState != 2 || !piVar1->owner
                || piVar1->owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                piVar1 = piVar1 + 0xcd;
                _tribeID = _tribeID + 1;
                if (0x176238b < (int)piVar1) {
                LAB_005182f7:
                    DAT_TroopValueState::instance.attackInfo.nof_tribes[param_1] = 0;
                    DAT_TroopValueState::instance.attackInfo.unknownByteArray02[param_1] = 0;
                    return FALSE;
                }
            }
            _owner = DAT_TribesState::instance.tribes[_tribeID].owner;
            if (_owner) {
                DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray[param_1] = (byte)_owner;
                DAT_TroopValueState::instance.attackInfo.attacker = (int)(char)(byte)_owner;
                DAT_TroopValueState::instance.attackInfo.attackWaveTicker[param_1] = 10000;
                DAT_TroopValueState::instance.attackInfo.value3Array01[param_1] = 3;
                DAT_TroopValueState::instance.attackInfo.value10 = 10;
                return TRUE;
            }
            goto LAB_005182f7;
        }

    }
}
}
