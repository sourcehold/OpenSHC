#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518C50
        void TroopValueState::renderAttackInfoDebugOverlay(int x, int y, int width, int height)
        {
            int iVar1;
            int _offset;
            int iVar2;
            int xParam;
            char local_3ec[1000];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3ec;
            xParam = x + 2;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Biggest zone: ", xParam, y, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.biggestZone, xParam, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            iVar2 = x + 0xc;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Start zone: ", iVar2, y, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startZone, iVar2, y, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            iVar1 = y + 0x10;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Scale zone: ", xParam, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.scaleZone, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "keep POS: ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .keep.yEntry,
                iVar2, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            iVar1 = y + 0x20;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "nof fpoints: ", xParam, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.nof_fpoints, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "inv count: ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.inv_count, iVar2, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "nof tribes: ", x + 0x16, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (int)(char)DAT_TroopValueState::instance.attackInfo.nof_tribes[DAT_TroopValueState::instance.attackInfo.inv_count], x + 0x16, iVar1,
                Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            iVar1 = y + 0x30;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Start con: ", xParam, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.startCon, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Keep con: ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.keepCon, iVar2, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "cas dis: ", x + 0x16, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.casDis, x + 0x16, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "zone size: ", x + 0x20, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_TroopValueState::instance.attackInfo.zoneSize, x + 0x20, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            _offset = DAT_TroopValueState::instance.attackInfo.attacker * 0x177bc;
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "Hack:%d(%d)(%d)  Scale:%d(%d)(%d) Stone:%d",
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -0xc),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -8),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.hackValuesArray + _offset + -4),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0xc),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -8),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -4),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray + _offset + -0x10));
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0x40, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            iVar2 = DAT_TroopValueState::instance.attackInfo.attacker * 0x177bc;
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "Town:%d(%d)  Gate:%d(%d)  Moat:%d(%d) Lord:%d(%d)",
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar2 + -0xc),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.townValuesArray + iVar2 + -4),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar2 + -0xc),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + iVar2 + -4),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + iVar2 + -0xc),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.moatValuesArray + iVar2 + -4), DAT_TroopValueState::instance.attackInfo.lord1,
                DAT_TroopValueState::instance.attackInfo.lord2);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0x50, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "High:%d(%d)(%d)  Arch:%d(%d)(%d)  People:%d(%d)(%d)",
                DAT_TroopValueState::instance.attackInfo.high1, DAT_TroopValueState::instance.attackInfo.high2, DAT_TroopValueState::instance.attackInfo.high3, DAT_TroopValueState::instance.attackInfo.arch1,
                DAT_TroopValueState::instance.attackInfo.arch2, DAT_TroopValueState::instance.attackInfo.arch3, DAT_TroopValueState::instance.attackInfo.people1, DAT_TroopValueState::instance.attackInfo.people2,
                DAT_TroopValueState::instance.attackInfo.people3);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0x60, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            iVar2 = DAT_TroopValueState::instance.attackInfo.attacker * 0x177bc;
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "Wide:%d(%d)(%d)",
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar2 + -0xc),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar2 + -8),
                *(undefined4*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + iVar2 + -4));
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0x70, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "Archer points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.archerPoints, DAT_TroopValueState::instance.attackInfo.archerPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0x80, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "Support points:%d,  Next:%d",
                DAT_TroopValueState::instance.attackInfo.supportPoints, DAT_TroopValueState::instance.attackInfo.supportPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0x90, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(
                local_3ec, "Tent points:%d,  Next:%d", DAT_TroopValueState::instance.attackInfo.tentPoints, DAT_TroopValueState::instance.attackInfo.tentPointsNext);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0xa0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(local_3ec,
                "ai troops: A:%d X:%d S:%d P:%d M:%d S:%d K:%d L:%d E:%d T:%d",
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
                local_3ec, xParam, y + 0xb0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "killed:%d lost:%d AI troops:%d",
                DAT_GameState::instance.playerDataArray[1].troopsKilled,
                DAT_GameState::instance.playerDataArray[1].troopsLost, DAT_TroopValueState::instance.attackInfo.aiTroops);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0xc0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL(OS_Func::_sprintf)(local_3ec, "Points: %d, %d, %d, %d, %d, %d, %d, %d, %d ",
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[0], DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[1],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2], DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4], DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[6], DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[7],
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[8]);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                local_3ec, xParam, y + 0xd0, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            ;
        }

    }
}
}
