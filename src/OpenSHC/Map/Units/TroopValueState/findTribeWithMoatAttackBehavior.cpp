#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A920
        BOOLEnum TroopValueState::findTribeWithMoatAttackBehavior()
        {
            for (int tribeID = 1; tribeID < countof(DAT_TribesState::instance.tribes); ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState == 0) {
                    continue;
                }
                BOOLEnum const fullIDIsMinus1
                    = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isFullIDEqualsToMinus1, DAT_GameState::ptr)(
                        DAT_TribesState::instance.tribes[tribeID].owner);
                if (fullIDIsMinus1
                    && DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType == Map::Units::STBT_0x3f7) {
                    this->x = DAT_TribesState::instance.tribes[tribeID].targetX;
                    this->y = DAT_TribesState::instance.tribes[tribeID].targetY;
                    DAT_TroopValueState::instance.attackInfo.field127625_0x42744 = tribeID;
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
