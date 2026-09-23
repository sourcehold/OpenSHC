#include "../AICState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/AI/AIC/AICSpecification.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AIStrengthType.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AICState;
    using OpenSHC::AI::AIStrengthType;
    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AIC::AICSpecification;
    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1320
    void AICState::renderDebugDataAiInfo(int x, int y, int width, int height)
    {
        char text[1000];

        // One row of 24 pixels per player, starting one row below y
        y += 24;
        for (int playerID = 1; playerID <= 8; playerID++, y += 24) {
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

            int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
            uint color = DAT_RenderingDefinedData::instance
                             .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerID]];

            // Player number and name
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                playerID, x + 6, y, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "-", x + 16, y, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.DAT_PlayerNames[playerID], x + 26, y + 1, OpenSHC::Text::TTA_LEFT,
                color, 0, 18, FALSE, 0);

            // Strength feeling
            if (DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling == OpenSHC::AI::AIST_WEAK) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("Weak", x + 202, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            } else if (DAT_GameState::instance.playerDataArray[playerID].aiStrengthFeeling
                == OpenSHC::AI::AIST_DEFAULT) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("Normal", x + 202, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("Strong", x + 202, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            }

            // Current AIV pause
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "P:", x + 262, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[playerID].aivCurrentPause, x + 264, y, OpenSHC::Text::TTA_LEFT,
                color, 0, 18, TRUE, 0);

            // Attack target and coordination level
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "Atk:%d W:%d",
                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID,
                DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 302, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // fixme: Castle (AIV); the castle ID is passed even for human players, whose format ignores it
            if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL) {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "AIV:n/a",
                    DAT_AIVState::instance.aivs[DAT_GameState::instance.playerDataArray[playerID].aivID].castleID + 1);
            } else {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "AIV: %d",
                    DAT_AIVState::instance.aivs[DAT_GameState::instance.playerDataArray[playerID].aivID].castleID + 1);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 382, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // Engineers
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "E:%d/%d",
                DAT_GameState::instance.playerDataArray[playerID].totalTroopsType6,
                DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01
                    + this->aics[aicIndex].SortieUnitRangedMin);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 452, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // Siege troops (attack troops without engineers): attack ticker in white when not attacking,
            // otherwise the attack force target
            int siegeTroops = DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops;
            if (DAT_GameState::instance.playerDataArray[playerID].aiPlayerState != 0) {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    text, "%d/%d", siegeTroops, DAT_GameState::instance.playerDataArray[playerID].attackTicker);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(text, x + 512, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0, 18, FALSE, 0);
            } else {
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "Sg:%d/%d", siegeTroops,
                    DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength
                        + this->aics[aicIndex].AttForceBase);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(text, x + 512, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
            }

            // Raiding/harassing troops
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "Hr:%d/%d",
                DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk,
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, this)(
                    aicIndex, playerID));
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 592, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);

            // Defensive troops
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(text, "Df:%d/%d",
                DAT_GameState::instance.playerDataArray[playerID].totalDefensiveTroopsUnk,
                this->aics[aicIndex].DefWalls);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                text, x + 657, y, OpenSHC::Text::TTA_LEFT, color, 0, 18, FALSE, 0);
        }
    }

}
}
