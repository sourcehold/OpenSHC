#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFA10
    void AICState::addRallyPointForTribe(int tribeID)
    {
        DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
        for (int unitID = 1; unitID < 2500; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE)
                continue;
            if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getTeamsDifferent, DAT_GameState::ptr)(
                    DAT_TribesState::instance.tribes[tribeID].owner, DAT_UnitsState::instance.units[unitID].owner)
                != FALSE)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_CATAPULT
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_TREBUCHET
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_S_FBALLISTA)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unknownSiegeTentRelated02 != 3)
                continue;

            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                DAT_PathFindingState::ptr)(-1, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
            DAT_TribesState::instance.tribes[tribeID]
                .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                = DAT_PathFindingState::instance.ALG_ResultX;
            DAT_TribesState::instance.tribes[tribeID]
                .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                = DAT_PathFindingState::instance.ALG_ResultY;
            DAT_TribesState::instance.tribes[tribeID].rallyPointCount++;
            if (DAT_TribesState::instance.tribes[tribeID].rallyPointCount >= 9)
                break;
        }

        if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex < 0)
            DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex
            >= DAT_TribesState::instance.tribes[tribeID].rallyPointCount)
            DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
    }

}
}
