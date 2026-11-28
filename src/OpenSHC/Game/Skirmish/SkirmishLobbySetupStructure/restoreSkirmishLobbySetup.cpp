#include "../../../Game.func.hpp"
#include "../SkirmishLobbySetupStructure.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/INT_00b960b0.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x00490060
        void SkirmishLobbySetupStructure::restoreSkirmishLobbySetup()
        {
            char cVar1;
            char* pcVar2;
            DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes = this->mapu4int2;
            pcVar2 = this->mapName;
            this->mbr_0x4 = DAT_GameState::instance.mapAndTime.skirmishFogOfWar;
            do {
                cVar1 = *pcVar2;
                pcVar2[0xc2ee7c] = cVar1;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[0] = this->roundTableOrderArray[0];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[0] = this->playerGroupArray[0];
            DAT_GameSynchronyState::instance.currentAIArray[0] = this->currentAIArray[0];
            DAT_GameSynchronyState::instance.aiVariationArray[0] = this->aiVariationArray[0];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[1] = this->roundTableOrderArray[1];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1] = this->playerGroupArray[1];
            DAT_GameSynchronyState::instance.currentAIArray[1] = this->currentAIArray[1];
            DAT_GameSynchronyState::instance.aiVariationArray[1] = this->aiVariationArray[1];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[2] = this->roundTableOrderArray[2];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2] = this->playerGroupArray[2];
            DAT_GameSynchronyState::instance.currentAIArray[2] = this->currentAIArray[2];
            DAT_GameSynchronyState::instance.aiVariationArray[2] = this->aiVariationArray[2];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[3] = this->roundTableOrderArray[3];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3] = this->playerGroupArray[3];
            DAT_GameSynchronyState::instance.currentAIArray[3] = this->currentAIArray[3];
            DAT_GameSynchronyState::instance.aiVariationArray[3] = this->aiVariationArray[3];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[4] = this->roundTableOrderArray[4];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4] = this->playerGroupArray[4];
            DAT_GameSynchronyState::instance.currentAIArray[4] = this->currentAIArray[4];
            DAT_GameSynchronyState::instance.aiVariationArray[4] = this->aiVariationArray[4];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[5] = this->roundTableOrderArray[5];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5] = this->playerGroupArray[5];
            DAT_GameSynchronyState::instance.currentAIArray[5] = this->currentAIArray[5];
            DAT_GameSynchronyState::instance.aiVariationArray[5] = this->aiVariationArray[5];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[6] = this->roundTableOrderArray[6];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6] = this->playerGroupArray[6];
            DAT_GameSynchronyState::instance.currentAIArray[6] = this->currentAIArray[6];
            DAT_GameSynchronyState::instance.aiVariationArray[6] = this->aiVariationArray[6];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[7] = this->roundTableOrderArray[7];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7] = this->playerGroupArray[7];
            DAT_GameSynchronyState::instance.currentAIArray[7] = this->currentAIArray[7];
            DAT_GameSynchronyState::instance.aiVariationArray[7] = this->aiVariationArray[7];
            DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[8] = this->roundTableOrderArray[8];
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8] = this->playerGroupArray[8];
            DAT_GameSynchronyState::instance.currentAIArray[8] = this->currentAIArray[8];
            DAT_GameSynchronyState::instance.aiVariationArray[8] = this->aiVariationArray[8];
            DAT_GameSynchronyState::instance.playerPositionsArray[0] = this->slot1Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[1] = this->slot2Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[2] = this->slot3Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[3] = this->slot4Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[4] = this->slot5Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[5] = this->slot6Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[6] = this->slot7Position;
            DAT_GameSynchronyState::instance.playerPositionsArray[7] = this->slot8Position;
            DAT_GameSynchronyState::instance.currentPlayerSlotID = this->currentPlayerSlotID;
            DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance = this->currentAdvantageBalance;
            DAT_GameSynchronyState::instance.skirmishGameIntensityType = this->currentAdvantageGroup;
            DAT_GameSynchronyState::instance.skirmishTechLevel = this->mbr_0x80;
            DAT_GameCore::instance.selectedLordTypes[0] = this->playerLordTypeArray[0];
            DAT_GameCore::instance.selectedLordTypes[1] = this->playerLordTypeArray[1];
            DAT_GameCore::instance.selectedLordTypes[2] = this->playerLordTypeArray[2];
            DAT_GameCore::instance.selectedLordTypes[3] = this->playerLordTypeArray[3];
            DAT_GameCore::instance.selectedLordTypes[4] = this->playerLordTypeArray[4];
            DAT_GameCore::instance.selectedLordTypes[5] = this->playerLordTypeArray[5];
            DAT_GameCore::instance.selectedLordTypes[6] = this->playerLordTypeArray[6];
            DAT_GameCore::instance.selectedLordTypes[7] = this->playerLordTypeArray[7];
            DAT_GameCore::instance.selectedLordTypes[8] = this->playerLordTypeArray[8];
            DAT_GameCore::instance.field152_0x2340 = this->mbr_0xf0;
            DAT_GameCore::instance.selectedLordTypeUnk = this->selectedLordType;
            DAT_GameSynchronyState::instance.skirmishDefaultPopularity = this->popularity;
            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = this->mapSelectionRelativeSelected;
            DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = this->mapSelectionScrollOffset;
            INT_00b960b0::instance = this->mapSelectionScrollOffset + this->mapSelectionRelativeSelected;
            DAT_GameSynchronyState::instance.lobbyMapSortOrder = this->mbr_0xfc;
            MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
        }

    }
}
}
