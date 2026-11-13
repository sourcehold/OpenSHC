#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC570
        void RecalculateAllies()
        {
            if ((int)DAT_GameCore::instance.mapTimeInTicks - (int)DAT_GameCore::instance.section1127 > 400
                && MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                       DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    == 0) {
                DAT_AlliesCount::instance = 0;
                return;
            }
            int const team
                = DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID];
            DAT_AlliesCount::instance = 0;
            for (int player = 1; player < 9; ++player) {
                if (player == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    continue;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[player] == 0) {
                    continue;
                }
                if ((int)DAT_GameCore::instance.mapTimeInTicks - (int)DAT_GameCore::instance.section1127 > 400
                    && MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                           player)
                        == 0) {
                    continue;
                }
                if (team != DAT_GameState::instance.mapAndTime.playerTeams[player]) {
                    continue;
                }
                DAT_SomeTeamMemberPlayerIDArray::instance[DAT_AlliesCount::instance] = player;
                DAT_AlliesCount::instance += 1;
                if ((int)DAT_AlliesCount::instance >= 6) {
                    break;
                }
            }
            if ((int)DAT_LastTeamMemberIndex::instance >= (int)DAT_AlliesCount::instance) {
                DAT_LastTeamMemberIndex::instance = DAT_AlliesCount::instance - 1;
            }
            if ((int)DAT_LastTeamMemberIndex::instance < 0) {
                DAT_LastTeamMemberIndex::instance = 0;
            }
        }

    }
}
}
