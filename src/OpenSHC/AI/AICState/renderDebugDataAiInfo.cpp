#include "OpenSHC/AI/AICState.func.hpp"
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
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AICState;
    using OpenSHC::AI::AIStrengthType;
    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AIC::AICSpecification;
    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1320
    void AICState ::renderDebugDataAiInfo(int x, int y, int width, int height)

    {

        uint foregroundColor;

        int iVar1;

        PlayerData* _playerData;

        int yParam;

        char* pcVar2;

        uint foregroundColor_00;

        char (*pPlayerNames)[250];

        int _aiTypeMin1;

        AICSpecification* local_3f4;

        AICState* local_3f0;

        char local_3ec[1000];

        uint local_4;

        int _playerID;

        local_4 = MSVC_SecurityCookie::instance ^ (uint)&_playerID;

        local_3f0 = this;

        _playerID = 1;

        _playerData = &DAT_GameState::instance.playerDataArray[1];

        pPlayerNames = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;

        do {

            yParam = y + 0x18;

            if (((_playerData->playerDeathRelated == 0) && (_playerData->lordKilledByPlayerID == 0))
                && ((_playerData->aiType != OpenSHC::AI::AIT_NULL
                    || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1)))) {

                /*
                        aiType - 1 */

                _aiTypeMin1 = _playerData->aiType + ~OpenSHC::AI::AIT_NULL;

                foregroundColor
                    = DAT_RenderingDefinedData::instance
                          .DAT_ColorArray[DAT_BlendingDefinedData::instance.SEC_PlayerSlotUnitColor[_playerID]];

                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    _playerID, x + 6, yParam, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);

                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "-", x + 0x10, yParam, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    *pPlayerNames, x + 0x1a, y + 0x19, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                if (_playerData->aiStrengthFeeling == OpenSHC::AI::AIST_WEAK) {

                    pcVar2 = "Weak";

                }

                else if (_playerData->aiStrengthFeeling == OpenSHC::AI::AIST_DEFAULT) {

                    pcVar2 = "Normal";

                }

                else {

                    pcVar2 = "Strong";
                }

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    pcVar2, x + 0xca, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    "P:", x + 0x106, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    _playerData->aivCurrentPause, x + 0x108, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12,
                    TRUE, 0);

                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    local_3ec, "Atk:%d W:%d", _playerData->attackedPlayerID, _playerData->aiAttackCoordinationLevel);

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    local_3ec, x + 0x12e, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                if (_playerData->aiType == OpenSHC::AI::AIT_NULL) {

                    iVar1 = DAT_AIVState::instance.SEC_AIVS[_playerData->aivID].castleID;

                    pcVar2 = "AIV:n/a";

                }

                else {

                    iVar1 = DAT_AIVState::instance.SEC_AIVS[_playerData->aivID].castleID;

                    pcVar2 = "AIV: %d";
                }

                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_3ec, (char const*)((int)(pcVar2)), iVar1 + 1);

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    local_3ec, x + 0x17e, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                local_3f4 = local_3f0->aics + _aiTypeMin1;

                /*
                        total engineers? */

                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_3ec, "E:%d/%d", _playerData->totalTroopsType6,
                    _playerData->unknownCounter_01 + local_3f0->aics[_aiTypeMin1].SortieUnitRangedMin);

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    local_3ec, x + 0x1c4, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                /*
                        total attack troops - engineer troops */

                iVar1 = _playerData->totalAttackTroops - _playerData->totalAttackingEngineerTroops;

                /*
                        ai player state == attacking */

                if (_playerData->aiPlayerState == 0) {

                    /*
                              AttForceBase + currentWaveRandomAttackingStrength */

                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_3ec, "Sg:%d/%d", iVar1,
                        _playerData->currentWaveRandomAttackingStrength + local_3f4->AttForceBase);

                    foregroundColor_00 = foregroundColor;

                }

                else {

                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_3ec, "%d/%d", iVar1, _playerData->attackTicker);

                    foregroundColor_00 = 0xffffff;
                }

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    local_3ec, x + 0x200, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor_00, 0, 0x12, FALSE, 0);

                iVar1 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount, local_3f0)(
                    _aiTypeMin1, _playerID);

                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    local_3ec, "Hr:%d/%d", _playerData->totalRaidingTroopsUnk, iVar1);

                /*
                        display raid/harassing units */

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    local_3ec, x + 0x250, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);

                /*
                        TotalDefensiveTroops / DefWalls */

                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    local_3ec, "Df:%d/%d", _playerData->totalDefensiveTroopsUnk, local_3f4->DefWalls);

                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    local_3ec, x + 0x291, yParam, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, FALSE, 0);
            }

            pPlayerNames = pPlayerNames + 1;

            _playerID = _playerID + 1;

            _playerData = _playerData + 0xe7d;

            y = yParam;

        } while (_playerID < 9);

        ;

        return;
    }

}
}
