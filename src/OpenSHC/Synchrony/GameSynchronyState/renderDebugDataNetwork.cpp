#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00488540
    void GameSynchronyState::renderDebugDataNetwork(int x, int y, int width, int height)
    {
        int const left = x + 2;
        // "Packets in: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Packets_in__005a7488, left, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->packetsReceived, left, y, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "Chores used: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Chores_used__005a7478, left + 10, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getGameCommandArrayIndex, this)(), left + 10, y,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // " Adv: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Adv__005a7470, left + 20, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->DAT_LagIndicatorPerPlayer[1], left + 20, y, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
            0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->DAT_LagIndicatorPerPlayer[2], left + 25, y, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
            0);
        int const column3 = left + 30;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->DAT_LagIndicatorPerPlayer[3], column3, y, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        int const column4 = left + 35;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->DAT_LagIndicatorPerPlayer[4], column4, y, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // One counter for the three player rows: a counter per loop swaps two stack slots.
        int player;
        // "Timings "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Timings_005a7464, left, y + 14, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        for (player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] != -1) {
                // " p"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_p_005a7460, left, y + 14, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    player, left, y + 14, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                // ":"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s___005a745c, left, y + 14, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->matchTimes[player], left, y + 14, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            }
        }
        uint relativeTimeColor;
        if (this->relativeTickTime < 0) {
            relativeTimeColor = Rendering::Colors::COL_0000FF;
        } else {
            relativeTimeColor = Rendering::Colors::COL_0080FF;
        }
        // "Relative time: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Relative_time__005a744c, left, y + 28, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->relativeTickTime, left, y + 28, Text::TTA_LEFT, relativeTimeColor, 18, TRUE, 0);
        // " Logical speed: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Logical_speed__005a7438, left + 150, y + 28, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameTicksThisLoop, left + 150, y + 28, Text::TTA_LEFT, Rendering::Colors::COL_0080FF,
            18, TRUE, 0);
        // Each hash is shown by its low 12 bits.
        // "Crcs "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Crcs_005a7430, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        for (player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] != -1) {
                // " p"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_p_005a7460, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    player, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                // ":"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s___005a745c, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->HASH_HashTotal[player] & 0xfff, left, y + 42, Text::TTA_LEFT, Rendering::Colors::COL_0080FF,
                    18, TRUE, 0);
            }
        }
        // "Crc times "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Crc_times_005a7424, left, y + 56, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        for (player = 1; player < 9; ++player) {
            if (this->currentPlayerFullIDArray[player] != -1) {
                // " p"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_p_005a7460, left, y + 56, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    player, left, y + 56, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                // ":"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s___005a745c, left, y + 56, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    this->DAT_PlayerMatchTimes[player], left, y + 56, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18,
                    TRUE, 0);
            }
        }
        if (this->syncStatus != 0) {
            // "GAME SPLINTERED - Resyncing"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_GAME_SPLINTERED___Resyncing_005a7408, left, y + 70, Text::TTA_LEFT, Rendering::Colors::COL_0000FF, 17,
                FALSE, 0);
        } else if (this->DAT_GameHalted != 0) {
            // "GAME SPLINTERED "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_GAME_SPLINTERED_005a73f4, left, y + 70, Text::TTA_LEFT, Rendering::Colors::COL_0000FF, 17, FALSE, 0);
        } else {
            // "Game in sync"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Game_in_sync_005a73e4, left, y + 70, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 17, FALSE, 0);
        }
        // The local player's hash per domain, again by its low 12 bits.
        // "CHI:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_CHI__005a73dc, left, y + 98, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[0] & 0xfff, left, y + 98,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  STR:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_STR__005a73d4, left, y + 98, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[1] & 0xfff, left, y + 98,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  VEG:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_VEG__005a73cc, left, y + 98, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[2] & 0xfff, left, y + 98,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  TRI:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_TRI__005a73c4, left, y + 98, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[3] & 0xfff, left, y + 98,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  PLA:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_PLA__005a73bc, left, y + 98, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[4] & 0xfff, left, y + 98,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "GAM:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_GAM__005a73b4, left, y + 98, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[5] & 0xfff, left, y + 98,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  LAY:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_LAY__005a73ac, left, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[6] & 0xfff, left, y + 112,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  FLY:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_FLY__005a73a4, left, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[7] & 0xfff, left, y + 112,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  MOAT:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_MOAT__005a739c, left, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[8] & 0xfff, left, y + 112,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  TELE:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_TELE__005a7394, left, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[9] & 0xfff, left, y + 112,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  PIDI:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_PIDI__005a738c, left, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[10] & 0xfff, left, y + 112,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "  ZONE:"
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_ZONE__005a7384, left, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 19, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->HASH_PartialHashPerPlayer.player[this->currentPlayerSlotID].domain[11] & 0xfff, left, y + 112,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 19, TRUE, 0);
        // "Chimps: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Chimps__005a7378, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_UnitsState::instance.unitCount, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
            0);
        // "Structs: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Structs__005a736c, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.structCount, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18,
            TRUE, 0);
        // "id_count: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_id_count__005a7360, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.uniqueGameObjectTracker, left, y + 126, Text::TTA_LEFT,
            Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "random no: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_random_no__005a7354, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            SEC_RNG::instance.currentNumber2, left, y + 126, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
            0);
        // "chore_latency: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_chore_latency__005a7344, left, y + 140, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->commandDelay, left, y + 140, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "pending_chores: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_pending_chores__005a7330, left, y + 140, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getPendingGameCommandsCount, this)(), left, y + 140,
            Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "cl time_diff: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_cl_time_diff__005a7320, left, y + 154, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->clTimeDiff, left, y + 154, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "Clans: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Clans__005a7318, left, y + 154, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_TribesState::instance.clans, left, y + 154, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "Battle Level: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Battle_Level__005a7308, left, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.battleLevel, left, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
            0);
        // ", "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s___005a7304, left, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.battleLevel2, left, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE,
            0);
        // The game mode is read through the global instance, as in the original.
        // "Multi Op: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_Multi_Op__005a72f8, column3, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameSynchronyState::instance.currentGameMode, column3, y + 168, Text::TTA_LEFT,
            Rendering::Colors::COL_0080FF, 18, TRUE, 0);
        // "GT: "
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_GT__005a72f0, column4, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameCore::instance.gameMode_2, column4, y + 168, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18,
            TRUE, 0);
    }

}
}
