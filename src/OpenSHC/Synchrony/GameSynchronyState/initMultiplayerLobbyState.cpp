#include "../../Synchrony.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode2;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuModalType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    /*
      Full multiplayer session initialisation. Resets all synchrony counters, clears per-player hash   and lag arrays,
      resets teams, sets default lobby settings (speed 40, gold 0, popularity 100,   balance 3, intensity 1), resets
      game commands and UI modals, restores default unit colours,   initialises skirmish lobby data, queues
      GCT_ASK_FOR_SLOT_ASSIGNMENT, and switches to   MVT_LOBBY_MENU. Called when entering a new multiplayer or skirmish
      lobby.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048C230
    void GameSynchronyState::initMultiplayerLobbyState()
    {
        byte* pbVar1;
        int* piVar2;
        int* piVar3;
        char* pbVar4;
        int* piVar5;
        int (*local_14)[20];
        int (*local_10)[100][2];
        int (*local_c)[100][2];
        undefined2* local_8;
        int local_4;
        this->transmissionCounterUnk = 0;
        this->DAT_GameHalted = 0;
        this->lateCommandPenalty = 0;
        this->field78_0xbf0 = 0;
        this->DAT_HashCountdown = 0;
        this->quitGameVoteRelated = 0;
        this->shouldSendAnnouncementUnk = 0;
        this->connectionNoticeShown = 0;
        this->unknownIncrementBy40_01 = 1;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearChatEvents, this)();
        DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        this->counter = 0xffffffff;
        this->limit = 5;
        this->laggingPlayerIDUnk = 0;
        this->DAT_SomeTime = 0;
        this->flag_0x7aad8 = FALSE;
        if (this->isHost) {
            this->DAT_TwoIfNotHost = 2;
        }
        local_8 = (undefined2*)((int)this->finalResults.unusedUnk + 0x12);
        local_c = this->historicalLagInfoPerPlayer;
        local_14 = this->DAT_ReceivedAIVFileAvailabilityPerAIArray;
        pbVar4 = this->DAT_PlayerGroupArray;
        piVar5 = &this->connectionLagInfoArray[0].checkFor0;
        piVar3 = &this->HASH_PartialHashPerPlayer.player0.domain02;
        piVar2 = &this->matchTime;
        local_4 = 9;
        do {
            piVar2[0x23161] = 0;
            *piVar2 = -1;
            pbVar4[0x33] = 0;
            pbVar1 = (byte*)(piVar2 + -0x1e846);
            pbVar1[0] = 0;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            piVar2[0x23a97] = 0;
            piVar2[-0x1e861] = 0;
            piVar2[-0x1e858] = 0;
            piVar2[-0x1e84f] = 0;
            (*local_14)[0] = -1;
            piVar2[9] = 0;
            piVar2[0x12] = 0;
            piVar2[0x2314f] = 0;
            piVar2[0x23158] = 0;
            *pbVar4 = 0;
            piVar2[0x90] = FALSE;
            piVar2[0x87] = 0;
            pbVar4[0x12] = 0;
            ((HashContainerElement*)(piVar3 + -1))->domain01 = 0;
            *piVar3 = 0;
            piVar3[1] = 0;
            piVar3[2] = 0;
            piVar3[3] = 0;
            piVar3[4] = 0;
            local_10 = local_c;
            local_c = (int (*)[100][2])0x64;
            do {
                (*local_10)[0][0] = 0;
                local_10 = (int (*)[100][2])(*local_10 + 1);
                local_c = (int (*)[100][2])((int)local_c + -1);
            } while (local_c != (int (*)[100][2])0x0);
            local_14 = local_14 + 1;
            piVar5[-4] = 0;
            *piVar5 = 0;
            piVar5[1] = 0;
            piVar2[0x23a7c] = 1;
            piVar2[0x23c31] = 0;
            piVar2[0x23c8b] = 0;
            piVar2[0x23ccf] = 0;
            piVar2[0x23c94] = 0;
            piVar2[0x23cc6] = 0;
            piVar2[0x23c9d] = 0;
            piVar2[0x23ca6] = 0;
            piVar2[0x23caf] = 0;
            piVar2[0x23cb8] = 0;
            pbVar4[-0x2cc] = 0;
            piVar2[0x23cd8] = 0;
            piVar2[0x23ce1] = 0;
            piVar2[0x23cea] = 0;
            piVar2[0x23cf3] = 0;
            piVar2[0x23cfc] = 0;
            local_8[-9] = 0;
            *local_8 = 0;
            local_8 = local_8 + 1;
            piVar2[0x23d0e] = 0;
            piVar2[0x23d17] = 0;
            pbVar1 = (byte*)(piVar2 + 0x23d20);
            pbVar1[0] = 0;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            pbVar1 = (byte*)(piVar2 + 0x23d29);
            pbVar1[0] = 0;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            piVar2[0x23d58] = 0;
            piVar2 = piVar2 + 1;
            pbVar4 = pbVar4 + 1;
            piVar3 = piVar3 + 0xc;
            piVar5 = piVar5 + 9;
            local_4 = local_4 + -1;
            local_c = local_10;
        } while (local_4);
        this->skirmishUnknownSetting1[0] = 1;
        this->skirmishUnknownSetting1[1] = 1;
        this->skirmishUnknownSetting1[2] = 1;
        this->skirmishUnknownSetting1[3] = 1;
        this->skirmishStartGold = 0;
        this->skirmishDefaultPopularity = 100;
        this->skirmishGameSpeedLevel = 0x28;
        this->field235_0x1072e8 = -1;
        this->field236_0x1072ec = -1;
        this->skirmishCurrentAdvantageBalance = 3;
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
        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            UI::Enums::MMT_NONE, FALSE);
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
            UI::Enums::MMT_NONE, FALSE);
        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
            UI::Enums::MMT_NONE, FALSE);
        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::stopAllActiveSounds, DAT_SoundSystemState::ptr)();
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
        DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
        this->field225_0x106ee4 = 1;
        MACRO_CALL(Synchrony_Func::InitSkirmishLobbyData)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::setDirectPlaySessionDescription, this)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
            Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
        DAT_GameCore::instance.menuTabToSwitchTo.tabType = ((BuildingsAndStatusMenuTabType)0);
        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_LOBBY_MENU, 0);
    }

}
}
