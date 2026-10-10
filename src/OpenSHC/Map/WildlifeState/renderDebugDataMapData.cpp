#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_BRIGHT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_DARK_GREEN.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MODERATE_GREEN.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Map {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052BF40
    void WildlifeState::renderDebugDataMapData(int x, int y, int width, int height)
    {
        int iVar2;
        int iVar4;
        int iVar8;
        char* textAddress;
        int x1 = x + 2;
        if (!this->DAT_DebugDataMapDataDisplayType) {
            textAddress = "Connect ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 1) {
            textAddress = "Chimps  ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 2) {
            textAddress = "Farmland   ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 3) {
            textAddress = "Humans  ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 4) {
            textAddress = "Mankind  ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 5) {
            textAddress = "Deer  ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 6) {
            textAddress = "Route  ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 7) {
            textAddress = "Panic  ";
        } else if (this->DAT_DebugDataMapDataDisplayType == 8) {
            textAddress = "Siege  ";
        } else {
            if (this->DAT_DebugDataMapDataDisplayType != 9)
                goto LAB_0052c0db;
            textAddress = "Slink  ";
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            textAddress, x + 0x1a6, y + 4, Text::TTA_LEFT, 0xffffff, 0x11, FALSE, 0);
    LAB_0052c0db:
        /*
          render the squares
         */
        int iVar7 = 41;
        int iVar6 = y;
        do {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, iVar6, x + 0x192, iVar6, (ushort)(COL_WHITE::instance.shortValue));
            iVar6 = iVar6 + 10;
            iVar7 = iVar7 + -1;
        } while (iVar7);
        iVar7 = 41;
        iVar6 = x1;
        do {
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                iVar6, y, iVar6, y + 400, (ushort)(COL_WHITE::instance.shortValue));
            iVar6 = iVar6 + 10;
            iVar7 = iVar7 + -1;
            iVar8 = 0;
        } while (iVar7);
        do {
            for (iVar6 = 0; iVar6 < 40; iVar6++) {
                if (0 < this->grid[iVar6][iVar8].firstMember) {
                    undefined2 uVar5 = COL_BLUE::instance.shortValue;
                    if (!this->DAT_DebugDataMapDataDisplayType) {
                        uint uVar1 = this->grid[iVar6][iVar8].separateAreaID;
                        uint uVar3 = uVar1 & 7;
                        if (!uVar1 || (uVar5 = COL_RED::instance.shortValue, uVar3 == 1)
                            || (uVar5 = COL_BRIGHT_YELLOW::instance.shortValue,
                                uVar3 == 2
                                    || ((uVar5 = COL_MODERATE_GREEN::instance.shortValue,
                                        uVar3 == 3 || (uVar5 = COL_WHITE::instance.shortValue, uVar3 == 4))))
                            || (uVar5 = COL_DARK_CYAN_GREY::instance.shortValue, uVar3 == 5))
                            goto LAB_0052c526;
                        if (uVar3 == 6) {
                        LAB_0052c51f:
                            uVar5 = COL_LIME::instance.shortValue;
                            goto LAB_0052c526;
                        }
                        iVar2 = y + iVar8 * 10;
                        iVar4 = x1 + iVar6 * 10;
                        uVar5 = COL_VERY_DARK_GREY::instance.shortValue;
                        if (uVar3 == 7) {
                            uVar5 = COL_VIVID_BLUE::instance.shortValue;
                        }
                    } else {
                        if (this->DAT_DebugDataMapDataDisplayType == 1) {
                            if (this->grid[iVar6][iVar8].separateAreaID != 0) {
                                iVar7 = this->grid[iVar6][iVar8].chimps;
                                uVar5 = COL_RED::instance.shortValue;
                            joined_r0x0052c335:
                                iVar2 = y + iVar8 * 10;
                                iVar4 = x1 + iVar6 * 10;
                                if (!iVar7) {
                                    uVar5 = COL_LIME::instance.shortValue;
                                }
                                goto LAB_0052c533;
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 2) {
                            if (this->grid[iVar6][iVar8].separateAreaID != 0
                                && (uVar5 = COL_DARK_GREEN::instance.shortValue,
                                    this->grid[iVar6][iVar8].farmFieldTiles == 0)
                                && (uVar5 = COL_RED::instance.shortValue, this->grid[iVar6][iVar8].rabbitCount == 0)
                                && (uVar5 = COL_WHITE::instance.shortValue,
                                    this->grid[iVar6][iVar8].field15_0x3c == 0)) {
                                iVar7 = this->grid[iVar6][iVar8].field20_0x50;
                                uVar5 = COL_DARK_CYAN_GREY::instance.shortValue;
                                goto joined_r0x0052c335;
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 3) {
                            if (this->grid[iVar6][iVar8].separateAreaID != 0) {
                                iVar7 = this->grid[iVar6][iVar8].unstalkedUnitCount;
                                uVar5 = COL_RED::instance.shortValue;
                                goto joined_r0x0052c335;
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 4) {
                            if ((this->grid[iVar6][iVar8].separateAreaID != 0)
                                && (uVar5 = COL_RED::instance.shortValue,
                                    this->grid[iVar6][iVar8].unstalkedUnitCount == 0)) {
                                iVar7 = this->grid[iVar6][iVar8].buildingTiles;
                            joined_r0x0052c3aa:
                                if (!iVar7) {
                                    iVar7 = this->grid[iVar6][iVar8].field13_0x34;
                                    uVar5 = COL_BRIGHT_YELLOW::instance.shortValue;
                                    goto joined_r0x0052c335;
                                }
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 5) {
                            if (this->grid[iVar6][iVar8].separateAreaID != 0
                                && (uVar5 = COL_RED::instance.shortValue,
                                    this->grid[iVar6][iVar8].unstalkedUnitCount == 0)
                                && this->grid[iVar6][iVar8].buildingTiles == 0
                                && (uVar5 = COL_BLACK::instance.shortValue,
                                    this->grid[iVar6][iVar8].lionCount == 0
                                        && (this->grid[iVar6][iVar8].camelCount == 0))) {
                                iVar7 = this->grid[iVar6][iVar8].deerCount;
                                uVar5 = COL_MODERATE_GREEN::instance.shortValue;
                                goto joined_r0x0052c3aa;
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 6) {
                            if (this->grid[iVar6][iVar8].separateAreaID != 0
                                && (uVar5 = COL_RED::instance.shortValue, this->grid[iVar6][iVar8].deerCount == 0)
                                && (uVar5 = COL_VIVID_BLUE::instance.shortValue,
                                    this->grid[iVar6][iVar8].lionCount == 0)
                                && (uVar5 = COL_WHITE::instance.shortValue,
                                    this->grid[iVar6][iVar8].field15_0x3c == 0)) {
                                iVar7 = this->grid[iVar6][iVar8].casDisRelated2;
                                uVar5 = COL_BRIGHT_YELLOW::instance.shortValue;
                            joined_r0x0052c46b:
                                if (!iVar7) {
                                    iVar7 = this->grid[iVar6][iVar8].field13_0x34;
                                    uVar5 = COL_BLACK::instance.shortValue;
                                    goto joined_r0x0052c335;
                                }
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 7) {
                            if ((this->grid[iVar6][iVar8].separateAreaID != 0)
                                && (uVar5 = COL_WHITE::instance.shortValue,
                                    this->grid[iVar6][iVar8].field18_0x48 == 0)) {
                                iVar7 = this->grid[iVar6][iVar8].deerCount;
                                uVar5 = COL_RED::instance.shortValue;
                                goto joined_r0x0052c46b;
                            }
                        } else if (this->DAT_DebugDataMapDataDisplayType == 8) {
                            uVar5 = COL_WHITE::instance.shortValue;
                            if (this->grid[iVar6][iVar8].field24_0x60 == 0
                                && (uVar5 = COL_BLACK::instance.shortValue, this->grid[iVar6][iVar8].field25_0x64 == 0)
                                && (uVar5 = COL_BRIGHT_YELLOW::instance.shortValue,
                                    this->grid[iVar6][iVar8].castlebuildings == 0
                                        && ((uVar5 = COL_BLUE::instance.shortValue,
                                            this->grid[iVar6][iVar8].separateAreaID != 0
                                                && (uVar5 = COL_VIVID_BLUE::instance.shortValue,
                                                    this->grid[iVar6][iVar8].unknownNonZero01 == 0))))) {
                                iVar7 = this->grid[iVar6][iVar8].field27_0x6c;
                                uVar5 = COL_RED::instance.shortValue;
                                goto joined_r0x0052c335;
                            }
                        } else {
                            if (this->DAT_DebugDataMapDataDisplayType != 9)
                                continue;
                            uVar5 = COL_RED::instance.shortValue;
                            if (this->grid[iVar6][iVar8].field29_0x74 == 0
                                && (uVar5 = COL_VIVID_BLUE::instance.shortValue,
                                    this->grid[iVar6][iVar8].unknownNonZero01 == 0)
                                && (uVar5 = COL_BLUE::instance.shortValue,
                                    this->grid[iVar6][iVar8].separateAreaID != 0))
                                goto LAB_0052c51f;
                        }
                    LAB_0052c526:
                        iVar4 = x1 + iVar6 * 10;
                        iVar2 = y + iVar8 * 10;
                    }
                LAB_0052c533:
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                        iVar4 + 1, iVar2 + 1, iVar4 + 9, iVar2 + 9, (ushort)(uVar5));
                }
            }
            iVar8 = iVar8 + 1;
            if (40 < iVar8) {}
        } while (true);
    }

}
}
