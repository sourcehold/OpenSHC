#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE040
    void AICState ::recomputeAIPathCostToAttackedKeep(int playerID, int useBorderDistance)

    {

        BOOLEnum BVar1;

        uint _borderDistance;

        bool _cannotNavigateToKeep;

        int _attackedPlayerID;

        int _bd;

        ushort _keepArea;

        _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;

        _keepArea = DAT_TileMapState::instance
                        .PathConnectionLayer[DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry];

        _bd = DAT_GameState::instance.playerDataArray[_attackedPlayerID].unknownPathBorderDistanceRelated;

        if (_bd < 120) {

            _borderDistance = ((_bd < 90) - 1 & 20) + 50;

        }

        else {

            _borderDistance = 98;
        }

        if (useBorderDistance == 0) {

            _borderDistance = 0;
        }

        *(int*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + playerID * 0x177bc + -0x10)
            = _attackedPlayerID;

        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemoryWithByteValue, DAT_LowLevelMemory::ptr)(
            80400, '\0', (void*)((int)(DAT_TileMapState::instance.AIZoneLayer)));

        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
            DAT_GameState::ptr)(playerID, DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID);

        _cannotNavigateToKeep = BVar1 == FALSE;

        if (_cannotNavigateToKeep) {

            _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;

        }

        else {

            _attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID;
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeAIZoneLayer,
            DAT_PathFindingState::ptr)(_attackedPlayerID, (int)((int)((uint)!_cannotNavigateToKeep)));

        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkLayerAndAIPathCostLayer,
            DAT_PathFindingState::ptr)(110, _borderDistance, (dword)((int)((int)(short)_keepArea)), playerID);

        return;
    }

}
}
