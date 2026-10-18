#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518C50
        void TroopValueState::renderAttackInfoDebugOverlay(int x, int y, int width, int height)
        {
            char textBuffer[1000];
            uint securityCookie = MSVC_SecurityCookie::instance ^ (uint)textBuffer;
            int const xParam = x + 2;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Biggest zone: ", xParam, y, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.biggestZone, xParam, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            int const xParam2 = xParam + 0xa;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Start zone: ", xParam2, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startZone, xParam2, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            int yParam = y + 0x10;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Scale zone: ", xParam, yParam, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.scaleZone, xParam, yParam, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "keep POS: ", xParam2, yParam, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .keep.yEntry,
                xParam2, yParam, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            yParam = y + 0x20;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "nof fpoints: ", xParam, yParam, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.nof_fpoints, xParam, yParam, Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "inv count: ", xParam2, yParam, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.inv_count, xParam2, yParam, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "nof tribes: ", xParam + 0x14, yParam, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(char)DAT_TroopValueState::instance.attackInfo
                    .nof_tribes[DAT_TroopValueState::instance.attackInfo.inv_count],
                xParam + 0x14, yParam, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            yParam = y + 0x30;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Start con: ", xParam, yParam, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startCon, xParam, yParam, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Keep con: ", xParam2, yParam, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.keepCon, xParam2, yParam, Text::TTA_LEFT, 0x80ff, 0x12, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "cas dis: ", xParam + 0x14, yParam, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.casDis, xParam + 0x14, yParam, Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "zone size: ", xParam + 0x1e, yParam, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.zoneSize, xParam + 0x1e, yParam, Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Hack:%d(%d)(%d)  Scale:%d(%d)(%d) Stone:%d",
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .hack1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .hack2,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .hack3,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .scale1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .scale2,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .scale3,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .stone1);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0x40, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Town:%d(%d)  Gate:%d(%d)  Moat:%d(%d) Lord:%d(%d)",
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .town1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .town3,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .gate1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .gate2,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .moat1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .moat3,
                DAT_TroopValueState::instance.attackInfo.lord1, DAT_TroopValueState::instance.attackInfo.lord2);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0x50, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "High:%d(%d)(%d)  Arch:%d(%d)(%d)  People:%d(%d)(%d)",
                DAT_TroopValueState::instance.attackInfo.high1, DAT_TroopValueState::instance.attackInfo.high2,
                DAT_TroopValueState::instance.attackInfo.high3, DAT_TroopValueState::instance.attackInfo.arch1,
                DAT_TroopValueState::instance.attackInfo.arch2, DAT_TroopValueState::instance.attackInfo.arch3,
                DAT_TroopValueState::instance.attackInfo.people1, DAT_TroopValueState::instance.attackInfo.people2,
                DAT_TroopValueState::instance.attackInfo.people3);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0x60, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Wide:%d(%d)(%d)",
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide2,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide3);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0x70, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Archer points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.archerPoints,
                DAT_TroopValueState::instance.attackInfo.archerPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0x80, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Support points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.supportPoints,
                DAT_TroopValueState::instance.attackInfo.supportPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0x90, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Tent points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.tentPoints,
                DAT_TroopValueState::instance.attackInfo.tentPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0xa0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "ai troops: A:%d X:%d S:%d P:%d M:%d S:%d K:%d L:%d E:%d T:%d",
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_A,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_X,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_S,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_P,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_M,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_S2,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_K,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_L,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_E,
                DAT_TroopValueState::instance.attackInfo.aiTribeSizesPerTribeType.aiTroops_T);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0xb0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "killed:%d lost:%d AI troops:%d",
                DAT_GameState::instance.playerDataArray[1].troopsKilled,
                DAT_GameState::instance.playerDataArray[1].troopsLost,
                DAT_TroopValueState::instance.attackInfo.aiTroops);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0xc0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Points: %d, %d, %d, %d, %d, %d, %d, %d, %d ",
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[0],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[1],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[6],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[7],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[8]);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, xParam, y + 0xd0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            ;
        }

    }
}
}
