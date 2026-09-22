#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD8F0
    void AICState::giveMoveCommandToSortieUnits(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;

        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[167];
        int aicIndex = aiType - 1;
        if (tribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[167])
            return;

        if (DAT_TribesState::instance.tribes[tribeID].size
            < DAT_GameState::instance.playerDataArray[playerID].totalTroopsType7 - 1)
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::syncBehaviourType7UnitTribes, this)(playerID);

        int targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker <= 0) {
            if (DAT_TribesState::instance.tribes[tribeID].size < this->aics[aicIndex].SortieUnitMeleeMin) {
                DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
                return;
            }

            int unitID = DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID;
            if (unitID != 0
                && DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitUID
                    == DAT_UnitsState::instance.units[unitID].uid
                && MACRO_CALL_MEMBER(
                       OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                       DAT_PathFindingState::ptr)(playerID,
                       (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[targetUnitID]
                               .tile],
                       (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
                       0)
                    != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits,
                    DAT_TribesState::ptr)(tribeID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    tribeID, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 0, 0,
                    OpenSHC::Map::Units::Instructions::UMSE_0);
                DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
                return;
            }
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
        DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
    }
}
}
