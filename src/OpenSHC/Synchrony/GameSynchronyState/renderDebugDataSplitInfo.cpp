#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EED0
    void GameSynchronyState::renderDebugDataSplitInfo(int x, int y, int width, int height)
    {
        int iVar1;
        int* piVar3;
        char* textAddress;
        int iVar2 = x + 2;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Splinter box ", iVar2, y, Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
        if (!this->splinterType) {
            textAddress = " - Chimps";
        } else if (this->splinterType == 1) {
            textAddress = " - Structures";
        } else if (this->splinterType == 2) {
            textAddress = " - Vegetation";
        } else if (this->splinterType == 3) {
            textAddress = " - Tribes";
        } else if (this->splinterType == 4) {
            textAddress = " - Players";
        } else {
            if (this->splinterType != 5)
                goto LAB_0047efc0;
            textAddress = " - Game elements";
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            textAddress, x + 0xc, y, Text::TTA_LEFT, 0xffffff, 0x11, TRUE, 0);
    LAB_0047efc0:
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Total split data items:  ", iVar2, y + 0x1c, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        int xParam = x + 0xc;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->totalSplitDataItems, xParam, y + 0x1c, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        if (!this->splinterType) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Total split chimps:  ", iVar2, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitChimps, xParam, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "First split chimp:  ", x + 0xca, y + 0x2a, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitChimps, x + 0xd4, y + 0x2a, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            piVar3 = this->HASH_Units[2];
            iVar2 = 10;
            do {
                piVar3 = piVar3 + 1;
                uint color = (-(uint)(piVar3[-0x9c4] != *piVar3) & 0xff000100) + 0xffffff;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    piVar3[-0x9c4], xParam, y + 0x46, Text::TTA_LEFT, color, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    *piVar3, xParam, y + 0x54, Text::TTA_LEFT, color, 0x12, FALSE, 0);
                xParam = xParam + 0x28;
                iVar2 = iVar2 + -1;
            } while (iVar2);
        }
        if (this->splinterType == 1) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Total split structures:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitStructures, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "First split structure:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitStructures, x + 0xd4, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        }
        if (this->splinterType == 2) {
            iVar1 = y + 0x2a;
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "Total split veg:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->totalSplitVeg, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                "First split veg:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                this->firstSplitVeg, x + 0xd4, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        }
        if (this->splinterType != 3) {
            if (this->splinterType == 4) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split players:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitPlayers, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split player:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitPlayer;
            } else if (this->splinterType == 5) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split elements:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitElements, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split element:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitElement;
            } else if (this->splinterType == 6) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split layers:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitLayers, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split layer:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitLayer;
            } else if (this->splinterType == 7) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split flies:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitFlies, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split fly:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitFly;
            } else if (this->splinterType == 8) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split moats:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitMoats, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split moat:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitMoat;
            } else if (this->splinterType == 9) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split teleports:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitTeleports, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split teleport:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitTeleports;
            } else if (this->splinterType == 10) {
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split pitch ditchs:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitPitchDitches, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split pitch ditch:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitPitchDitch;
            } else {
                if (this->splinterType != 0xb) {}
                iVar1 = y + 0x2a;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "Total split zones:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    this->totalSplitZones, xParam, iVar1, 0x80ff, 0x12, 1);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    "First split zone:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
                iVar2 = this->firstSplitZone;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                iVar2, x + 0xd4, y + 0x2a, 0x80ff, 0x12, 1);
        }
        iVar1 = y + 0x2a;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "Total split tribes:  ", iVar2, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->totalSplitTribes, xParam, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "First split tribe:  ", x + 0xca, iVar1, Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            this->firstSplitTribe, x + 0xd4, iVar1, Text::TTA_LEFT, 0x80ff, 0x12, TRUE, 0);
    }

}
}
