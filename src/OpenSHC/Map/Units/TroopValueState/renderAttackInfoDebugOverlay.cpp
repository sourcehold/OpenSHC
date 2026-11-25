#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

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
            // "Biggest zone: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Biggest_zone__005abb48, column1X, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.biggestZone, column1X, y, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            int const column2X = column1X + 10;
            // "Start zone: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Start_zone__005abb38, column2X, y, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startZone, column2X, y, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            int rowY = y + 16;
            // "Scale zone: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Scale_zone__005abb28, column1X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.scaleZone, column1X, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "keep POS: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_keep_POS__005abb1c, column2X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .buildingEntryInfos[Game::Player::Enums::BEIE_KEEP]
                    .yEntry,
                column2X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            rowY = y + 32;
            // "nof fpoints: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_nof_fpoints__005abb0c, column1X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.nof_fpoints, column1X, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "inv count: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_inv_count__005abb00, column2X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.inv_count, column2X, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "nof tribes: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_nof_tribes__005abaf0, column1X + 20, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE,
                0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (char)DAT_TroopValueState::instance.attackInfo
                    .nof_tribes[DAT_TroopValueState::instance.attackInfo.inv_count],
                column1X + 20, rowY, Text::TTA_LEFT, Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            rowY = y + 48;
            // "Start con: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Start_con__005abae4, column1X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startCon, column1X, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "Keep con: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_Keep_con__005abad8, column2X, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.keepCon, column2X, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "cas dis: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_cas_dis__005abacc, column1X + 20, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.casDis, column1X + 20, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            // "zone size: "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_zone_size__005abac0, column1X + 30, rowY, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, TRUE, 0);
            // "Hack:%d(%d)(%d)  Scale:%d(%d)(%d) Stone:%d"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.zoneSize, column1X + 30, rowY, Text::TTA_LEFT,
                Rendering::Colors::COL_0080FF, 18, TRUE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Hack_d_d_d__Scale_d_d_d__005aba94,
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
            // "Town:%d(%d)  Gate:%d(%d)  Moat:%d(%d) Lord:%d(%d)"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 64, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Town_d_d__Gate_d_d__Moat_d__005aba60,
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
            // "High:%d(%d)(%d)  Arch:%d(%d)(%d)  People:%d(%d)(%d)"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 80, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_High_d_d_d__Arch_d_d_d__P_005aba2c,
                DAT_TroopValueState::instance.attackInfo.high1, DAT_TroopValueState::instance.attackInfo.high2,
                DAT_TroopValueState::instance.attackInfo.high3, DAT_TroopValueState::instance.attackInfo.arch1,
                DAT_TroopValueState::instance.attackInfo.arch2, DAT_TroopValueState::instance.attackInfo.arch3,
                DAT_TroopValueState::instance.attackInfo.people1, DAT_TroopValueState::instance.attackInfo.people2,
                DAT_TroopValueState::instance.attackInfo.people3);
            // "Wide:%d(%d)(%d)"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 96, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Wide_d_d_d__005aba1c,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide1,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide2,
                DAT_TroopValueState::instance.attackInfo
                    .playerInfo[DAT_TroopValueState::instance.attackInfo.attacker - 1]
                    .wide3);
            // "Archer points:%d,  Next:%d"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 112, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Archer_points_d__Next_d_005aba00,
                DAT_TroopValueState::instance.attackInfo.archerPoints,
                DAT_TroopValueState::instance.attackInfo.archerPointsNext);
            // "Support points:%d,  Next:%d"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 128, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Support_points_d__Next_d_005ab9e4,
                DAT_TroopValueState::instance.attackInfo.supportPoints,
                DAT_TroopValueState::instance.attackInfo.supportPointsNext);
            // "Tent points:%d,  Next:%d"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 144, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Tent_points_d__Next_d_005ab9c8,
                DAT_TroopValueState::instance.attackInfo.tentPoints,
                DAT_TroopValueState::instance.attackInfo.tentPointsNext);
            // "ai troops: A:%d X:%d S:%d P:%d M:%d S:%d K:%d L:%d E:%d T:%d"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 160, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_ai_troops__A_d_X_d_S_d_P_d_M_005ab988,
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
            // "killed:%d lost:%d AI troops:%d"
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 176, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_killed_d_lost_d_AI_troops_d_005ab968,
                DAT_GameState::instance.playerDataArray[1].troopsKilled,
                DAT_GameState::instance.playerDataArray[1].troopsLost,
                DAT_TroopValueState::instance.attackInfo.aiTroops);
            // "Points: %d, %d, %d, %d, %d, %d, %d, %d, %d "
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                textBuffer, column1X, y + 192, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(textBuffer, s_Points___d___d___d___d___d___d____005ab93c,
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
                textBuffer, column1X, y + 208, Text::TTA_LEFT, Rendering::Colors::COL_FFFFFF, 18, FALSE, 0);
        }

    }
}
}
