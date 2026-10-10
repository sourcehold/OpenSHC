#include "../Helpers.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_EnemyArrayIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      Iterates all player slots (1-8), filtering for players on a different team than the current   player that are
      either human (currentPlayerFullIDArray != -1) or AI (currentAIArray != 0) and   still have a live lord (or the
      game just started). Populates DAT_RequestedGoodsByWhoArray with up   to 6 enemy player IDs and sets
      DAT_EnemyArrayIndex.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AC650
    void Helpers::BuildEnemyPlayerList()
    {
        int iVar1;
        int _team
            = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
        DAT_EnemyArrayIndex::instance = 0;
        for (int _playerID = 1; _playerID < 9; _playerID++) {
            if (_playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID
                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1
                    || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0))
                && ((int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127) < 400
                    || (iVar1 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_playerID),
                        iVar1 != 0))
                && _team != DAT_GameState::instance.mapAndTime.playerTeams[_playerID]) {
                DAT_RequestedGoodsByWhoArray::instance[DAT_EnemyArrayIndex::instance + 1] = _playerID;
                DAT_EnemyArrayIndex::instance = DAT_EnemyArrayIndex::instance + 1;
                if (5 < DAT_EnemyArrayIndex::instance) {}
            }
        }
    }

}
}
