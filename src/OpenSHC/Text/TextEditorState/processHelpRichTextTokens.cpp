#include "../TextEditorState.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_00df3348.hpp"
#include "OpenSHC/Globals/DAT_00df334c.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    union TextMemUnion {
        uint value;
        wchar_t* text;
        HelpTextToken helpToken;
        HelpTextPicturePositionToken picturePositionToken;
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x0045FDC0
    int TextEditorState::processHelpRichTextTokens(int param_1)
    {
        short sVar1;
        ushort uVar2;
        WCHAR WVar3;
        undefined1 colorBlue;
        int iVar5;
        wchar_t* pwVar6;
        wchar_t* pwVar7;
        short* psVar8;
        int iVar9;
        uint uVar10;
        WCHAR* pWVar11;
        int iVar12;
        BOOLEnum BVar13;
        dword dVar14;
        short sVar15;
        uint colorRed;
        int iVar17;
        undefined1 colorGreen;
        char* pcVar19;
        int iVar20;
        int textMemIndex;
        dword local_138;
        int local_134;
        dword local_130;
        int local_12c;
        uint local_124;
        int local_120;
        int local_11c;
        int local_118;
        int local_114;
        FontSizeClass* local_110;
        int local_10c;
        int local_108;
        int local_104;
        int local_100;
        int local_fc;
        int local_f8;
        dword local_f4;
        int local_f0;
        uint local_ec;
        int local_e8;
        int local_e4;
        short* local_e0;
        int local_dc;
        uint local_d8;
        int local_d4;
        undefined4 local_d0;
        wchar_t local_cc[100];
        local_ec = 0xffffffff;
        textMemIndex = 0;
        local_110 = DAT_TextManagerObject::instance.fontSizeClassArray + 0x11;
        local_130 = DAT_TextManagerObject::instance.fontSizeClassArray[17].lineHeight_0x14;
        local_f0 = 0;
        local_d8 = 0xccfaff;
        local_d0 = 0x8bcf84;
        local_dc = -1;
        local_fc = 0;
        local_120 = 0;
        local_e8 = 0;
        local_108 = 0;
        local_11c = 0;
        local_100 = 0;
        local_10c = 0;
        local_e4 = 0;
        local_134 = -10000;
        if (this->helpDialogVariant == 2 || this->isCustomTextMode) {
            local_d8 = 0xc2f0eb;
        }
        if (!this->isTextHelpDialogMode) {
            return 1;
        }
        this->unknown_0x23964 = -1;
        this->unknown_0x23968 = -1;
        if (this->unknown_0x2396C) {
            DAT_00df334c::instance = 1;
        }
        if (this->activeHelpHotspotIndex < 0) {
            this->activeHelpHotspotIndex = 0;
        }
        if (this->customHelpTextLength < this->activeHelpHotspotIndex) {
            this->activeHelpHotspotIndex = this->customHelpTextLength;
        }
        iVar20 = 0;
        while (this->lineLayoutTable[iVar20].unknown0 != -1) {
            ++iVar20;
        }
        while (true) {
            iVar5 = textMemIndex;
            local_124 = local_d8;
            local_12c = 1;
            if (-1 < (int)local_ec) {
                local_124 = local_d0;
            }
            local_114 = textMemIndex;
            TextMemUnion textMemUnion;
            textMemUnion.value
                = MACRO_CALL_MEMBER(TextEditorState_Func::getWideCharOrWideCharPointer, this)(&textMemIndex);
            if (this->useAlternateHelpTab && textMemUnion.value < L' ' && textMemUnion.helpToken != HTT_NEWPARAGRAPH
                && iVar5 == this->activeHelpHotspotIndex) {
                local_108 = iVar20 + local_130;
                local_e8 = iVar20;
                if (param_1 == 1) {
                    iVar5 = 0;
                    if (local_120) {
                        iVar5 = this->lineLayoutTable[iVar20].unknown2 / 2;
                    }
                    local_10c = local_114 - local_11c;
                    if (this->unknown_0x2396C < 0) {
                        this->activeHelpHotspotIndex = local_100 + DAT_00df3348::instance;
                        if (local_11c <= this->activeHelpHotspotIndex) {
                            this->activeHelpHotspotIndex = local_11c + -1;
                        }
                        this->unknown_0x2396C = 0;
                    }
                    local_134 = 0;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        this->dialogContentX + iVar5 - 1 + local_138,
                        this->dialogContentY - this->helpContentScrollOffsetY - 1 + iVar20,
                        this->dialogContentX + iVar5 - 1 + local_138,
                        this->dialogContentY - this->helpContentScrollOffsetY + 1 + local_108,
                        COL_DARK_LIME::instance.shortValue);
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        this->dialogContentX + iVar5 + local_138,
                        this->dialogContentY - this->helpContentScrollOffsetY - 1 + iVar20,
                        this->dialogContentX + iVar5 + local_138,
                        this->dialogContentY - this->helpContentScrollOffsetY + 1 + local_108,
                        COL_DARK_LIME::instance.shortValue);
                    local_e4 = 1;
                    iVar5 = local_114;
                }
            }

            iVar17 = local_11c;
            iVar9 = 1;
            switch (textMemUnion.helpToken) {
            case (wchar_t*)0: // TODO?: unknown token, or just NULL, meaning end?
                if (param_1 == 0) {
                    iVar5 = iVar20 + -1 + local_130;
                    do {
                        this->topVisibleLineIndex = iVar5;
                        if (this->lineLayoutTable[this->topVisibleLineIndex + 1].unknown0 == 25
                            && this->lineLayoutTable[this->topVisibleLineIndex + 1].unknown1
                                == this->dialogContentHeight - 25)
                            break;
                    } while (iVar5 = this->topVisibleLineIndex + 1, this->topVisibleLineIndex + 1 < 20000);
                    this->topVisibleLineIndex += 6;
                    if (this->useAlternateHelpTab) {
                        if (local_e8 < this->helpContentScrollOffsetY) {
                            this->helpContentScrollOffsetY = local_e8;
                        }
                        if (this->helpContentScrollOffsetY + this->dialogContentWidth < local_108) {
                            this->helpContentScrollOffsetY = (local_108 - this->dialogContentWidth) + 5;
                            DAT_TextManagerObject::instance.field6_0x18 = 0;
                            return iVar9;
                        }
                    }
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
                if (!this->useAlternateHelpTab) {
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
                DAT_00df3348::instance = local_10c;
                if (0 < this->unknown_0x23960 && local_134 == 1) {
                    this->activeHelpHotspotIndex = local_10c + local_11c;
                    if (this->customHelpTextLength < this->activeHelpHotspotIndex) {
                        this->activeHelpHotspotIndex = this->customHelpTextLength;
                    }
                    this->unknown_0x23960 = 0;
                }
                if (!local_e4 && this->activeHelpHotspotIndex && DAT_00df334c::instance) {
                    --this->activeHelpHotspotIndex;
                    this->unknown_0x2396C = 0;
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
                DAT_00df334c::instance = 0;
                DAT_TextManagerObject::instance.field6_0x18 = 0;
                return TRUE;
            case HTT_PIC:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(local_cc, L"<PIC %d (\"%S\"),",
                        this->DAT_PointerToTemporaryTextMemory[textMemIndex],
                        this->graphicFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    ++textMemIndex;
                    switch ((HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[textMemIndex] + 1) {
                    case HTT_PIC_LEFT:
                        wcscat(local_cc, L"LEFT>");
                        textMemIndex += 2;
                        break;
                    case HTT_PIC_CENTRE:
                        wcscat(local_cc, L"CENTRE>");
                        textMemIndex += 2;
                        break;
                    case HTT_PIC_RIGHT:
                        wcscat(local_cc, L"RIGHT>");
                        textMemIndex += 2;
                        break;
                    case HTT_PIC_HERE:
                        wcscat(local_cc, L"HERE>");
                        textMemIndex += 2;
                        break;
                    default:
                        textMemIndex += 2;
                        break;
                    }
                    break;
                } else {
                    ++local_dc;
                    if (param_1 == 1) {
                        if (this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] == 3) {
                            uVar10 = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                            goto LAB_0046026d;
                        }
                        textMemIndex += 3;
                        continue;
                    }
                    if (param_1
                        || (local_dc != this->imageHotspotCount
                            && this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] != 3)) {
                        textMemIndex += 3;
                        continue;
                    }
                    uVar2 = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    uVar10 = (uint)uVar2;
                    if (local_dc == this->imageHotspotCount) {
                        this->imageHotspotTable[this->imageHotspotCount].yPos = iVar20 + 25;
                        this->imageHotspotTable[this->imageHotspotCount].imageRelated = uVar2;
                        this->imageHotspotTable[this->imageHotspotCount].unknown3 = local_ec;
                    }
                LAB_0046026d:
                    local_f4 = (dword)this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                    iVar5 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[100 - uVar10].width;
                    dVar14 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[100 - uVar10].height;
                    sVar15 = (short)iVar5;
                    switch ((HelpTextPicturePositionToken)local_f4) {
                    case HTT_PIC_LEFT:
                        this->imageHotspotTable[this->imageHotspotCount].xPos = this->lineLayoutTable[iVar20].unknown0;
                        int sVar1 = this->lineLayoutTable[iVar20].unknown0;
                        for (int i = 0; i < dVar14 + 50; ++i) {
                            this->lineLayoutTable[iVar20 + i].unknown1 = sVar1 + 25 + sVar15;
                        }
                        break;
                    case HTT_PIC_CENTRE:
                        this->imageHotspotTable[this->imageHotspotCount].xPos = (this->dialogContentHeight - iVar5) / 2;
                        for (int i = 0; i < dVar14 + 50; ++i) {
                            this->lineLayoutTable[iVar20 + i].unknown0 = -1;
                        }
                        break;
                    case HTT_PIC_RIGHT:
                        this->imageHotspotTable[this->imageHotspotCount].xPos
                            = this->lineLayoutTable[iVar20].unknown1 - sVar15;
                        int sVar1 = this->lineLayoutTable[iVar20].unknown1;
                        for (int i = 0; i < dVar14 + 50; ++i) {
                            this->lineLayoutTable[iVar20 + i].unknown1 = (sVar1 - sVar15) - 25;
                            this->lineLayoutTable[iVar20 + i].unknown0 = -1;
                        }
                        break;
                    case HTT_PIC_HERE:
                        iVar5 = iVar5 + 3;
                        if (this->lineLayoutTable[iVar20].unknown1 < iVar5 + local_138) {
                            local_f0 = 0;
                            if (local_120) {
                                this->lineLayoutTable[iVar20].unknown2
                                    = this->lineLayoutTable[iVar20].unknown1 - local_138;
                                local_120 = local_fc;
                            }
                            do {
                                iVar20 = iVar20 + local_130 + 1;
                                iVar12 = iVar20 * 6 + 0x2409db4;
                                do {
                                    iVar9 = iVar20;
                                    local_138 = (dword) * (short*)(iVar12 + 6);
                                    iVar12 = iVar12 + 6;
                                    iVar20 = iVar9 + 1;
                                } while (local_138 == 0xffffffff);
                            } while (this->lineLayoutTable[iVar9 + 1].unknown1 < local_138 + iVar5);
                            if (this->useAlternateHelpTab && param_1 == 1) {
                                ++local_134;
                                local_100 = local_11c;
                                local_11c = local_114;
                                if (0 < this->unknown_0x2396C && 1 < local_134) {
                                    this->activeHelpHotspotIndex = iVar17 + local_10c;
                                    local_134 = -10000;
                                    if (local_114 <= this->activeHelpHotspotIndex) {
                                        this->activeHelpHotspotIndex = local_114 + -1;
                                    }
                                    this->unknown_0x2396C = 0;
                                }
                            }
                            local_130 = local_110->lineHeight_0x14;
                        }
                        if (local_130 < dVar14) {
                            local_130 = dVar14;
                        }
                        local_138 = local_138 + iVar5;
                        if (param_1 != 1 && local_dc == this->imageHotspotCount) {
                            this->imageHotspotTable[this->imageHotspotCount].xPos = local_138 - iVar5;
                            this->imageHotspotTable[this->imageHotspotCount].yPos = iVar20;
                            ++this->imageHotspotCount;
                        }
                    }
                    textMemIndex += 3;
                    if (local_f4 == 3 || param_1) {
                        continue;
                    }
                    ++this->imageHotspotCount;
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return FALSE;
                }
            case HTT_FONT:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(
                        local_cc, L"<FONT %d>", this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
                    textMemIndex += 2;
                    break;
                } else {
                    int fontSize = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    if (fontSize < 15) {
                        fontSize += 5;
                    }
                    textMemIndex = textMemIndex + 2;
                    local_110 = DAT_TextManagerObject::instance.fontSizeClassArray + fontSize;
                    dVar14 = DAT_TextManagerObject::instance.fontSizeClassArray[fontSize].lineHeight_0x14;
                    if (local_130 < dVar14 || !local_f0) {
                        local_130 = dVar14;
                    }
                    continue;
                }
            case HTT_COLOUR:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(local_cc, L"<COLOUR %S>",
                        DAT_UserHelpDefinedData::instance
                            .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                            .name_0x0);
                    textMemIndex += 2;
                    break;
                } else {
                    if (param_1 == 1) {
                        int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        if (this->helpDialogVariant == 2 && colorIndex == 1) {
                            colorRed = 0xd7;
                            colorGreen = 0xd2;
                            colorBlue = 0xa4;
                        } else {
                            colorRed = DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].r_0x4;
                            colorGreen = DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].g_0x8;
                            colorBlue = DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].b_0xc;
                        }
                        textMemIndex += 2;
                        local_d8
                            = ((colorBlue << 16) & 0xff0000) | ((colorGreen << 8) & 0x00ff00) | colorRed & 0x0000ff;
                    } else {
                    LAB_00460698:
                        textMemIndex += 2;
                    }
                    continue;
                }
            case HTT_LINK:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(local_cc, L"<LINK=\"%S\">",
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    break;
                } else {
                    local_ec = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    if (param_1 == 1) {
                        DAT_TextManagerObject::instance.field6_0x18 = 1;
                    }
                    textMemIndex += 2;
                    continue;
                }
            case HTT_ENDLINK:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    wcscpy(local_cc, L"<\\LINK>");
                    break;
                } else {
                    local_ec = 0xffffffff;
                    if (param_1 == 1) {
                        DAT_TextManagerObject::instance.field6_0x18 = 0;
                    }
                    continue;
                }
            case HTT_NEWPARAGRAPH:
                if (local_120) {
                    this->lineLayoutTable[iVar20].unknown2 = this->lineLayoutTable[iVar20].unknown1 - local_138;
                    local_120 = local_fc;
                }
                if (this->useAlternateHelpTab && iVar5 == this->activeHelpHotspotIndex) {
                    local_108 = local_130 + iVar20;
                    iVar12 = 0;
                    local_e8 = iVar20;
                    if (param_1 == 1) {
                        if (local_120) {
                            iVar12 = this->lineLayoutTable[iVar20].unknown2 / 2;
                        }
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            this->dialogContentX + iVar12 - 1 + local_138,
                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + iVar20,
                            this->dialogContentX + iVar12 + -1 + local_138,
                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + local_108,
                            COL_DARK_LIME::instance.shortValue);
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            this->dialogContentX + iVar12 + local_138,
                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + iVar20,
                            this->dialogContentX + iVar12 + local_138,
                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + local_108,
                            COL_DARK_LIME::instance.shortValue);
                        local_e4 = 1;
                    }
                }
                iVar20 += 3 + local_130;
                local_f0 = 0;

                int unknown0;
                do {
                    unknown0 = this->lineLayoutTable[iVar20++].unknown0;
                } while (unknown0 == -1);
                local_130 = local_110->lineHeight_0x14;
                iVar12 = local_11c;
                if (this->useAlternateHelpTab != 0) {
                    local_100 = local_11c;
                    if (param_1 == 1) {
                        ++local_134;
                        if (0 < this->unknown_0x2396C && 1 < local_134) {
                            this->activeHelpHotspotIndex = local_10c + local_11c;
                            local_134 = -10000;
                            if (iVar5 <= this->activeHelpHotspotIndex) {
                                this->activeHelpHotspotIndex = iVar5 + -1;
                            }
                            this->unknown_0x2396C = 0;
                        }
                    }
                    iVar12 = iVar5;
                    if ((iVar5 == this->activeHelpHotspotIndex) && (param_1 == 1)) {
                        local_10c = 0;
                        if (this->unknown_0x2396C < 0) {
                            this->activeHelpHotspotIndex = DAT_00df3348::instance + local_11c;
                            if (iVar5 <= this->activeHelpHotspotIndex) {
                                this->activeHelpHotspotIndex = iVar5 + -1;
                            }
                            this->unknown_0x2396C = 0;
                        }
                        local_134 = 0;
                    }
                }
                local_11c = iVar12;
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    wcscpy(local_cc, L"<NEWPARAGRAPH>");
                    break;
                }
                continue;
            case HTT_CENTRE:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    wcscpy(local_cc, L"<CENTRE>");
                    break;
                } else {
                    local_fc = 1;
                    local_120 = 1;
                    continue;
                }
            case HTT_ENDCENTRE:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    wcscpy(local_cc, L"<\\CENTRE>");
                    break;
                } else {
                    local_fc = 0;
                    continue;
                }
            case HTT_TAB: // TODO?: unknown token
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    wcscpy(local_cc, L"<tab>");
                    break;
                } else {
                    if (this->lineLayoutTable[iVar20].unknown1 < local_138 + 30) {
                        local_f0 = 0;
                        if (local_120) {
                            this->lineLayoutTable[iVar20].unknown2 = this->lineLayoutTable[iVar20].unknown1 - local_138;
                            local_120 = local_fc;
                        }
                        do {
                            iVar20 += local_130 + 1;
                            int unknown0;
                            do {
                                unknown0 = this->lineLayoutTable[iVar20++].unknown0;
                            } while (unknown0 == -1);
                        } while (this->lineLayoutTable[iVar20].unknown1 < local_138 + 30);
                        iVar12 = local_11c;
                        if (this->useAlternateHelpTab && param_1 == 1) {
                            ++local_134;
                            local_100 = local_11c;
                            iVar12 = iVar5;
                            if (0 < this->unknown_0x2396C && 1 < local_134) {
                                this->activeHelpHotspotIndex = local_11c + local_10c;
                                local_134 = -10000;
                                if (iVar5 <= this->activeHelpHotspotIndex) {
                                    this->activeHelpHotspotIndex = iVar5 + -1;
                                }
                                this->unknown_0x2396C = 0;
                            }
                        }
                        local_11c = iVar12;
                        local_130 = local_110->lineHeight_0x14;
                    }
                    local_138 += 30;
                    continue;
                }
            case HTT_LINKCOLOUR:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(local_cc, L"<LINKCOLOUR %S>",
                        DAT_UserHelpDefinedData::instance
                            .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                            .name_0x0);
                    textMemIndex += 2;
                    break;
                } else {
                    if (param_1 == 1) {
                        int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        textMemIndex += 2;
                        local_d0
                            = ((DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].b_0xc << 16) & 0xff0000)
                            | ((DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].g_0x8 << 8) & 0x00ff00)
                            | DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].r_0x4 & 0x0000ff;
                    } else {
                        textMemIndex += 2;
                    }
                    continue;
                }
            case HTT_SOUND:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(local_cc, L"<SOUND=\"%S\">",
                        this->soundFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    break;
                } else {
                    if (param_1 == 1 && -1 < iVar20 - this->helpContentScrollOffsetY
                        && iVar20 - this->helpContentScrollOffsetY < this->dialogContentWidth
                        && !this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]) {
                        this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]] = 1;
                    }
                    textMemIndex += 2;
                    continue;
                }
            case HTT_STRING:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(
                        local_cc, L"<STRING %d>", this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
                    textMemIndex += 2;
                    break;
                } else {
                    textMemIndex += 2;
                    continue;
                }
            default:
                pwVar6 = textMemUnion.text;
                goto switchD_00460064_caseD_d;
            case HTT_INCLUDE:
                if (this->helpDialogSubMode == 1) {
                    local_124 = 0xff;
                    local_12c = 0;
                    MACRO_CALL(Global_Func::PrintToDestination)(local_cc, L"<INCLUDE=\"%S\">",
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    break;
                } else {
                    textMemIndex += 2;
                    continue;
                }
            }
            // NOTE: This is either the local text buffer, or the text directly from the text memory...
            pwVar6 = local_cc;
        switchD_00460064_caseD_d:
            if (0x1f < (int)pwVar6) {
                iVar12 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfWideText, local_110)(
                    pwVar6, wcslen((wchar_t*)pwVar6));
                iVar5 = local_11c;
                local_f4 = local_138 + iVar12;
                if (this->lineLayoutTable[iVar20].unknown1 < local_f4) {
                    local_f0 = 0;
                    if (local_120 != 0) {
                        this->lineLayoutTable[iVar20].unknown2 = this->lineLayoutTable[iVar20].unknown1 - local_138;
                        local_120 = local_fc;
                    }
                    iVar20 = iVar20 + 1 + local_130;
                    iVar17 = iVar20 * 6 + 0x2409db4;
                    do {
                        iVar9 = iVar20;
                        local_138 = (dword) * (short*)(iVar17 + 6);
                        iVar17 = iVar17 + 6;
                        iVar20 = iVar9 + 1;
                    } while (local_138 == 0xffffffff);
                    local_130 = local_110->lineHeight_0x14;
                    if (this->useAlternateHelpTab != 0) {
                        local_134 = local_134 + 1;
                        local_100 = local_11c;
                        local_11c = local_114;
                        if ((0 < this->unknown_0x2396C) && (1 < local_134)) {
                            this->activeHelpHotspotIndex = iVar5 + local_10c;
                            local_134 = -10000;
                            if (local_114 <= this->activeHelpHotspotIndex) {
                                this->activeHelpHotspotIndex = local_114 + -1;
                            }
                            this->unknown_0x2396C = 0;
                        }
                    }
                    local_e0 = this->lineLayoutTable + iVar9 * 3 + 4;
                    local_f4 = iVar12 + local_138;
                    if ((int)*local_e0 < (int)local_f4) {
                        local_f8 = 0;
                        if (local_120 != 0) {
                            local_f8 = this->lineLayoutTable[iVar9 + 1].unknown2 / 2;
                        }
                        pWVar11 = pwVar6 + 1;
                        do {
                            WVar3 = *pwVar6;
                            pwVar6 = pwVar6 + 1;
                        } while (WVar3 != L'\0');
                        local_d4 = (int)pwVar6 - (int)pWVar11 >> 1;
                        local_118 = 0;
                        if (0 < local_d4) {
                            local_104 = local_114;
                            do {
                                local_f4 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, local_110)(
                                    textMemUnion.text[local_118]);
                                if ((int)*local_e0 < (int)(local_138 + local_f4)) {
                                    do {
                                        iVar5 = local_11c;
                                        if (local_120 != 0) {
                                            this->lineLayoutTable[iVar20].unknown2 = *local_e0 - local_138;
                                            local_120 = local_fc;
                                        }
                                        iVar20 = iVar20 + local_130 + 1;
                                        if (this->useAlternateHelpTab && param_1 == 1) {
                                            local_134 = local_134 + 1;
                                            local_100 = local_11c;
                                            local_11c = local_104;
                                            if ((0 < this->unknown_0x2396C) && (1 < local_134)) {
                                                this->activeHelpHotspotIndex = iVar5 + local_10c;
                                                local_134 = -10000;
                                                if (local_104 <= this->activeHelpHotspotIndex) {
                                                    this->activeHelpHotspotIndex = local_104 + -1;
                                                }
                                                this->unknown_0x2396C = 0;
                                            }
                                        }
                                        iVar5 = iVar20 * 6 + 0x2409db4;
                                        do {
                                            iVar12 = iVar20;
                                            local_138 = (dword) * (short*)(iVar5 + 6);
                                            iVar5 = iVar5 + 6;
                                            iVar20 = iVar12 + 1;
                                        } while (local_138 == 0xffffffff);
                                        if (local_120) {
                                            local_f8 = this->lineLayoutTable[iVar12 + 1].unknown2 / 2;
                                        }
                                        local_e0 = this->lineLayoutTable + iVar12 * 3 + 4;
                                    } while (this->lineLayoutTable[iVar12].unknown1 < local_f4 + local_138);
                                }
                                dVar14 = local_138;
                                if (!this->useAlternateHelpTab || local_104 != this->activeHelpHotspotIndex) {
                                    if (param_1 == 1)
                                        goto LAB_00460f59;
                                } else {
                                    iVar5 = iVar20 + local_130;
                                    local_108 = iVar5;
                                    local_e8 = iVar20;
                                    if (param_1 == 1) {
                                        if (local_12c) {
                                            local_10c = (local_118 - local_11c) + local_114;
                                            if (this->unknown_0x2396C < 0) {
                                                this->activeHelpHotspotIndex = DAT_00df3348::instance + local_100;
                                                if (local_11c <= this->activeHelpHotspotIndex) {
                                                    this->activeHelpHotspotIndex = local_11c - 1;
                                                }
                                                this->unknown_0x2396C = 0;
                                            }
                                            local_134 = 0;
                                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                                DAT_PencilRenderCore::ptr)(
                                                this->dialogContentX + local_f8 - 1 + local_138,
                                                this->dialogContentY - this->helpContentScrollOffsetY + -1 + iVar20,
                                                this->dialogContentX + local_f8 - 1 + local_138,
                                                this->dialogContentY - this->helpContentScrollOffsetY + 1 + iVar5,
                                                COL_DARK_LIME::instance.shortValue);
                                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                                DAT_PencilRenderCore::ptr)(this->dialogContentX + local_f8 + dVar14,
                                                this->dialogContentY - this->helpContentScrollOffsetY - 1 + iVar20,
                                                this->dialogContentX + local_f8 + dVar14,
                                                this->dialogContentY - this->helpContentScrollOffsetY + 1 + iVar5,
                                                COL_DARK_LIME::instance.shortValue);
                                            local_e4 = 1;
                                        }
                                    LAB_00460f59:
                                        iVar5 = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, local_110)(
                                            textMemUnion.text[local_118], this->dialogContentX + local_f8 + local_138,
                                            this->dialogContentY - this->helpContentScrollOffsetY + iVar20, local_124,
                                            0);
                                        local_f0 = 1;
                                        BVar13 = MACRO_CALL_MEMBER(
                                            Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                            this->dialogContentX + local_f8 + local_138 - this->helpContentScrollX,
                                            this->dialogContentY - this->helpContentScrollOffsetY + iVar20
                                                - this->helpContentScrollY,
                                            iVar5 - this->dialogContentX + local_f8 + local_138, local_130 + 2);
                                        if (BVar13 != FALSE) {
                                            if (local_12c == 0) {
                                                this->unknown_0x23964 = local_114;
                                            } else {
                                                this->unknown_0x23964 = local_104;
                                                this->unknown_0x23968 = local_ec;
                                            }
                                        }
                                    }
                                }
                                local_138 = local_138 + local_f4;
                                local_104 = local_104 + 1;
                                local_118 = local_118 + 1;
                            } while (local_118 < local_d4);
                        }
                        continue;
                    }
                }
                iVar5 = this->dialogContentX + local_138;
                local_104 = (this->dialogContentY - this->helpContentScrollOffsetY) + iVar20;
                if (local_120 != 0) {
                    iVar5 += this->lineLayoutTable[iVar20].unknown2 / 2;
                }
                local_d4 = wcslen((wchar_t*)pwVar6);
                for (int i = 0; i < local_d4; ++i) {
                    local_f8 = local_114 - local_11c;
                    if ((this->useAlternateHelpTab == 0) || (i + local_114 != this->activeHelpHotspotIndex)) {
                        if (param_1 != 1)
                            goto LAB_00461201;
                    LAB_0046117a:
                        local_f0 = 1;
                        iVar12 = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, local_110)(
                            textMemUnion.text[i], iVar5, local_104, local_124, 0);
                        BVar13 = MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                            iVar5 - this->helpContentScrollX, local_104 - this->helpContentScrollY, iVar12 - iVar5,
                            local_130 + 2);
                        if (BVar13 != FALSE) {
                            if (local_12c == 0) {
                                this->unknown_0x23964 = local_114;
                            } else {
                                this->unknown_0x23964 = i + local_114;
                                this->unknown_0x23968 = local_ec;
                            }
                        }
                    } else {
                        if (param_1 == 1 && local_12c) {
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(iVar5 + -1, local_104 - 1, iVar5 + -1,
                                local_104 + 1 + local_130, COL_DARK_LIME::instance.shortValue);
                            MACRO_CALL_MEMBER(
                                UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(iVar5,
                                local_104 - 1, iVar5, local_104 + 1 + local_130, COL_DARK_LIME::instance.shortValue);
                            local_e4 = 1;
                        }
                        local_108 = iVar20 + local_130;
                        local_e8 = iVar20;
                        if (param_1 == 1) {
                            local_10c = local_f8 + i;
                            local_134 = 0;
                            if (this->unknown_0x2396C < 0 && local_12c) {
                                this->activeHelpHotspotIndex = local_100 + DAT_00df3348::instance;
                                if (local_11c <= this->activeHelpHotspotIndex) {
                                    this->activeHelpHotspotIndex = local_11c + -1;
                                }
                                this->unknown_0x2396C = 0;
                            }
                            goto LAB_0046117a;
                        }
                    LAB_00461201:
                        dVar14
                            = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, local_110)(textMemUnion.text[i]);
                        iVar12 = iVar5 + dVar14;
                    }
                    iVar5 = iVar12;
                }
                local_138 = local_f4;
            }
        }
    }

}
}
