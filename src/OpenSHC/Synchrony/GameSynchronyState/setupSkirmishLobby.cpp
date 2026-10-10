#include "../../Synchrony.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/BitMapState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BitMapState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using Game::GameMode2;
    using UI::Enums::DisplayElementID;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487650
    void GameSynchronyState::setupSkirmishLobby()
    {
        byte* pbVar1;
        int iVar2;
        int* piVar3;
        int* piVar4;
        char* local_1c;
        int (*local_18)[20];
        char (*local_14)[250];
        undefined2* local_10;
        int (*local_c)[100][2];
        int* local_8;
        int local_4;
        this->currentGameMode = Game::GM_SOLITARY;
        this->transmissionCounterUnk = 0;
        this->DAT_GameHalted = 0;
        this->lateCommandPenalty = 0;
        this->field78_0xbf0 = 0;
        this->DAT_HashCountdown = 0;
        this->quitGameVoteRelated = 0;
        this->shouldSendAnnouncementUnk = 0;
        this->connectionNoticeShown = 0;
        this->DAT_HostPlayerSlotID = 0;
        this->DPLAYX_ReceivedPlayerID = 0;
        this->DPLAY_ToID = 0;
        this->DPLAYX_PlayerHandle = 0xffffffff;
        this->currentPlayerSlotID = 0;
        this->DAT_HostAnnounced = 0;
        this->field57_0x79c[0] = 0;
        this->field57_0x79c[1] = 0;
        this->field57_0x79c[2] = 0;
        this->field57_0x79c[3] = 0;
        this->unknownIncrementBy40_01 = 1;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearChatEvents, this)();
        DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        this->counter = 0xffffffff;
        this->limit = 5;
        this->laggingPlayerIDUnk = 0;
        this->DAT_SomeTime = 0;
        this->flag_0x7aad8 = FALSE;
        this->DAT_TwoIfNotHost = 2;
        MACRO_CALL_MEMBER(IO::BitMapState_Func::setBMPFacesToMagenta, DAT_BitMapState::ptr)();
        local_1c = this->DAT_PlayerGroupArray;
        local_10 = (undefined2*)((int)this->finalResults.unusedUnk + 0x12);
        local_8 = &this->connectionLagInfoArray[0].checkFor0;
        local_c = this->historicalLagInfoPerPlayer;
        piVar3 = &this->HASH_PartialHashPerPlayer.player0.domain02;
        local_14 = this->DAT_PlayerNames;
        local_18 = this->DAT_ReceivedAIVFileAvailabilityPerAIArray;
        piVar4 = this->currentAIArray;
        local_4 = 9;
        do {
            piVar4[-0x1b] = -1;
            piVar4[0x1e858] = -1;
            *piVar4 = 0;
            piVar4[9] = 0;
            piVar4[0x419b9] = 0;
            local_1c[0x33] = 0;
            pbVar1 = (byte*)(piVar4 + 0x12);
            pbVar1[0] = 0;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            piVar4[0x422ef] = 0;
            piVar4[-9] = 0;
            (*local_18)[0] = -1;
            piVar4[0x1e861] = 0;
            piVar4[0x1e86a] = 0;
            MACRO_CALL(OS_Func::_memset)(local_14, 0, 0xfa);
            piVar4[0x419a7] = 0;
            piVar4[0x419b0] = 0;
            *local_1c = 0;
            piVar4[0x1e8e8] = FALSE;
            piVar4[0x1e8df] = 0;
            local_1c[0x12] = 0;
            ((HashContainerElement*)(piVar3 + -1))->domain01 = 0;
            *piVar3 = 0;
            piVar3[1] = 0;
            piVar3[2] = 0;
            piVar3[3] = 0;
            piVar3[4] = 0;
            iVar2 = 100;
            do {
                (*local_c)[0][0] = 0;
                local_c = (int (*)[100][2])(*local_c + 1);
                iVar2 = iVar2 + -1;
            } while (iVar2);
            local_18 = local_18 + 1;
            local_14 = local_14 + 1;
            local_8[-4] = 0;
            *local_8 = 0;
            local_8[1] = 0;
            piVar4[0x422d4] = 1;
            piVar4[0x42489] = 0;
            piVar4[0x424e3] = 0;
            piVar4[0x42527] = 0;
            piVar4[0x424ec] = 0;
            piVar4[0x4251e] = 0;
            piVar4[0x424f5] = 0;
            piVar4[0x424fe] = 0;
            piVar4[0x42507] = 0;
            piVar4[0x42510] = 0;
            local_1c[-0x2cc] = 0;
            piVar4[0x42530] = 0;
            piVar4[0x42539] = 0;
            piVar4[0x42542] = 0;
            piVar4[0x4254b] = 0;
            piVar4[0x42554] = 0;
            local_10[-9] = 0;
            *local_10 = 0;
            piVar4[0x42566] = 0;
            piVar4[0x4256f] = 0;
            pbVar1 = (byte*)(piVar4 + 0x42578);
            pbVar1[0] = 0;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            pbVar1 = (byte*)(piVar4 + 0x42581);
            pbVar1[0] = 0;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            piVar4[0x425b0] = 0;
            local_10 = local_10 + 1;
            local_8 = local_8 + 9;
            piVar4 = piVar4 + 1;
            piVar3 = piVar3 + 0xc;
            local_4 = local_4 + -1;
            local_1c = local_1c + 1;
        } while (local_4);
        this->skirmishUnknownSetting1[0] = 1;
        this->skirmishUnknownSetting1[1] = 1;
        this->skirmishUnknownSetting1[2] = 1;
        this->skirmishUnknownSetting1[3] = 1;
        this->skirmishStartGold = 0;
        this->skirmishDefaultPopularity = 100;
        this->skirmishGameSpeedLevel = 0x28;
        this->skirmishCurrentAdvantageBalance = 3;
        this->field235_0x1072e8 = -1;
        this->field236_0x1072ec = -1;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[0] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[1] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[2] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[3] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[4] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[5] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[6] = 0;
        DAT_TextureRenderCoreObject::instance.unknownPlayerDependentRenderValue[7] = 0;
        this->skirmishTechLevel = 4;
        this->skirmishGameIntensityType = 1;
        this->skirmishGameIntensityType2 = 1;
        this->skirmishWinCondition = 0;
        this->skirmishTroopsCostGold = 1;
        this->lobbyMapSortOrder = 6;
        if (this->skirmishAutoSaveEveryMinutes && this->skirmishAutoSaveEveryMinutes != 5
            && this->skirmishAutoSaveEveryMinutes != 10 && this->skirmishAutoSaveEveryMinutes != 0x14) {
            this->skirmishAutoSaveEveryMinutes = 10;
        }
        this->saveRelated = 0;
        this->lastAutoSaveTime = 0;
        this->commandDelay = 0x23;
        DAT_GameState::instance.mapAndTime.gameOver = FALSE;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::resetGameCommands, this)();
        DAT_GameCore::instance.mapTimeInTicks = 0;
        this->syncStatus = 0;
        this->flag_0xbec = 0;
        this->skirmishStrongWalls = 0;
        this->skirmishAlliances = 0;
        this->skirmishNoCowThrowing = 0;
        this->skirmishNoDogs = 0;
        this->skirmishNoRushSetting = 0;
        this->skirmishExtremeMode = 1;
        this->skirmishExtremeMode2 = 0;
        this->DAT_MapFileReceivingState = 0;
        DAT_GameState::instance.mapAndTime.skirmishFogOfWar = 0;
        MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
            UI::Enums::DEID_WIN_DEFEAT_WINDOW, 0);
    }

}
}
