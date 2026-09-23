#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2F80
    void AICState::moveAttackingUnitsToNextRallyPoint(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;

        for (int i = 0; i < 2; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[190 + i];
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[i + 190])
                continue;

            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::allUnitsReachedTheirDestination,
                    DAT_TribesState::ptr)(tribeID)
                == FALSE)
                continue;

            DAT_TribesState::instance.tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addRallyPointForTribe, this)(tribeID);

            short rallyPointCount = DAT_TribesState::instance.tribes[tribeID].rallyPointCount;
            int rallyPointIndex = DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex + 1;
            if (rallyPointIndex >= rallyPointCount)
                rallyPointIndex = 0;

            int x = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[rallyPointIndex][0];
            int y = DAT_TribesState::instance.tribes[tribeID].rallyPointArray[rallyPointIndex][1];
            int targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = rallyPointIndex;

            if (rallyPointCount <= 0)
                continue;

            if (rallyPointCount <= 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                    DAT_UnitsState::instance.units[targetUnitID].y, x, y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 5)
                    continue;
            } else {
                if (DAT_UnitsState::instance.units[targetUnitID].closestEnemyMicroDistance <= 96)
                    continue;
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                tribeID, x, y, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
        }
    }

}
}
