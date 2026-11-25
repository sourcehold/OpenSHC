#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x00518C50
        void TroopValueState::renderAttackInfoDebugOverlay(int x, int y, int width, int height)
        {
            char textBuffer[1000];
            uint const securityCookie = MSVC_SecurityCookie::instance ^ (uint)textBuffer;
            int const column1X = x + 2;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Biggest zone: ", column1X, y, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.biggestZone, column1X, y, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
            int const column2X = column1X + 10;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Start zone: ", column2X, y, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startZone, column2X, y, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
            int rowY = y + 16;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Scale zone: ", column1X, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.scaleZone, column1X, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "keep POS: ", column2X, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                    .yEntry,
                column2X, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
            rowY = y + 32;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "nof fpoints: ", column1X, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.nof_fpoints, column1X, rowY, Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "inv count: ", column2X, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.inv_count, column2X, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "nof tribes: ", column1X + 20, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (char)DAT_TroopValueState::instance.attackInfo
                    .nof_tribes[DAT_TroopValueState::instance.attackInfo.inv_count],
                column1X + 20, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
            rowY = y + 48;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Start con: ", column1X, rowY, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startCon, column1X, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Keep con: ", column2X, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.keepCon, column2X, rowY, Text::TTA_LEFT, 0x80ff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "cas dis: ", column1X + 20, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.casDis, column1X + 20, rowY, Text::TTA_LEFT, 0x80ff, 0x12,
                TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "zone size: ", column1X + 30, rowY, Text::TTA_LEFT, 0xffffff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.zoneSize, column1X + 30, rowY, Text::TTA_LEFT, 0x80ff, 0x12,
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
                textBuffer, column1X, y + 64, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
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
                textBuffer, column1X, y + 80, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "High:%d(%d)(%d)  Arch:%d(%d)(%d)  People:%d(%d)(%d)",
                DAT_TroopValueState::instance.attackInfo.high1, DAT_TroopValueState::instance.attackInfo.high2,
                DAT_TroopValueState::instance.attackInfo.high3, DAT_TroopValueState::instance.attackInfo.arch1,
                DAT_TroopValueState::instance.attackInfo.arch2, DAT_TroopValueState::instance.attackInfo.arch3,
                DAT_TroopValueState::instance.attackInfo.people1, DAT_TroopValueState::instance.attackInfo.people2,
                DAT_TroopValueState::instance.attackInfo.people3);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 96, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
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
                textBuffer, column1X, y + 112, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Archer points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.archerPoints,
                DAT_TroopValueState::instance.attackInfo.archerPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 128, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Support points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.supportPoints,
                DAT_TroopValueState::instance.attackInfo.supportPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 144, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "Tent points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.tentPoints,
                DAT_TroopValueState::instance.attackInfo.tentPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 160, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
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
                textBuffer, column1X, y + 176, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, "killed:%d lost:%d AI troops:%d",
                DAT_GameState::instance.playerDataArray[1].troopsKilled,
                DAT_GameState::instance.playerDataArray[1].troopsLost,
                DAT_TroopValueState::instance.attackInfo.aiTroops);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 192, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
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
                textBuffer, column1X, y + 208, Text::TTA_LEFT, 0xffffff, 18, FALSE, 0);
        }

    }
}
}
