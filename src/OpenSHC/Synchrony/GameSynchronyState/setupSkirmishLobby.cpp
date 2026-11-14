#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/BitMapState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_BitMapState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00487650
    void GameSynchronyState::setupSkirmishLobby()
    {
        this->currentGameMode = Game::GM_SOLITARY;
        this->transmissionCounterUnk = 0;
        this->DAT_GameHalted = 0;
        this->lateCommandPenalty = 0;
        this->field_0xbf0 = 0;
        this->DAT_HashCountdown = 0;
        this->quitGameVoteRelated = 0;
        this->shouldSendAnnouncementUnk = 0;
        this->connectionNoticeShown = 0;
        this->DAT_HostPlayerSlotID = 0;
        this->DPLAYX_ReceivedPlayerID = 0;
        this->DPLAY_ToID = 0;
        this->DPLAYX_PlayerHandle = DPID_UNKNOWN;
        this->currentPlayerSlotID = 0;
        this->DAT_HostAnnounced = 0;
        for (int i = 0; i < 4; ++i) {
            this->field_0x79c[i] = 0;
        }
        this->unknownIncrementBy40_01 = 1;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::clearChatEvents, this)();
        DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        this->counter = -1;
        this->limit = 5;
        this->laggingPlayerIDUnk = 0;
        this->DAT_SomeTime = 0;
        this->flag_0x7aad8 = FALSE;
        this->DAT_TwoIfNotHost = 2;
        MACRO_CALL_MEMBER(IO::BitMapState_Func::setBMPFacesToMagenta, DAT_BitMapState::ptr)();
        for (int player = 0; player < countof(this->currentPlayerFullIDArray); ++player) {
            this->currentPlayerFullIDArray[player] = -1;
            this->currentAIArray[player] = 0;
            this->matchTimes[player] = -1;
            this->aiVariationArray[player] = 0;
            this->unknownPlayerInfo_03[player] = 0;
            this->field_0x109e80[player] = 0;
            this->field_0x75c[player] = 0;
            this->unknownPlayerInfoArray_01[player] = 0;
            this->somePlayerRelatedArray[player] = 0;
            this->DAT_ReceivedAIVFileAvailabilityPerAIArray[player][0] = -1;
            this->HASH_HashTotal[player] = 0;
            this->DAT_PlayerMatchTimes[player] = 0;
            MACRO_CALL(OS_Func::_memset)(this->DAT_PlayerNames[player], 0, sizeof(this->DAT_PlayerNames[player]));
            this->DAT_PlayerSlotArraySomeValue[player] = 0;
            this->unknownPlayerInfo_01[player] = 0;
            this->DAT_PlayerGroupArray[player] = 0;
            this->isIncludedPlayer[player] = FALSE;
            this->DAT_MultiplayerGameVersions[player] = 0;
            this->slotActionPending[player] = 0;
            // Six stores rather than a loop over the domains, which would move the loop's base pointer.
            this->HASH_PartialHashPerPlayer.player[player].domain[0] = 0;
            this->HASH_PartialHashPerPlayer.player[player].domain[1] = 0;
            this->HASH_PartialHashPerPlayer.player[player].domain[2] = 0;
            this->HASH_PartialHashPerPlayer.player[player].domain[3] = 0;
            this->HASH_PartialHashPerPlayer.player[player].domain[4] = 0;
            this->HASH_PartialHashPerPlayer.player[player].domain[5] = 0;
            for (int entry = 0; entry < countof(this->historicalLagInfoPerPlayer[0]); ++entry) {
                this->historicalLagInfoPerPlayer[player][entry][0] = 0;
            }
            this->connectionLagInfoArray[player].average1 = 0;
            this->connectionLagInfoArray[player].checkFor0 = 0;
            this->connectionLagInfoArray[player].time = 0;
            this->DAT_ChatMessageReceiverArray[player] = 1;
            this->finalResults.finalTimeAlive[player] = 0;
            this->finalResults.finalBuildingsBurned[player] = 0;
            this->finalResults.finalBuidingsDestroyed[player] = 0;
            this->finalResults.finalFoodProduced[player] = 0;
            this->finalResults.finalWeaponsProduced[player] = 0;
            this->finalResults.finalIronProduced[player] = 0;
            this->finalResults.finalStoneProduced[player] = 0;
            this->finalResults.finalWoodProduced[player] = 0;
            this->finalResults.finalPitchProduced[player] = 0;
            this->finalResults.finalKilledLords[player] = 0;
            this->finalResults.finalTroopsKilledWeighted[player] = 0;
            this->finalResults.finalBuildingsDestroyedWeighted[player] = 0;
            this->finalResults.finalTroopsProduced[player] = 0;
            this->finalResults.finalGoodsRecieved[player] = 0;
            this->finalResults.finalGoodsSent[player] = 0;
            this->finalResults.unknownShortArray1[player] = 0;
            this->finalResults.unknownShortArray2[player] = 0;
            this->finalResults.finalDateOfDeathInMonths[player] = 0;
            this->finalResults.tail.tail2.field_0x0[player] = 0;
            this->finalResults.tail.tail2.field_0x24[player] = 0;
            this->finalResults.tail.tail2.field_0x48[player] = 0;
            this->mapSendingFileHandles[player] = NULL;
        }
        for (int i = 0; i < countof(this->skirmishUnknownSetting1); ++i) {
            this->skirmishUnknownSetting1[i] = 1;
        }
        this->skirmishStartGold = 0;
        this->skirmishDefaultPopularity = 100;
        this->skirmishGameSpeedLevel = 40;
        this->skirmishCurrentAdvantageBalance = 3;
        this->field_0x1072e8 = -1;
        this->field_0x1072ec = -1;
        // The faces of player slots 1 to 8
        for (int slot = 1; slot <= 8; ++slot) {
            DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[slot + 19] = 0;
        }
        this->skirmishTechLevel = 4;
        this->skirmishGameIntensityType = 1;
        this->skirmishGameIntensityType2 = 1;
        this->skirmishWinCondition = 0;
        this->skirmishTroopsCostGold = 1;
        this->lobbyMapSortOrder = 6;
        // Only autosave intervals of 5, 10 and 20 minutes (or none) are kept.
        if (this->skirmishAutoSaveEveryMinutes != 0 && this->skirmishAutoSaveEveryMinutes != 5
            && this->skirmishAutoSaveEveryMinutes != 10 && this->skirmishAutoSaveEveryMinutes != 20) {
            this->skirmishAutoSaveEveryMinutes = 10;
        }
        this->saveRelated = 0;
        this->lastAutoSaveTime = 0;
        this->commandDelay = 35;
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
