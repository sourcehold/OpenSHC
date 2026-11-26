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

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00519690
        void TroopValueState::buildRallyPointsFromSiegeUnits(int tribeID)
        {
            DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
            for (int siegeTribeID = 1; siegeTribeID < countof(DAT_TribesState::instance.tribes); ++siegeTribeID) {
                if (!DAT_TribesState::instance.tribes[siegeTribeID].tribeState) {
                    continue;
                }
                BOOLEnum const fullIDIsMinus1
                    = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isFullIDEqualsToMinus1, DAT_GameState::ptr)(
                        DAT_TribesState::instance.tribes[siegeTribeID].owner);
                if (!fullIDIsMinus1) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[siegeTribeID].tribeType != AI::Tribes::AITT_CATAPULT
                    && DAT_TribesState::instance.tribes[siegeTribeID].tribeType != AI::Tribes::AITT_TREBUCHET) {
                    continue;
                }
                int const unitID = DAT_TribesState::instance.tribes[siegeTribeID].selectionTargetUnitID;
                if (DAT_UnitsState::instance.units[unitID].stoneAmmunition <= 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                    DAT_PathFindingState::ptr)(
                    -1, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                    = DAT_PathFindingState::instance.ALG_ResultX;
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                    = DAT_PathFindingState::instance.ALG_ResultY;
                ++DAT_TribesState::instance.tribes[tribeID].rallyPointCount;
            }
            if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex < 0) {
                DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
            }
            if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex
                >= DAT_TribesState::instance.tribes[tribeID].rallyPointCount) {
                DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
            }
        }

    }
}
}
