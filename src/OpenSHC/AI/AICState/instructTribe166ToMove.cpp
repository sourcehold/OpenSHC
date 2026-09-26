#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD7B0
    void AICState::instructTribe166ToMove(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return;
        int aicIndex = aiType - 1;

        if (DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 > 0)
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01--;
        if (DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 > 50)
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 = 50;

        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[166];
        BOOLEnum keepEnclosed = MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);
        if (tribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[166])
            return;

        if (DAT_TribesState::instance.tribes[tribeID].size
            < DAT_GameState::instance.playerDataArray[playerID].totalTroopsType6 - 5)
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitsToTribe166, this)(playerID);

        if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0 && keepEnclosed == FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            return;
        }

        if (DAT_TribesState::instance.tribes[tribeID].size < this->aics[aicIndex].SortieUnitRangedMin) {
            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            return;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].someXPosition <= 0
            || DAT_GameState::instance.playerDataArray[playerID].someYPosition <= 0) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits, DAT_TribesState::ptr)(
            tribeID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
            tribeID, DAT_GameState::instance.playerDataArray[playerID].someXPosition,
            DAT_GameState::instance.playerDataArray[playerID].someYPosition, 0, 0,
            OpenSHC::Map::Units::Instructions::UMSE_0);
        DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
    }
}
}
