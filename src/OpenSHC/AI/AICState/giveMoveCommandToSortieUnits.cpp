#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD8F0
    void AICState ::giveMoveCommandToSortieUnits(int playerID)
    {
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == 0)
            return;

        int _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xa7];
        if (_tribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[_tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xa7])
            return;

        if ((int)DAT_TribesState::instance.tribes[_tribeID].size
            < DAT_GameState::instance.playerDataArray[playerID].totalTroopsType7 + -1)
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::syncBehaviourType7UnitTribes, this)(playerID);

        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0) {
            // nervous: send to keep then set stance
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(_tribeID, playerID);
            DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            return;
        }

        if ((int)DAT_TribesState::instance.tribes[_tribeID].size
            < *(int*)((int)this + (_aiType + -1) * 0x2a4 + 0x154)) {
            // tribe too small: just set stance
            DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            return;
        }

        int _unitID = DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitID;
        int iVar1;
        if (((_unitID != 0)
                && (DAT_GameState::instance.playerDataArray[playerID].lastEncounteredTroopUnitUID
                    == DAT_UnitsState::instance.units[_unitID].uid))
            && (iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(playerID,
                    (dword)((int)((int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_UnitsState::instance
                                    .units[DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID].tile])),
                    (dword)((int)((int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_UnitsState::instance.units[_unitID].tile])),
                    0),
                iVar1 != 0)) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits,
                DAT_TribesState::ptr)(_tribeID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                DAT_TribesState::ptr)(_tribeID,
                (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].x)),
                (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].y)), 0, 0,
                OpenSHC::Map::Units::Instructions::UMSE_0);
            DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(_tribeID, playerID);
        DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
    }
}
}
