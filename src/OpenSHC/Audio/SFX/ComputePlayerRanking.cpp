#include "../../Audio.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Audio {

    /*
      variable _playerPointsArray made by gynt   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0044B680
    int SFX::ComputePlayerRanking(int playerID)
    {
        int _playerID;
        int _highestPointsUnk;
        undefined4 _deadPlayerList[10];
        int _playerPointsArray[9][2];
        _playerPointsArray[0][0] = 0;
        _playerPointsArray[1][0] = 0;
        _playerPointsArray[2][0] = 0;
        _playerPointsArray[3][0] = 0;
        _playerPointsArray[4][0] = 0;
        _playerPointsArray[5][0] = 0;
        _playerPointsArray[6][0] = 0;
        _playerPointsArray[7][0] = 0;
        _playerPointsArray[8][0] = 0;
        int _arrayIndex = 0;
        for (_playerID = 1; _playerID < 9; _playerID++) {
            if (DAT_GameSynchronyState::instance.finalResults.active[_playerID] != 0) {
                _playerPointsArray[_arrayIndex][0] = _playerID;
                int _isAlive = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_playerID);
                if (!_isAlive) {
                    if (_playerID == playerID) {
                        return 0;
                    }
                    _deadPlayerList[_playerID] = 1;
                    _playerPointsArray[_arrayIndex][1] = 0;
                } else {
                    int _playerPoints = MACRO_CALL(Audio::SFX_Func::ComputePlayerPoints1)(_playerID);
                    _playerPointsArray[_arrayIndex][1] = _playerPoints;
                }
                _arrayIndex = _arrayIndex + 1;
            }
        }
        int _index = 0;
        if (0 < _arrayIndex) {
            do {
                int _highestPointsIndex = -1;
                int _index2 = 0;
                do {
                    if ((_playerPointsArray[_index2][0] != 0)
                        && ((_highestPointsIndex == -1 || (_highestPointsUnk < _playerPointsArray[_index2][1])))) {
                        _highestPointsUnk = _playerPointsArray[_index2][1];
                        _highestPointsIndex = _index2;
                    }
                    _index2 = _index2 + 1;
                } while (_index2 < _arrayIndex);
                if (_highestPointsIndex < 0) {
                    return 0;
                }
                if (_playerPointsArray[_highestPointsIndex][0] == playerID) {
                    return _index + 1;
                }
                _index = _index + 1;
                _playerPointsArray[_highestPointsIndex][0] = 0;
            } while (_index < _arrayIndex);
        }
        return 0;
    }

}
}
