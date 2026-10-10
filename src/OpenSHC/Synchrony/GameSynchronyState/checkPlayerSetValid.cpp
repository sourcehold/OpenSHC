#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E8F0
    int GameSynchronyState::checkPlayerSetValid()
    {
        int* _pFullIDs;
        int _somePlayerID;
        int _someCounter;
        int _validPlayerCount;
        int local_2c;
        int _teamMemberCounts[9];
        _someCounter = 0;
        _validPlayerCount = 0;
        _teamMemberCounts[0] = 0;
        _teamMemberCounts[1] = 0;
        _teamMemberCounts[2] = 0;
        _teamMemberCounts[3] = 0;
        _teamMemberCounts[4] = 0;
        _teamMemberCounts[5] = 0;
        _teamMemberCounts[6] = 0;
        _teamMemberCounts[7] = 0;
        _teamMemberCounts[8] = 0;
        _pFullIDs = DAT_GameSynchronyState::instance.currentPlayerFullIDArray + 1;
        local_2c = 2;
        do {
            if (*_pFullIDs == -1) {
                /*
                  no human player in this slot
                 */
                if (_pFullIDs[0x1b] != 0)
                    goto LAB_0047e967;
            } else {
                _someCounter = _someCounter + 1;
            LAB_0047e967:
                _teamMemberCounts[_pFullIDs[-0x1e8232]] = _teamMemberCounts[_pFullIDs[-0x1e8232]] + 1;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    _someCounter = _someCounter + 1;
                }
            }
            if ((((_pFullIDs[1] != -1) && (_someCounter = _someCounter + 1, _pFullIDs[1] != -1))
                    || (_pFullIDs[0x1c] != 0))
                && (_teamMemberCounts[_pFullIDs[-0x1e8231]] = _teamMemberCounts[_pFullIDs[-0x1e8231]] + 1,
                    DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                _someCounter = _someCounter + 1;
            }
            if ((((_pFullIDs[2] != -1) && (_someCounter = _someCounter + 1, _pFullIDs[2] != -1))
                    || (_pFullIDs[0x1d] != 0))
                && (_teamMemberCounts[_pFullIDs[-0x1e8230]] = _teamMemberCounts[_pFullIDs[-0x1e8230]] + 1,
                    DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                _someCounter = _someCounter + 1;
            }
            if ((((_pFullIDs[3] != -1) && (_someCounter = _someCounter + 1, _pFullIDs[3] != -1))
                    || (_pFullIDs[0x1e] != 0))
                && (_teamMemberCounts[_pFullIDs[-0x1e822f]] = _teamMemberCounts[_pFullIDs[-0x1e822f]] + 1,
                    DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                _someCounter = _someCounter + 1;
            }
            _pFullIDs = _pFullIDs + 4;
            local_2c = local_2c + -1;
            if (!local_2c) {
                if (1 < _someCounter) {
                    _somePlayerID = 1;
                    while (_teamMemberCounts[_somePlayerID] == 0
                        || (_validPlayerCount = _validPlayerCount + 1, _teamMemberCounts[_somePlayerID] < 3)) {
                        _somePlayerID = _somePlayerID + 1;
                        if (8 < _somePlayerID) {
                            return _validPlayerCount;
                        }
                    }
                }
                return 0;
            }
        } while (true);
    }

}
}
