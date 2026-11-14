#include "../Synchrony.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_00b960f8.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/INT_00b95950.hpp"
#include "OpenSHC/Globals/INT_00b95958.hpp"
#include "OpenSHC/Globals/INT_00b95960.hpp"
#include "OpenSHC/Globals/INT_00b95ab8.hpp"
#include "OpenSHC/Globals/INT_00b960b0.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004274F0
void Synchrony::InitSkirmishLobbyData()
{
    MACRO_CALL_MEMBER(AI::AIVState_Func::hostChecksLobbyAIVAvailability, DAT_AIVState::ptr)();
    DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
    DAT_GameSynchronyState::instance.mapExistenceAckCountdown = 0;
    DAT_GameCore::instance.mapU4Int0 = 0;
    MACRO_CALL_MEMBER(Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
    MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
    DAT_GameSynchronyState::instance.mapName[0] = '\0';
    DAT_GameCore::instance.mapDescription[0] = '\0';
    DAT_GameCore::instance.mapDescUseStringTableIndex = 0;
    memset(DAT_MinimapViewState::instance.loadedMiniMap, 0, sizeof(DAT_MinimapViewState::instance.loadedMiniMap));
    DAT_ButtonBackgroundBlendStrength::instance = 32;
    DAT_00b960dc::instance = -3;
    DWORD_00b95b1c::instance = timeGetTime();
    memset(DAT_GameSynchronyState::instance.playerPositionsArray, -10,
        sizeof(DAT_GameSynchronyState::instance.playerPositionsArray));
    INT_00b95960::instance = -1;
    INT_00b95950::instance = -1;
    INT_00b960b0::instance = -1;
    DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
    DAT_GameSynchronyState::instance.lobbyMapSortOrder = 6;
    INT_00b95ab8::instance = 0;
    for (int i = 0; i < 20; ++i) {
        DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[i]
            = DAT_RenderingDefinedData::instance
                  .SkirmishIntensityRelatedArray[0][DAT_GameSynchronyState::instance.skirmishTechLevel][i];
    }
    for (int i = 0; i < 10; ++i) {
        DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[i]
            = DAT_RenderingDefinedData::instance
                  .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][i];
    }
    DAT_GameSynchronyState::instance.skirmishStartGold
        = DAT_RenderingDefinedData::instance.StartGold[DAT_GameSynchronyState::instance.skirmishTechLevel / 2];
    for (int i = 0; i < 9; ++i) {
        DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[i] = 1;
    }
    if (DAT_GameSynchronyState::instance.isHost) {
        memset(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray, -1,
            sizeof(DAT_GameSynchronyState::instance.DAT_PlayerGroupArray));
        MACRO_CALL_MEMBER(GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
    }
    INT_00b95958::instance = 0;
    DAT_00b960f8::instance = 0;
}

}
