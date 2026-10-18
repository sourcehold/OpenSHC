#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A920
        undefined4 TroopValueState::findTribeWithMoatAttackBehavior()
        {
            BOOLEnum fullIDIsMinus1;
            for (int tribeID = 1; tribeID < 1250; tribeID = tribeID + 1) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0) {
                    fullIDIsMinus1 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isFullIDEqualsToMinus1,
                        DAT_GameState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner);
                    if (fullIDIsMinus1
                        && DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType == Map::Units::STBT_0x3f7) {
                        this->x = (int)DAT_TribesState::instance.tribes[tribeID].targetX;
                        this->y = (int)DAT_TribesState::instance.tribes[tribeID].targetY;
                        DAT_TroopValueState::instance.attackInfo.field127625_0x42744 = tribeID;
                        return 1;
                    }
                }
            }
            return 0;
        }

    }
}
}
