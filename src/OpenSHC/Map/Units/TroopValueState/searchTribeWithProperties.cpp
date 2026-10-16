#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

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
            if (this->attackInfo.nof_tribes[param_1] == 0) {
                return FALSE;
            }
            _tribeID = 1;
            piVar1 = &DAT_TribesState::instance.tribes[1];
            while (((piVar1->tribeState != 2 || (!piVar1->owner))
                || (piVar1->owner == DAT_GameSynchronyState::instance.currentPlayerSlotID))) {
                piVar1 = piVar1 + 0xcd;
                _tribeID = _tribeID + 1;
                if (0x176238b < (int)piVar1) {
                LAB_005182f7:
                    this->attackInfo.nof_tribes[param_1] = 0;
                    this->attackInfo.unknownByteArray02[param_1] = 0;
                    return FALSE;
                }
            }
            _owner = DAT_TribesState::instance.tribes[_tribeID].owner;
            if (_owner) {
                this->attackInfo.attackWavePlayerIDArray[param_1] = (byte)_owner;
                this->attackInfo.attacker = (int)(char)(byte)_owner;
                this->attackInfo.attackWaveTicker[param_1] = 10000;
                this->attackInfo.value3Array01[param_1] = 3;
                this->attackInfo.value10 = 10;
                return TRUE;
            }
            goto LAB_005182f7;
        }

    }
}
}
