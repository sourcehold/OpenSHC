#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE5F0
    void AICState ::sendUnitsToPlayerIDsKeepIfPossible(int playerID1, short* playerID2)

    {

        BOOLEnum BVar1;

        dword _gatehouseTile;

        int _tribeID;

        int _counter;

        int* local_10;

        uint _ghY;

        uint _ghX;

        int _maxTribeCount;

        int _p1_keepCampfireX;

        int _aiTribeBehaviourTypeOffset;

        uint _p1_keepCampfireY;

        short* _playerID2;

        _playerID2 = playerID2;

        _p1_keepCampfireY = DAT_GameState::instance.playerDataArray[playerID1].campground.yEntry;

        _p1_keepCampfireX = DAT_GameState::instance.playerDataArray[playerID1].campground.xEntry;

        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
            DAT_GameState::ptr)(playerID1, (int)((int)(playerID2)));

        if (BVar1 == FALSE) {

            _gatehouseTile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findOwnedGatehouse,
                DAT_PathFindingState::ptr)((int)playerID2, (uint)((int)(_p1_keepCampfireX)), _p1_keepCampfireY);

            if (_gatehouseTile == 0) {

                DAT_GameState::instance.playerDataArray[playerID1].requestStateUnk = 0;

                return;
            }

            _ghY = (uint)DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_gatehouseTile];

            _ghX = _gatehouseTile - DAT_ViewportRenderState::instance.translationMatrix[_ghY].addXgetTile;
        }

        local_10 = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

        do {

            _maxTribeCount = *local_10;

            _aiTribeBehaviourTypeOffset = (*(int (*)[2])(local_10 + -1))[0];

            _counter = 0;

            if (0 < _maxTribeCount) {

                /*
                        fixme: reused parameter */

                playerID2 = DAT_GameState::instance.playerDataArray[playerID1].aiTribeIDs + _aiTribeBehaviourTypeOffset;

                do {

                    _tribeID = (int)*playerID2;

                    if ((_tribeID != 0)
                        && (DAT_TribesState::instance.tribes[_tribeID].uid
                            == DAT_GameState::instance.playerDataArray[playerID1]
                                .aiTribeUIDs[_counter + _aiTribeBehaviourTypeOffset])) {

                        DAT_TribesState::instance.tribes[_tribeID].unitStance
                            = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
                            DAT_GameState::ptr)(playerID1, (int)((int)(_playerID2)));

                        if (BVar1 == FALSE) {

                            /*
                                          send to enemy gate house */

                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                _tribeID, _ghX, _ghY, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);

                        }

                        else if (_aiTribeBehaviourTypeOffset == 0xbe) {

                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                _tribeID, (int)((int)(_playerID2)));

                        }

                        else {

                            BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::selectionContainsHorses,
                                DAT_TribesState::ptr)(_tribeID);

                            if (BVar1 == FALSE) {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(
                                    _tribeID, (int)((int)(_playerID2)));

                            }

                            else {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                    _tribeID, (int)((int)(_playerID2)));
                            }
                        }
                    }

                    playerID2 = playerID2 + 1;

                    _counter = _counter + 1;

                } while (_counter < _maxTribeCount);
            }

            local_10 = local_10 + 2;

        } while ((int)local_10 < 0xb42a2c);

        return;
    }

}
}
