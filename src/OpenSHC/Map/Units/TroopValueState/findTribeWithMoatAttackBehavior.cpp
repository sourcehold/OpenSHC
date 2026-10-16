#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A920
        undefined4 TroopValueState::findTribeWithMoatAttackBehavior()
        {
            BOOLEnum BVar1;
            int* piVar2;
            int iVar3;
            iVar3 = 1;
            piVar2 = &DAT_TribesState::instance.tribes[1].owner;
            do {
                if (*(short*)(piVar2 + 5) != 0) {
                    BVar1 = MACRO_CALL_MEMBER(
                        Game::GameStateStructures_Func::isFullIDEqualsToMinus1, DAT_GameState::ptr)(*piVar2);
                    if ((BVar1) && (*(SomeTribeBehaviorTypeShort*)(piVar2 + 9) == Map::Units::STBT_0x3f7)) {
                        this->x = (int)DAT_TribesState::instance.tribes[iVar3].targetX;
                        this->y = (int)DAT_TribesState::instance.tribes[iVar3].targetY;
                        this->attackInfo.field127625_0x42744 = iVar3;
                        return (undefined4)(1);
                    }
                }
                piVar2 = piVar2 + 0xcd;
                iVar3 = iVar3 + 1;
                if (0x176238b < (int)piVar2) {
                    return (undefined4)(0);
                }
            } while (true);
        }

    }
}
}
