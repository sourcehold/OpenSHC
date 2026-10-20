#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522720
        int TribesState::getAvailableTribeID(int playerID)
        {
            /*
              Early returns rather than the decompiler's nested `if (0 < _tribeID)` arms:
              the original places each `xor eax, eax` inline behind its own guard.
             */
            int _tribeID;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                _tribeID = 1249;
                while (this->tribes[_tribeID].tribeState != 0 || this->tribes[_tribeID].time != 0) {
                    _tribeID = _tribeID + -1;
                    DAT_CurrentTribeID::instance = _tribeID;
                    if (_tribeID <= 0) {
                        return 0;
                    }
                }
                DAT_CurrentTribeID::instance = _tribeID;
                if (_tribeID <= 0) {
                    return 0;
                }
                this->tribes[_tribeID].time = 1;
                return _tribeID;
            }
            _tribeID = 1250 - playerID;
            DAT_CurrentTribeID::instance = _tribeID;
            if (_tribeID <= 0) {
                return 0;
            }
            /*
              is tribe slot in use?
             */
            while (this->tribes[_tribeID].tribeState != 0 || this->tribes[_tribeID].time != 0) {
                _tribeID = _tribeID + -8;
                DAT_CurrentTribeID::instance = _tribeID;
                if (_tribeID <= 0) {
                    return 0;
                }
            }
            DAT_CurrentTribeID::instance = _tribeID;
            if (_tribeID <= 0) {
                return 0;
            }
            /*
              claim it
             */
            this->tribes[_tribeID].time = (short)DAT_GameCore::instance.mapTimeInTicks + 400;
            return _tribeID;
        }

    }
}
}
