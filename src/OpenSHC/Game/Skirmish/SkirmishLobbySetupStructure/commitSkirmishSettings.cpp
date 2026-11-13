#include "../SkirmishLobbySetupStructure.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x00486C40
        void SkirmishLobbySetupStructure::commitSkirmishSettings()
        {
            this->mapu4int2 = DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes;
            this->mbr_0x4 = DAT_GameState::instance.mapAndTime.skirmishFogOfWar;
            strcpy(this->mapName, DAT_GameSynchronyState::instance.mapName);
            for (int player = 0; player < 9; ++player) {
                this->roundTableOrderArray[player] = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[player];
                this->playerGroupArray[player] = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[player];
                this->currentAIArray[player] = DAT_GameSynchronyState::instance.currentAIArray[player];
                this->aiVariationArray[player] = DAT_GameSynchronyState::instance.aiVariationArray[player];
            }
            this->slot1Position = DAT_GameSynchronyState::instance.playerPositionsArray[0];
            this->slot2Position = DAT_GameSynchronyState::instance.playerPositionsArray[1];
            this->slot3Position = DAT_GameSynchronyState::instance.playerPositionsArray[2];
            this->slot4Position = DAT_GameSynchronyState::instance.playerPositionsArray[3];
            this->slot5Position = DAT_GameSynchronyState::instance.playerPositionsArray[4];
            this->slot6Position = DAT_GameSynchronyState::instance.playerPositionsArray[5];
            this->slot7Position = DAT_GameSynchronyState::instance.playerPositionsArray[6];
            this->slot8Position = DAT_GameSynchronyState::instance.playerPositionsArray[7];
            this->currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            this->currentAdvantageBalance = DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance;
            this->currentAdvantageGroup = DAT_GameSynchronyState::instance.skirmishGameIntensityType;
            this->mbr_0x80 = DAT_GameSynchronyState::instance.skirmishTechLevel;
            for (int player = 0; player < 9; ++player) {
                this->playerLordTypeArray[player] = DAT_GameCore::instance.selectedLordTypes[player];
            }
            this->mbr_0xf0 = DAT_GameCore::instance.field_0x2340;
            this->selectedLordType = DAT_GameCore::instance.selectedLordTypeUnk;
            this->popularity = DAT_GameSynchronyState::instance.skirmishDefaultPopularity;
            this->mapSelectionRelativeSelected = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
            this->mapSelectionScrollOffset = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
            this->mbr_0xfc = DAT_GameSynchronyState::instance.lobbyMapSortOrder;
        }

    }
}
}
