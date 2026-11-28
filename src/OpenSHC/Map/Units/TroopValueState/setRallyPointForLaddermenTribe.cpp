#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map.func.hpp"
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
            int laddermenTribeCount = 0;
            for (int tribeID = 1; tribeID < countof(DAT_TribesState::instance.tribes); ++tribeID) {
                if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0) {
                    if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isFullIDEqualsToMinus1, DAT_GameState::ptr)(
                            DAT_TribesState::instance.tribes[tribeID].owner)
                        && DAT_TribesState::instance.tribes[tribeID].tribeType == AI::Tribes::AITT_LADDERMEN) {
                        ++laddermenTribeCount;
                        if (laddermenTribeCount == DAT_TribesState::instance.tribes[param_1].someCounter1 + 1) {
                            int const _unitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                                DAT_PathFindingState::ptr)(-1, (int)(DAT_UnitsState::instance.units[_unitID].x),
                                (int)(DAT_UnitsState::instance.units[_unitID].y));
                            short const _rallyPointY = (short)DAT_PathFindingState::instance.ALG_ResultY;
                            DAT_TribesState::instance.tribes[param_1].rallyPointArray[0][0]
                                = (short)DAT_PathFindingState::instance.ALG_ResultX;
                            DAT_TribesState::instance.tribes[param_1].rallyPointArray[0][1] = _rallyPointY;
                            return;
                        }
                    }
                }
            }
        }

    }
}
}
