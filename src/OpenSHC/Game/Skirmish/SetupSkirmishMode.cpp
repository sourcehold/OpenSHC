#include "../../Game.func.hpp"
#include "../Skirmish.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Game {

    using Commands::GameCommandType;
    using Game::GameMode;
    using Game::GameMode2;
    using Game::TrailType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004C68D0
    void Skirmish::SetupSkirmishMode(int skirmishTrailMission)
    {
        char cVar1;
        int* piVar2;
        char* pcVar3;
        int iVar4;
        int iVar5;
        char (*pacVar6)[250];
        CampaignTrailMission* pCVar7;
        dword _startDateInMonths;
        pCVar7 = DAT_SkirmishDefinedData::instance.SkirmishTrailMissions + skirmishTrailMission;
        if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
            pCVar7 = DAT_SkirmishDefinedData::instance.ExtremeTrailMissions + skirmishTrailMission;
        } else if (DAT_GameCore::instance.currentTrailType == Game::TT_WARCHEST) {
            pCVar7 = DAT_SkirmishDefinedData::instance.WarchestTrailMissions + skirmishTrailMission;
        }
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::setupSkirmishLobby, DAT_GameSynchronyState::ptr)();
        DAT_GameSynchronyState::instance.isHost = TRUE;
        DAT_GameSynchronyState::instance.currentGameMode = Game::GM_SKIRMISH_SINGLE_PLAYER;
        DAT_GameSynchronyState::instance.DPLAYX_ReceivedPlayerID = 1;
        DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
        MACRO_CALL(OS_Func::_memset)(
            DAT_GameSynchronyState::instance.DAT_PlayerNames, 0, (size_t)((int)(2250)));
        piVar2 = DAT_GameSynchronyState::instance.currentAIArray;
        do {
            piVar2[-0x1b] = -1;
            *piVar2 = 0;
            piVar2[9] = -1;
            piVar2 = piVar2 + 1;
        } while ((int)piVar2 < 0x191dea0);
        pcVar3 = MACRO_CALL_MEMBER(
            Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
        pacVar6 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
        do {
            cVar1 = *pcVar3;
            (*pacVar6)[0] = cVar1;
            pcVar3 = pcVar3 + 1;
            pacVar6 = (char (*)[250])(*pacVar6 + 1);
        } while (cVar1 != '\0');
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[0] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[1] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[2] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[3] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[4] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[5] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[6] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[7] = 1;
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[8] = 1;
        DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
        DAT_GameCore::instance.mapU4Int0 = 0;
        if (1 < pCVar7->numberOfPlayers) {
            piVar2 = &pCVar7->player2AI;
            iVar4 = 1;
            do {
                iVar5 = iVar4 + 1;
                DAT_GameSynchronyState::instance.currentAIArray[iVar4 + 1] = *piVar2;
                MACRO_CALL(Synchrony_Func::ResetAiVariationArrayValue)(iVar5);
                piVar2 = piVar2 + 1;
                iVar4 = iVar5;
            } while (iVar5 < pCVar7->numberOfPlayers);
        }
        DAT_GameSynchronyState::instance.playerPositionsArray[0] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[1] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[2] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[3] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[4] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[5] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[6] = -10;
        DAT_GameSynchronyState::instance.playerPositionsArray[7] = -10;
        iVar4 = 0;
        piVar2 = &pCVar7->position1;
        do {
            if (*piVar2 != 0) {
                DAT_GameSynchronyState::instance.playerPositionsArray[*piVar2 - 1] = (char)iVar4;
            }
            iVar4 = iVar4 + 1;
            piVar2 = piVar2 + 1;
        } while (iVar4 < 8);
        iVar4 = pCVar7->numberOfPlayers;
        iVar5 = 0;
        piVar2 = &pCVar7->team1;
        do {
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar5 + 1] = (byte)*piVar2;
            if (iVar4 <= iVar5) {
                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar5 + 1] = 0xff;
            }
            iVar5 = iVar5 + 1;
            piVar2 = piVar2 + 1;
        } while (iVar5 < 8);
        pcVar3 = (char *)(pCVar7->mapNameAddress);
        iVar4 = 0x1a22f9c - (int)pcVar3;
        do {
            cVar1 = *pcVar3;
            pcVar3[iVar4] = cVar1;
            pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = pCVar7->fairness;
        DAT_GameSynchronyState::instance.skirmishGameIntensityType = pCVar7->startLevels;
        piVar2 = &pCVar7->aiv1;
        DAT_GameCore::instance.isSkirmishTrail = TRUE;
        if (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
            DAT_GameCore::instance.extremeTrailProgress = skirmishTrailMission;
            MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)((int)piVar2);
            _startDateInMonths
                = DAT_GameCore::instance.extremeTrailStartDatesInMonths[DAT_GameCore::instance.extremeTrailProgress];
            DAT_GameCore::instance.extremeTrailStartDateMonths = _startDateInMonths;
        } else if (DAT_GameCore::instance.currentTrailType == Game::TT_WARCHEST) {
            DAT_GameCore::instance.warchestTrailProgress = skirmishTrailMission;
            MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)((int)piVar2);
            _startDateInMonths
                = DAT_GameCore::instance.warchestTrailStartDatesInMonths[DAT_GameCore::instance.warchestTrailProgress];
            DAT_GameCore::instance.warchestTrailStartDateMonths = _startDateInMonths;
        } else {
            DAT_GameCore::instance.skirmishTrailProgress = skirmishTrailMission;
            MACRO_CALL(UI::Actions_Func::LaunchSkirmishGame)((int)piVar2);
            _startDateInMonths
                = DAT_GameCore::instance.skirmishTrailStartDateInMonths[DAT_GameCore::instance.skirmishTrailProgress];
            DAT_GameCore::instance.skirmishTrailStartDateMonths = _startDateInMonths;
        }
        DAT_GameState::instance.mapAndTime.year = (int)_startDateInMonths / 0xc;
        DAT_GameState::instance.mapAndTime.month = (int)_startDateInMonths % 0xc;
        DAT_GameSynchronyState::instance.finalResults.yearStart = (int)_startDateInMonths / 0xc;
        DAT_GameSynchronyState::instance.finalResults.monthStart = (int)_startDateInMonths % 0xc;
    }

}
}
