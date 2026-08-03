#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/AttackInfoSubElement.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::AttackInfoSubElement;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE110
    void AICState ::recomputeAttackAIZone()

    {

        int* _pBorderDistance;

        int _playerID;

        AttackInfoSubElement* _pi;

        int _fullID;

        _playerID = 1;

        _pi = DAT_TroopValueState::instance.attackInfo.playerInfo;

        _pBorderDistance = &DAT_GameState::instance.playerDataArray[1].unknownPathBorderDistanceRelated;

        do {

            _fullID = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID];

            _pi->currentPlayerID_OR_attackedPlayerID_OR_one = _playerID;

            if ((_fullID != -1) || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {

                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    80400, '\0', (void*)((int)(DAT_TileMapState::instance.AIZoneLayer)));

                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
                    DAT_PathFindingState::ptr)(_playerID, 2);

                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
                    DAT_PathFindingState::ptr)(252, 0, 1, _playerID);

                *_pBorderDistance = DAT_PathFindingState::instance.distance;

                _pi->currentPlayerID_OR_attackedPlayerID_OR_one = 1;
            }

            _playerID = _playerID + 1;

            _pBorderDistance = _pBorderDistance + 0xe7d;

            _pi = _pi + 1;

        } while (_playerID < 9);

        return;
    }

}
}
