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

        // FUNCTION: STRONGHOLDCRUSADER 0x00519690
        void TroopValueState::buildRallyPointsFromSiegeUnits(int tribeID)
        {
            short* psVar1;
            int sVar2;
            BOOLEnum BVar3;
            DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (DAT_TribesState::instance.tribes[_tribeID].tribeState) {
                    BVar3 = MACRO_CALL_MEMBER(
                        Game::GameStateStructures_Func::isFullIDEqualsToMinus1, DAT_GameState::ptr)(DAT_TribesState::instance.tribes[_tribeID].owner);
                    if (BVar3) {
                        if (((DAT_TribesState::instance.tribes[_tribeID].tribeType == ((AITribeType)0x16)) || (DAT_TribesState::instance.tribes[_tribeID].tribeType == ((AITribeType)0x17)))
                            && (sVar2 = (int)DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID,
                                0 < DAT_UnitsState::instance.units[sVar2].stoneAmmunition)) {
                            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                                DAT_PathFindingState::ptr)(-1, (int)(DAT_UnitsState::instance.units[sVar2].x),
                                (int)(DAT_UnitsState::instance.units[sVar2].y));
                            DAT_TribesState::instance.tribes[tribeID]
                                .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                                = (short)DAT_PathFindingState::instance.ALG_ResultX;
                            DAT_TribesState::instance.tribes[tribeID]
                                .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                                = (short)DAT_PathFindingState::instance.ALG_ResultY;
                            DAT_TribesState::instance.tribes[tribeID].rallyPointCount
                                = DAT_TribesState::instance.tribes[tribeID].rallyPointCount + 1;
                        }
                    }
                }
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
