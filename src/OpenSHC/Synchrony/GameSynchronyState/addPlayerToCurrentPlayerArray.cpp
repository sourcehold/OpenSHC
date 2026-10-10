#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EB80
    int GameSynchronyState::addPlayerToCurrentPlayerArray(int playerFullID)
    {
        int _slot;
        int* _pFullIdArrayPlus1_2;
        int* _fullIDArray;
        int* _pFullIdArrayPlus1;
        _fullIDArray = this->currentPlayerFullIDArray + 1;
        int _slot_2 = 1;
        _pFullIdArrayPlus1 = _fullIDArray;
        do {
            if (*_pFullIdArrayPlus1 == playerFullID) {
                return _slot_2;
            }
            _slot_2 = _slot_2 + 1;
            _pFullIdArrayPlus1 = _pFullIdArrayPlus1 + 1;
        } while (_slot_2 < 9);
        if (this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            _slot = 1;
            _pFullIdArrayPlus1_2 = _fullIDArray;
            do {
                if (((*_pFullIdArrayPlus1_2 == -1) || (*_pFullIdArrayPlus1_2 == playerFullID))
                    && _pFullIdArrayPlus1_2[0x1b] <= 0)
                    goto LAB_0047ebf4;
                _slot = _slot + 1;
                _pFullIdArrayPlus1_2 = _pFullIdArrayPlus1_2 + 1;
            } while (_slot < 9);
        }
        _slot = 1;
        while (*_fullIDArray != -1 && *_fullIDArray != playerFullID) {
            _slot = _slot + 1;
            _fullIDArray = _fullIDArray + 1;
            if (8 < _slot) {
                return 0;
            }
        }
    LAB_0047ebf4:
        this->currentPlayerFullIDArray[_slot] = playerFullID;
        return _slot;
    }

}
}
