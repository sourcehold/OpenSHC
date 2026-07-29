#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE5F0
    void AICState::sendUnitsToPlayerIDsKeepIfPossible(int playerID1, int playerID2)
    {
        uint _p1_campfireX = DAT_GameState::instance.playerDataArray[playerID1].campground.xEntry;
        uint _p1_campfireY = DAT_GameState::instance.playerDataArray[playerID1].campground.yEntry;

        int const _canNavigate = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
            DAT_GameState::ptr)(playerID1, playerID2);

        uint _ghX;
        uint _ghY;

        if (_canNavigate == FALSE) {
            dword const _gatehouseTile
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findOwnedGatehouse,
                    DAT_PathFindingState::ptr)(playerID2, _p1_campfireX, _p1_campfireY);
            if (_gatehouseTile == 0) {
                DAT_GameState::instance.playerDataArray[playerID1].requestStateUnk = 0;
                return;
            }
            _ghY = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_gatehouseTile];
            _ghX = _gatehouseTile - DAT_ViewportRenderState::instance.translationMatrix[_ghY].addXgetTile;
        }

        int* _mappingPtr = &DAT_SkirmishDefinedData::instance.MaxAttackTribes1[0].tribeCount;

        for (int _index = 0; _index < 11; _index++) {
            int const _tribeTypeStart = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeType;
            int _tribeIndex = 0;
            int const _maxTribeCount = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeCount;

            for (; _tribeIndex < _maxTribeCount; _tribeIndex++) {

                int const _tribeID
                    = (int)DAT_GameState::instance.playerDataArray[playerID1].aiTribeIDs[_tribeTypeStart + _tribeIndex];

                if ((_tribeID != 0)
                    && (DAT_TribesState::instance.tribes[_tribeID].uid
                        == DAT_GameState::instance.playerDataArray[playerID1]
                            .aiTribeUIDs[_tribeIndex + _tribeTypeStart])) {

                    DAT_TribesState::instance.tribes[_tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                    int const _canNav2
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
                            DAT_GameState::ptr)(playerID1, playerID2);

                    if (_canNav2 != FALSE) {
                        if (_tribeTypeStart == 0xbe) {
                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                _tribeID, playerID2);
                        } else {
                            int const _hasHorses
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::selectionContainsHorses,
                                    DAT_TribesState::ptr)(_tribeID);
                            if (_hasHorses != FALSE) {
                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                    _tribeID, playerID2);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(
                                    _tribeID, playerID2);
                            }
                        }
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                            _tribeID, _ghX, _ghY, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                    }
                }
            }
        }
    }
}
}
