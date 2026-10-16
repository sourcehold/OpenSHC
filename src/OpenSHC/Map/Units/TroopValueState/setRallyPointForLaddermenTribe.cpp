#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00519790
        void TroopValueState::setRallyPointForLaddermenTribe(int param_1)
        {
            short sVar1;
            BOOLEnum BVar2;
            int iVar3;
            int* piVar4;
            int iVar5;
            iVar3 = 0;
            iVar5 = 1;
            piVar4 = &DAT_TribesState::instance.tribes[1].owner;
            do {
                if (*(short*)(piVar4 + 5) != 0) {
                    BVar2 = MACRO_CALL_MEMBER(
                        Game::GameStateStructures_Func::isFullIDEqualsToMinus1, DAT_GameState::ptr)(*piVar4);
                    if (((BVar2) && (*(AITribeTypeShort*)((int)piVar4 + 0x16) == AI::Tribes::AITT_LADDERMEN))
                        && (iVar3 = iVar3 + 1, iVar3 == DAT_TribesState::instance.tribes[param_1].someCounter1 + 1)) {
                        sVar1 = DAT_TribesState::instance.tribes[iVar5].selectionTargetUnitID;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                            DAT_PathFindingState::ptr)(-1, (int)((int)(DAT_UnitsState::instance.units[sVar1].x)),
                            (int)((int)(DAT_UnitsState::instance.units[sVar1].y)));
                        sVar1 = (short)DAT_PathFindingState::instance.ALG_ResultY;
                        DAT_TribesState::instance.tribes[param_1].rallyPointArray[0][0]
                            = (short)DAT_PathFindingState::instance.ALG_ResultX;
                        DAT_TribesState::instance.tribes[param_1].rallyPointArray[0][1] = sVar1;
                    }
                }
                piVar4 = piVar4 + 0xcd;
                iVar5 = iVar5 + 1;
                if (0x176238b < (int)piVar4) {}
            } while (true);
        }

    }
}
}
