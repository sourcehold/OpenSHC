#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D1700
        BOOLEnum StoreCurrentGameIntoTemporarySKMasterEntry(int score)
        {
            DAT_SkMasterDataEntry::instance.score = score;
            strcpy(DAT_SkMasterDataEntry::instance.mapName, DAT_GameSynchronyState::instance.mapName);
            DAT_SkMasterDataEntry::instance.skMasterScore = MACRO_CALL(UI::GreatestLord_Func::ComputeSkMasterScore)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID);
            int activePlayerCount = 0;
            for (int player = 1; player < 9; ++player) {
                if (DAT_GameSynchronyState::instance.finalResults.active[player] == 0) {
                    break;
                }
                ++activePlayerCount;
            }
            DAT_SkMasterDataEntry::instance.activePlayerCount = activePlayerCount;
            for (int player = 1; player < 9; ++player) {
                DAT_SkMasterDataEntry::instance.array1[player]
                    = DAT_GameState::instance.mapAndTime.playerGroupArray[player];
            }
            for (int player = 1; player < 9; ++player) {
                DAT_SkMasterDataEntry::instance.aiArray[player]
                    = DAT_GameSynchronyState::instance.currentAIArray[player];
            }
            for (int player = 1; player < 9; ++player) {
                DAT_SkMasterDataEntry::instance.aliveArray[player]
                    = DAT_GameState::instance.mapAndTime.playerIsAlive[player];
            }
            DAT_SkMasterDataEntry::instance.lordType = DAT_GameCore::instance.selectedLordTypeUnk;
            MACRO_CALL(Skirmish_Func::StoreLocalTime)();
            DAT_SkMasterDataEntry::instance.results = DAT_GameSynchronyState::instance.finalResults;
            return TRUE;
        }

    }
}
}
