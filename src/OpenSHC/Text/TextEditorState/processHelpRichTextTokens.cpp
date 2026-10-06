// disable deprecation warnings for wcscpy and wcscat
#pragma warning(disable : 4996)

#include "../TextEditorState.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextPicturePositionToken.hpp"
#include "OpenSHC/wstring-literals.hpp"

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
        int value;
        wchar_t* text;
        HelpTextToken helpToken;
        Enums::HelpTextPicturePositionToken picturePositionToken;
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x0045FDC0
    int TextEditorState::processHelpRichTextTokens(int param_1)
    {
        int imageCount;
        BGR24 color;
        int wordLength;
        BGR24 linkColor;
        BOOL local_f0;
        int currentLinkId;
        int lineStartY;
        BOOL local_e4;
        int local_100;
        BOOL centreActive;
        int textMemIndex;
        int leftPosition;
        int local_134;
        int currentFontLineHeight;
        int local_12c;
        TextMemUnion textToRender;
        BGR24 charColor;
        BOOL centerCurrentLine;
        int local_11c;
        int local_114;
        FontSizeClass* currentFontClass;
        int local_10c;
        int lineEndY;

        wchar_t wideTextBuffer[100];

        int local_f8;
        // shared scratch value: picture position token, end position of the current word, width of the current char
        int local_f4;
        int index;

        currentLinkId = -1;
        textMemIndex = 0;
        currentFontClass = DAT_TextManagerObject::instance.fontSizeClassArray + 17;
        currentFontLineHeight = currentFontClass->lineHeight_0x14;
        local_f0 = FALSE;
        color = 0xccfaff;
        linkColor = 0x8bcf84;
        imageCount = -1;
        centreActive = FALSE;
        centerCurrentLine = FALSE;
        lineStartY = 0;
        lineEndY = 0;
        local_11c = 0;
        local_100 = 0;
        local_10c = 0;
        local_e4 = FALSE;
        local_134 = -10000;
        if (this->helpDialogVariant == 2 || this->isCustomTextMode) {
            color = 0xc2f0eb;
        }
        if (!this->isTextHelpDialogMode) {
            return 1;
        }
        this->field49_0x23964 = -1;
        this->currentLinkId = -1;
        if (this->field51_0x2396c) {
            DAT_00df334c::instance = 1;
        }
        if (this->activeHelpHotspotIndex < 0) {
            this->activeHelpHotspotIndex = 0;
        }
        if (this->activeHelpHotspotIndex > this->customHelpTextLength) {
            this->activeHelpHotspotIndex = this->customHelpTextLength;
        }
        int lineY = -1;
        do {
            leftPosition = this->lineLayoutTable[++lineY].leftBorder;
        } while (leftPosition == -1);
        while (true) {
            do {
                charColor = color;
                local_12c = TRUE;
                if (0 <= currentLinkId) {
                    charColor = linkColor;
                }
                index = textMemIndex;
                local_114 = index;
                textToRender.value
                    = MACRO_CALL_MEMBER(TextEditorState_Func::getWideCharOrWideCharPointer, this)(&textMemIndex);
                if (this->useAlternateHelpTab && textToRender.value < L' '
                    && textToRender.helpToken != Enums::HTT_NEWPARAGRAPH && local_114 == this->activeHelpHotspotIndex) {
                    lineStartY = lineY;
                    lineEndY = lineY + currentFontLineHeight;
                    if (param_1 == 1) {
                        int xModify = 0;
                        if (centerCurrentLine) {
                            xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                        }
                        local_10c = local_114 - local_11c;
                        if (this->field51_0x2396c < 0) {
                            this->activeHelpHotspotIndex = local_100 + DAT_00df3348::instance;
                            if (this->activeHelpHotspotIndex >= local_11c) {
                                this->activeHelpHotspotIndex = local_11c - 1;
                            }
                            this->field51_0x2396c = 0;
                        }
                        local_134 = 0;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            this->dialogContentX + xModify - 1 + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                            this->dialogContentX + xModify - 1 + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                            COL_DARK_LIME::instance.shortValue);
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            this->dialogContentX + xModify + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                            this->dialogContentX + xModify + leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                            COL_DARK_LIME::instance.shortValue);

                        local_e4 = TRUE;
                    }
                }

                switch (textToRender.helpToken) {
                case Enums::HTT_PIC:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__PIC__d__S__005a583c,
                            this->DAT_PointerToTemporaryTextMemory[index],
                            this->graphicFileNames[this->DAT_PointerToTemporaryTextMemory[index]]);
                        Enums::HelpTextPicturePositionToken positionToken
                            = (Enums::HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[index + 1];
                        ++index;
                        switch (positionToken) {
                        case Enums::HTPPT_LEFT:
                            wcscat(wideTextBuffer, u_LEFT__005a5494);
                            index += 2;
                            textMemIndex = index;
                            textToRender.text = wideTextBuffer;
                            continue;
                        case Enums::HTPPT_RIGHT:
                            wcscat(wideTextBuffer, u_RIGHT__005a5484);
                            index += 2;
                            textMemIndex = index;
                            textToRender.text = wideTextBuffer;
                            continue;
                        case Enums::HTPPT_CENTRE:
                            wcscat(wideTextBuffer, u_CENTRE__005a5474);
                            index += 2;
                            textMemIndex = index;
                            textToRender.text = wideTextBuffer;
                            continue;
                        case Enums::HTPPT_HERE:
                            wcscat(wideTextBuffer, u_HERE__005a5468);
                            index += 2;
                            textMemIndex = index;
                            textToRender.text = wideTextBuffer;
                            continue;
                        default:
                            break;
                        }
                    } else {
                        ++imageCount;

                        int imageIndex;
                        if (param_1 == 1) {
                            if (this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] != Enums::HTPPT_HERE) {
                                goto skipPicture;
                            }
                            imageIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        } else {
                            if (param_1 != 0) {
                                goto skipPicture;
                            }
                            if (imageCount != this->imageHotspotCount
                                && this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] != Enums::HTPPT_HERE) {
                                goto skipPicture;
                            }
                            imageIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                            if (imageCount == this->imageHotspotCount) {
                                this->imageHotspotTable[this->imageHotspotCount].yPos = lineY + 25;
                                this->imageHotspotTable[this->imageHotspotCount].imageIndex = imageIndex;
                                this->imageHotspotTable[this->imageHotspotCount].linkId = currentLinkId;
                            }
                        }

                        local_f4 = this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                        ++textMemIndex;
                        int imageWidth = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].width;
                        int imageHeight = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].height;
                        switch (local_f4) {
                        case Enums::HTPPT_LEFT: {
                            this->imageHotspotTable[this->imageHotspotCount].xPos
                                = this->lineLayoutTable[lineY].leftBorder;
                            int newLeftBorder = this->lineLayoutTable[lineY].leftBorder + 25 + imageWidth;
                            for (int i = 0; i < imageHeight + 50; ++i) {
                                this->lineLayoutTable[lineY + i].leftBorder = newLeftBorder;
                            }
                            break;
                        }
                        case Enums::HTPPT_RIGHT: {
                            this->imageHotspotTable[this->imageHotspotCount].xPos
                                = this->lineLayoutTable[lineY].rightBorder - imageWidth;
                            int newRightBorder = this->lineLayoutTable[lineY].rightBorder - imageWidth - 25;
                            for (int i = 0; i < imageHeight + 50; ++i) {
                                this->lineLayoutTable[lineY + i].rightBorder = newRightBorder;
                            }
                            break;
                        }
                        case Enums::HTPPT_CENTRE:
                            this->imageHotspotTable[this->imageHotspotCount].xPos
                                = (this->dialogContentWidth - imageWidth) / 2;
                            for (int i = 0; i < imageHeight + 50; ++i) {
                                this->lineLayoutTable[lineY + i].leftBorder = -1;
                            }
                            break;
                        case Enums::HTPPT_HERE: {
                            int const hereWidth = imageWidth + 3;
                            if (hereWidth + leftPosition > this->lineLayoutTable[lineY].rightBorder) {
                                local_f0 = FALSE;
                                if (centerCurrentLine) {
                                    this->lineLayoutTable[lineY].widthForCentering
                                        = this->lineLayoutTable[lineY].rightBorder - leftPosition;
                                    centerCurrentLine = centreActive;
                                }
                                do {
                                    lineY += currentFontLineHeight + 1;
                                    do {
                                        leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                                    } while (leftPosition == -1);
                                } while (leftPosition + hereWidth > this->lineLayoutTable[lineY].rightBorder);
                                if (this->useAlternateHelpTab && param_1 == 1) {
                                    local_100 = local_11c;
                                    local_11c = local_114;
                                    ++local_134;
                                    if (0 < this->field51_0x2396c && 2 <= local_134) {
                                        local_134 = -10000;
                                        this->activeHelpHotspotIndex = local_100 + local_10c;
                                        if (this->activeHelpHotspotIndex >= local_114) {
                                            this->activeHelpHotspotIndex = local_114 - 1;
                                        }
                                        this->field51_0x2396c = 0;
                                    }
                                }
                                currentFontLineHeight = currentFontClass->lineHeight_0x14;
                            }
                            if (imageHeight > currentFontLineHeight) {
                                currentFontLineHeight = imageHeight;
                            }
                            leftPosition += hereWidth;
                            if (param_1 != 1 && imageCount == this->imageHotspotCount) {
                                this->imageHotspotTable[this->imageHotspotCount].xPos = leftPosition - hereWidth;
                                this->imageHotspotTable[this->imageHotspotCount].yPos = lineY;
                                ++this->imageHotspotCount;
                            }
                            break;
                        }
                        }
                        textMemIndex += 2;
                        if (local_f4 == Enums::HTPPT_HERE || param_1) {
                            continue;
                        }
                        ++this->imageHotspotCount;
                        DAT_TextManagerObject::instance.field6_0x18 = 0;
                        return FALSE;

                    skipPicture:
                        textMemIndex += 3;
                        continue;
                    }
                    break;
                case Enums::HTT_FONT:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(
                            wideTextBuffer, u__FONT__d__005a5454, this->DAT_PointerToTemporaryTextMemory[index]);
                    } else {
                        int fontSize = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        if (fontSize < 15) {
                            fontSize += 5;
                        }
                        textMemIndex += 2;
                        currentFontClass = &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize];
                        if (currentFontClass->lineHeight_0x14 > currentFontLineHeight || !local_f0) {
                            currentFontLineHeight = currentFontClass->lineHeight_0x14;
                        }
                        continue;
                    }
                    break;
                case Enums::HTT_COLOUR:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__COLOUR__S__005a5824,
                            DAT_UserHelpDefinedData::instance
                                .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[index]]
                                .name_0x0);
                    } else {
                        if (param_1 == 1) {
                            int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];

                            uint colorRed;
                            uint colorGreen;
                            uint colorBlue;
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
                            color = RGB(colorRed, colorGreen, colorBlue);
                        } else {
                            textMemIndex += 2;
                        }
                        continue;
                    }
                    break;
                case Enums::HTT_LINKCOLOUR:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINKCOLOUR__S__005a5804,
                            DAT_UserHelpDefinedData::instance
                                .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[index]]
                                .name_0x0);
                    } else {
                        if (param_1 == 1) {
                            int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                            textMemIndex += 2;
                            linkColor = RGB(DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].r_0x4,
                                DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].g_0x8,
                                DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].b_0xc);
                        } else {
                            textMemIndex += 2;
                        }
                        continue;
                    }
                    break;
                case Enums::HTT_LINK:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINK_S__005a57ec,
                            DAT_UserHelpDefinedData::instance
                                .HelpSections[this->DAT_PointerToTemporaryTextMemory[index]]);
                    } else {
                        currentLinkId = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        if (param_1 == 1) {
                            DAT_TextManagerObject::instance.field6_0x18 = 1;
                        }
                        textMemIndex += 2;
                        continue;
                    }
                    break;
                case Enums::HTT_INCLUDE:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__INCLUDE_S__005a57cc,
                            DAT_UserHelpDefinedData::instance
                                .HelpSections[this->DAT_PointerToTemporaryTextMemory[index]]);
                    } else {
                        textMemIndex += 2;
                        continue;
                    }
                    break;
                case Enums::HTT_SOUND:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__SOUND_S__005a57b0,
                            this->soundFileNames[this->DAT_PointerToTemporaryTextMemory[index]]);
                    } else {
                        if (param_1 == 1) {
                            int const visibleY = lineY - this->helpContentScrollOffsetY;
                            if (0 <= visibleY && visibleY < this->dialogContentHeight
                                && !this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]) {
                                this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]] = 1;
                            }
                        }
                        textMemIndex += 2;
                        continue;
                    }
                    break;
                case Enums::HTT_ENDLINK:
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__LINK__005a53d4);
                        textToRender.text = wideTextBuffer;
                        continue;
                    } else {
                        currentLinkId = -1;
                        if (param_1 == 1) {
                            DAT_TextManagerObject::instance.field6_0x18 = 0;
                        }
                        continue;
                    }
                    break;
                case Enums::HTT_STRING:
                    if (this->helpDialogSubMode == 1) {
                        index = textMemIndex;
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(
                            wideTextBuffer, u__STRING__d__005a5358, this->DAT_PointerToTemporaryTextMemory[index]);
                    } else {
                        textMemIndex += 2;
                        continue;
                    }
                    break;
                case Enums::HTT_CENTRE:
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__CENTRE__005a539c);
                        textToRender.text = wideTextBuffer;
                        continue;
                    } else {
                        centreActive = TRUE;
                        centerCurrentLine = TRUE;
                        continue;
                    }
                    break;
                case Enums::HTT_ENDCENTRE:
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__CENTRE__005a5388);
                        textToRender.text = wideTextBuffer;
                        continue;
                    } else {
                        centreActive = FALSE;
                        continue;
                    }
                    break;
                case Enums::HTT_NEWPARAGRAPH:
                    if (centerCurrentLine) {
                        this->lineLayoutTable[lineY].widthForCentering
                            = this->lineLayoutTable[lineY].rightBorder - leftPosition;
                        centerCurrentLine = centreActive;
                    }
                    if (this->useAlternateHelpTab && local_114 == this->activeHelpHotspotIndex) {
                        lineEndY = currentFontLineHeight + lineY;
                        int xModify = 0;
                        lineStartY = lineY;
                        if (param_1 == 1) {
                            if (centerCurrentLine) {
                                xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                            }
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(this->dialogContentX + xModify - 1 + leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                this->dialogContentX + xModify - 1 + leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                                COL_DARK_LIME::instance.shortValue);
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(this->dialogContentX + xModify + leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                this->dialogContentX + xModify + leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                                COL_DARK_LIME::instance.shortValue);

                            local_e4 = TRUE;
                        }
                    }
                    lineY += 3 + currentFontLineHeight;
                    local_f0 = FALSE;
                    do {
                        leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                    } while (leftPosition == -1);
                    currentFontLineHeight = currentFontClass->lineHeight_0x14;

                    if (this->useAlternateHelpTab) {
                        local_100 = local_11c;
                        local_11c = local_114;
                        if (param_1 == 1) {
                            ++local_134;
                            if (0 < this->field51_0x2396c && 2 <= local_134) {
                                local_134 = -10000;
                                this->activeHelpHotspotIndex = local_10c + local_100;
                                if (this->activeHelpHotspotIndex >= local_114) {
                                    this->activeHelpHotspotIndex = local_114 - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                        }
                        if (local_114 == this->activeHelpHotspotIndex && param_1 == 1) {
                            local_10c = 0;
                            if (this->field51_0x2396c < 0) {
                                this->activeHelpHotspotIndex = DAT_00df3348::instance + local_100;
                                if (this->activeHelpHotspotIndex >= local_114) {
                                    this->activeHelpHotspotIndex = local_114 - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                            local_134 = 0;
                        }
                    }
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__NEWPARAGRAPH__005a5790);
                        textToRender.text = wideTextBuffer;
                        continue;
                    } else {
                        continue;
                    }
                    break;
                case Enums::HTT_TAB: // TODO?: unknown token
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__tab__005a5784);
                        textToRender.text = wideTextBuffer;
                        continue;
                    } else {
                        if (leftPosition + 30 > this->lineLayoutTable[lineY].rightBorder) {
                            local_f0 = FALSE;
                            if (centerCurrentLine) {
                                this->lineLayoutTable[lineY].widthForCentering
                                    = this->lineLayoutTable[lineY].rightBorder - leftPosition;
                                centerCurrentLine = centreActive;
                            }
                            do {
                                lineY += currentFontLineHeight + 1;
                                do {
                                    leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                                } while (leftPosition == -1);
                            } while (leftPosition + 30 > this->lineLayoutTable[lineY].rightBorder);

                            if (this->useAlternateHelpTab && param_1 == 1) {
                                local_100 = local_11c;
                                local_11c = local_114;
                                ++local_134;
                                if (0 < this->field51_0x2396c && 2 <= local_134) {
                                    local_134 = -10000;
                                    this->activeHelpHotspotIndex = local_100 + local_10c;
                                    if (this->activeHelpHotspotIndex >= local_114) {
                                        this->activeHelpHotspotIndex = local_114 - 1;
                                    }
                                    this->field51_0x2396c = 0;
                                }
                            }
                            currentFontLineHeight = currentFontClass->lineHeight_0x14;
                        }
                        leftPosition += 30;
                        continue;
                    }
                    break;
                case (wchar_t*)0: // TODO?: unknown token, or just NULL, meaning end?
                    if (param_1 == 0) {
                        this->topVisibleLineIndex = lineY + currentFontLineHeight - 1;
                        do {
                            ++this->topVisibleLineIndex;
                            if (this->lineLayoutTable[this->topVisibleLineIndex].leftBorder == 25
                                && this->lineLayoutTable[this->topVisibleLineIndex].rightBorder
                                    == this->dialogContentWidth - 25) {
                                break;
                            }
                        } while (this->topVisibleLineIndex < 20000);
                        this->topVisibleLineIndex += 5;
                        if (this->useAlternateHelpTab) {
                            if (lineStartY < this->helpContentScrollOffsetY) {
                                this->helpContentScrollOffsetY = lineStartY;
                            }
                            if (lineEndY > this->helpContentScrollOffsetY + this->dialogContentHeight) {
                                this->helpContentScrollOffsetY = (lineEndY - this->dialogContentHeight) + 5;
                            }
                        }
                    } else {
                        if (this->useAlternateHelpTab) {
                            DAT_00df3348::instance = local_10c;
                            if (0 < this->field51_0x2396c && local_134 == 1) {
                                this->activeHelpHotspotIndex = local_10c + local_11c;
                                if (this->activeHelpHotspotIndex > this->customHelpTextLength) {
                                    this->activeHelpHotspotIndex = this->customHelpTextLength;
                                }
                                this->field51_0x2396c = 0;
                            }
                            if (!local_e4 && this->activeHelpHotspotIndex && DAT_00df334c::instance) {
                                --this->activeHelpHotspotIndex;
                                this->field52_0x23970 = 0;
                            } else {
                                DAT_00df334c::instance = 0;
                            }
                        }
                    }
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                default:
                    continue;
                }
                index += 2;
                textMemIndex = index;
                textToRender.text = wideTextBuffer;
            } while (textToRender.value < L' ');

            int textWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfWideText, currentFontClass)(
                textToRender.text, wcslen(textToRender.text));
            local_f4 = leftPosition + textWidth;
            if (local_f4 > this->lineLayoutTable[lineY].rightBorder) {
                local_f0 = FALSE;
                if (centerCurrentLine) {
                    this->lineLayoutTable[lineY].widthForCentering
                        = this->lineLayoutTable[lineY].rightBorder - leftPosition;
                    centerCurrentLine = centreActive;
                }
                lineY += 1 + currentFontLineHeight;
                do {
                    leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                } while (leftPosition == -1);
                currentFontLineHeight = currentFontClass->lineHeight_0x14;
                if (this->useAlternateHelpTab) {
                    local_100 = local_11c;
                    local_11c = local_114;
                    ++local_134;
                    if (0 < this->field51_0x2396c && 2 <= local_134) {
                        local_134 = -10000;
                        this->activeHelpHotspotIndex = local_100 + local_10c;
                        if (this->activeHelpHotspotIndex >= local_114) {
                            this->activeHelpHotspotIndex = local_114 - 1;
                        }
                        this->field51_0x2396c = 0;
                    }
                }
                short* rightBorder = &this->lineLayoutTable[lineY].rightBorder;
                local_f4 = textWidth + leftPosition;
                if (local_f4 > *rightBorder) {
                    local_f8 = 0;
                    if (centerCurrentLine) {
                        local_f8 = this->lineLayoutTable[lineY].widthForCentering / 2;
                    }
                    wordLength = wcslen(textToRender.text);
                    for (int i = 0; i < wordLength; ++i) {
                        local_f4 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, currentFontClass)(
                            textToRender.text[i]);
                        while (leftPosition + local_f4 > *rightBorder) {
                            if (centerCurrentLine) {
                                this->lineLayoutTable[lineY].widthForCentering = *rightBorder - leftPosition;
                                centerCurrentLine = centreActive;
                            }
                            lineY += currentFontLineHeight + 1;
                            if (this->useAlternateHelpTab && param_1 == 1) {
                                local_100 = local_11c;
                                local_11c = local_114 + i;
                                ++local_134;
                                if (0 < this->field51_0x2396c && 2 <= local_134) {
                                    local_134 = -10000;
                                    this->activeHelpHotspotIndex = local_100 + local_10c;
                                    if (this->activeHelpHotspotIndex >= local_114 + i) {
                                        this->activeHelpHotspotIndex = local_114 + i - 1;
                                    }
                                    this->field51_0x2396c = 0;
                                }
                            }
                            do {
                                leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                            } while (leftPosition == -1);
                            if (centerCurrentLine) {
                                local_f8 = this->lineLayoutTable[lineY].widthForCentering / 2;
                            }
                            rightBorder = &this->lineLayoutTable[lineY].rightBorder;
                        }
                        if (this->useAlternateHelpTab && local_114 + i == this->activeHelpHotspotIndex) {
                            lineStartY = lineY;
                            lineEndY = lineY + currentFontLineHeight;
                            if (param_1 == 1) {
                                if (local_12c) {
                                    local_10c = (i - local_11c) + local_114;
                                    if (this->field51_0x2396c < 0) {
                                        this->activeHelpHotspotIndex = DAT_00df3348::instance + local_100;
                                        if (this->activeHelpHotspotIndex >= local_11c) {
                                            this->activeHelpHotspotIndex = local_11c - 1;
                                        }
                                        this->field51_0x2396c = 0;
                                    }
                                    local_134 = 0;
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                        DAT_PencilRenderCore::ptr)(this->dialogContentX + local_f8 - 1 + leftPosition,
                                        this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                        this->dialogContentX + local_f8 - 1 + leftPosition,
                                        this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                                        COL_DARK_LIME::instance.shortValue);
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                        DAT_PencilRenderCore::ptr)(this->dialogContentX + local_f8 + leftPosition,
                                        this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                        this->dialogContentX + local_f8 + leftPosition,
                                        this->dialogContentY - this->helpContentScrollOffsetY + 1 + lineEndY,
                                        COL_DARK_LIME::instance.shortValue);

                                    local_e4 = TRUE;
                                }
                            }
                        }
                        if (param_1 == 1) {
                            int const charXPos = this->dialogContentX + local_f8 + leftPosition;
                            int const charYPos = this->dialogContentY - this->helpContentScrollOffsetY + lineY;
                            int const newCharXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar,
                                currentFontClass)(textToRender.text[i], charXPos, charYPos, charColor, 0);
                            local_f0 = TRUE;
                            if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                    charXPos - this->helpContentScrollX, charYPos - this->helpContentScrollY,
                                    newCharXPos - charXPos, currentFontLineHeight + 2)) {
                                if (local_12c) {
                                    this->field49_0x23964 = local_114 + i;
                                    this->currentLinkId = currentLinkId;
                                } else {
                                    this->field49_0x23964 = local_114;
                                }
                            }
                        }

                        leftPosition += local_f4;
                    }
                    continue;
                }
            }

            int charXPos = this->dialogContentX + leftPosition;
            int charYPos = (this->dialogContentY - this->helpContentScrollOffsetY) + lineY;
            if (centerCurrentLine) {
                charXPos += this->lineLayoutTable[lineY].widthForCentering / 2;
            }
            wordLength = wcslen(textToRender.text);
            for (int i = 0; i < wordLength; ++i) {
                local_f8 = local_114 - local_11c;

                if (this->useAlternateHelpTab && i + local_114 == this->activeHelpHotspotIndex) {
                    if (param_1 == 1 && local_12c) {
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            charXPos - 1, charYPos - 1, charXPos - 1, charYPos + 1 + currentFontLineHeight,
                            COL_DARK_LIME::instance.shortValue);
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            charXPos, charYPos - 1, charXPos, charYPos + 1 + currentFontLineHeight,
                            COL_DARK_LIME::instance.shortValue);
                        local_e4 = TRUE;
                    }
                    lineStartY = lineY;
                    lineEndY = lineY + currentFontLineHeight;
                    if (param_1 == 1) {
                        local_134 = 0;
                        local_10c = local_f8 + i;
                        if (this->field51_0x2396c < 0 && local_12c) {
                            this->activeHelpHotspotIndex = local_100 + DAT_00df3348::instance;
                            if (this->activeHelpHotspotIndex >= local_11c) {
                                this->activeHelpHotspotIndex = local_11c - 1;
                            }
                            this->field51_0x2396c = 0;
                        }
                    }
                }

                if (param_1 == 1) {
                    local_f0 = TRUE;
                    int oldCharPos = charXPos;
                    charXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                        textToRender.text[i], charXPos, charYPos, charColor, 0);
                    if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                            oldCharPos - this->helpContentScrollX, charYPos - this->helpContentScrollY,
                            charXPos - oldCharPos, currentFontLineHeight + 2)) {
                        if (local_12c) {
                            this->field49_0x23964 = i + local_114;
                            this->currentLinkId = currentLinkId;
                        } else {
                            this->field49_0x23964 = local_114;
                        }
                    }
                } else {
                    charXPos += MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, currentFontClass)(
                        textToRender.text[i]);
                }
            }
            leftPosition = local_f4;
        }
    }
}
}
