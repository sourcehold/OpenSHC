#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0580
    BOOLEnum AICState ::aiOfTypeInCurrentGame(int param_1)

    {

        int* _ptrCurrentAIArray;

        PlayerData* _playerData;

        _playerData = &DAT_GameState::instance.playerDataArray[1];

        _ptrCurrentAIArray = DAT_GameSynchronyState::instance.currentAIArray + 1;

        while (((*_ptrCurrentAIArray == 0 || (_playerData->lordKilledByPlayerID != 0))
            || (param_1 != _playerData->aiType + ~OpenSHC::AI::AIT_NULL))) {

            _ptrCurrentAIArray = _ptrCurrentAIArray + 1;

            _playerData = _playerData + 0xe7d;

            if (0x191de9f < (int)_ptrCurrentAIArray) {

                return FALSE;
            }
        }

        return TRUE;
    }

}
}
