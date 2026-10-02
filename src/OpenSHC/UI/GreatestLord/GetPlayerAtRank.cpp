#include "../GreatestLord.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0044B760
    int GreatestLord::GetPlayerAtRank(int rankingPosition)
    {
        int _rank;
        int _playerID;
        int _ranking[9];
        _ranking[0] = -1;
        _ranking[1] = -1;
        _ranking[2] = -1;
        _ranking[3] = -1;
        _ranking[4] = -1;
        _ranking[5] = -1;
        _ranking[6] = -1;
        _ranking[7] = -1;
        _ranking[8] = -1;
        _playerID = 0;
        do {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1)
                || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {
                _rank = MACRO_CALL(OpenSHC::Audio::SFX_Func::ComputePlayerRanking)(_playerID);
                _ranking[_rank] = _playerID;
            }
            _playerID = _playerID + 1;
        } while (_playerID < 9);
        return _ranking[rankingPosition + 1];
    }

}
}
