#include "../AICState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/AI/AIC/AICSpecification.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AIStrengthType.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AICState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1320
    void AICState::renderDebugDataAiInfo(int x, int y, int width, int height)
    {
        int playerID = 1;
        char text[1000];

        // One row of 24 pixels per player, starting one row below y
        y += 24;
        for (; playerID <= 8; playerID++, y += 24) {
            if (DAT_GameState::instance.playerDataArray[playerID].playerDeathRelated != 0) {
                continue;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID != 0) {
                continue;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                continue;
            }

            int aiIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;

            uint color = DAT_RenderingDefinedData::instance
                             .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerID]];

            // Player number and name
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                playerID, x + 6, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
            // "-"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___005a2280, x + 16, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.DAT_PlayerNames[playerID], x + 26, y + 1, OpenSHC::Text::TTA_LEFT,
                color, 0, 18, FALSE, 0);

            // Strength feeling
            if (DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling == OpenSHC::AI::AIST_WEAK) {
                // "Weak"
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_Weak_005aad78, x + 202, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling
                == OpenSHC::AI::AIST_DEFAULT) {
                // "Normal"
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_Normal_005aad70, x + 202, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            } else {
                // "Strong"
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_Strong_005aad68, x + 202, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            }

            // Current AIV pause
            // "P:"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_P__005aad64, x + 262, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].aivCurrentPause, x + 264, y, OpenSHC::Text::TTA_LEFT,
                color, 0, 18, TRUE, 0);

            // Attack target and coordination level
            // "Atk:%d W:%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Atk_d_W_d_005aad58,
                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID,
                DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 302, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // fixme: Castle (AIV); the castle ID is passed even for human players, whose format ignores it
            int aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;
            if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL) {
                // "AIV:n/a"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    text, s_AIV_n_a_005aad50, DAT_AIVState::instance.aivs[aivID].castleID + 1);
            } else {
                // "AIV: %d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    text, s_AIV___d_005aad48, DAT_AIVState::instance.aivs[aivID].castleID + 1);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 382, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // Engineers
            // "E:%d/%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_E_d_d_005aad40,
                DAT_GameState::instance.playerDataArray[playerID].totalTroopsType6,
                DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01
                    + this->aics[aiIndex].SortieUnitRangedMin);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 452, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // Siege troops (attack troops without engineers): attack ticker in white when not attacking,
            // otherwise the attack force target
            if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState != 0) {
                // "%d/%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_perc_d_slash_perc_d_005a2780,
                    DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                        - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops,
                    DAT_GameState::instance.playerDataArray[playerID].attackTicker);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    text, x + 512, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 0, 18, FALSE, 0);
            } else {
                // "Sg:%d/%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Sg_d_d_005aad34,
                    DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                        - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops,
                    DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength
                        + this->aics[aiIndex].AttForceBase);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(text, x + 512, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            }

            // Raiding/harassing troops
            // "Hr:%d/%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Hr_d_d_005aad28,
                DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk,
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(
                    aiIndex, playerID));
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 592, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // Defensive troops
            // "Df:%d/%d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, s_Df_d_d_005aad1c,
                DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk,
                this->aics[aiIndex].DefWalls);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 657, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
        }
    }

}
}
