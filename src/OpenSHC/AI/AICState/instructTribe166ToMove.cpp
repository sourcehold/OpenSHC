#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD7B0
    void AICState ::instructTribe166ToMove(int playerID)
    {
        AITypeInt _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == OpenSHC::AI::AIT_NULL)
            return;

        int _counter = DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01;
        if (0 < _counter)
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 = _counter + -1;
        if (50 < DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01)
            DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 = 50;

        int _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[166];
        BOOLEnum _keepEnclosed = MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);

        if (_tribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[_tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xa6])
            return;

        if ((int)DAT_TribesState::instance.tribes[_tribeID].size
            < DAT_GameState::instance.playerDataArray[playerID].totalTroopsType6 + -5)
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addUnitsToTribe166, this)(playerID);

        if ((DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker < 1)
            || (_keepEnclosed != FALSE)) {

            if ((int)DAT_TribesState::instance.tribes[_tribeID].size
                < *(int*)((int)this + (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x14c)) {
                // tribe too small: just set stance
                DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
                return;
            }

            if ((0 < DAT_GameState::instance.playerDataArray[playerID].someXPosition)
                && (0 < DAT_GameState::instance.playerDataArray[playerID].someYPosition)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits,
                    DAT_TribesState::ptr)(_tribeID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                    DAT_TribesState::ptr)(_tribeID,
                    (uint)((int)(DAT_GameState::instance.playerDataArray[playerID].someXPosition)),
                    (uint)((int)(DAT_GameState::instance.playerDataArray[playerID].someYPosition)), 0, 0,
                    OpenSHC::Map::Units::Instructions::UMSE_0);
                DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
                return;
            }
        }

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(_tribeID, playerID);
        DAT_TribesState::instance.tribes[_tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
    }
}
}
