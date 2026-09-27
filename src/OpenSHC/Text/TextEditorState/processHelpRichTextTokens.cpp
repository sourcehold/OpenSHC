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

// Even now, part of the logic after the L' ' is pulled into the switch, but not the right way
// the position after endlink might be related to being the first position that has no +2 on the the memindex, but still
// sets the wideBuffer; no idea how to trigger it, though

// It is possible to move the pulled section by messing with certain branches, however, this likely really requires the
// right structure over all cases, it might even involve mixed structures, since a human wrote it

// most unmarked things are related to the alternate help text, which only seems to be active for the map editor text,
// which is strange. So either this is a left over, or maybe the help text editor hat a switch for this in some way

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
        wchar_t wideTextBuffer[100];

        int local_f8;

        int currentLinkId = -1;
        int textMemIndex = 0;
        FontSizeClass* currentFontClass = DAT_TextManagerObject::instance.fontSizeClassArray + 17;
        int currentFontLineHeight = currentFontClass->lineHeight_0x14;
        BOOL local_f0 = FALSE;
        BGR24 color = 0xccfaff;
        BGR24 linkColor = 0x8bcf84;
        int imageCount = -1;
        BOOL centreActive = FALSE;
        BOOL centerCurrentLine = FALSE;
        int lineStartY = 0;
        int lineEndY = 0;
        int local_11c = 0;
        int local_100 = 0;
        int local_10c = 0;
        BOOL local_e4 = FALSE;
        int local_134 = -10000;
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
        int leftPosition;
        do {
            leftPosition = this->lineLayoutTable[++lineY].leftBorder;
        } while (leftPosition == -1);

        bool abortProcessing;
        do {
            abortProcessing = false;

            TextMemUnion textToRender;
            int local_114;
            BGR24 charColor;
            // false if text debug view token handled (this->helpDialogSubMode == 1), maybe related to input?
            BOOL local_12c;
            do {
                charColor = color;
                local_12c = TRUE;
                if (0 <= currentLinkId) {
                    charColor = linkColor;
                }
                local_114 = textMemIndex;
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
                        int xPos = this->dialogContentX + xModify;
                        int yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            xPos + leftPosition - 1, yPos + lineY - 1, xPos + leftPosition - 1, yPos + lineEndY + 1,
                            COL_DARK_LIME::instance.shortValue);
                        xPos = this->dialogContentX + xModify;
                        yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            xPos + leftPosition, yPos + lineY - 1, xPos + leftPosition, yPos + lineEndY + 1,
                            COL_DARK_LIME::instance.shortValue);
                        local_e4 = TRUE;
                    }
                }

                switch (textToRender.helpToken) {
                case Enums::HTT_PIC: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__PIC__d__S__005a583c,
                            this->DAT_PointerToTemporaryTextMemory[textMemIndex],
                            this->graphicFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                        Enums::HelpTextPicturePositionToken positionToken
                            = (Enums::HelpTextPicturePositionToken)this
                                  ->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                        ++textMemIndex;
                        switch (positionToken) {
                        case Enums::HTPPT_LEFT:
                            wcscat(wideTextBuffer, u_LEFT__005a5494);
                            break;
                        case Enums::HTPPT_RIGHT:
                            wcscat(wideTextBuffer, u_RIGHT__005a5484);
                            break;
                        case Enums::HTPPT_CENTRE:
                            wcscat(wideTextBuffer, u_CENTRE__005a5474);
                            break;
                        case Enums::HTPPT_HERE:
                            wcscat(wideTextBuffer, u_HERE__005a5468);
                            break;
                        }
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    ++imageCount;

                    bool validImageIndex = false;
                    int imageIndex;
                    if (param_1 == 1 && this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] == Enums::HTPPT_HERE) {
                        imageIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        validImageIndex = true;
                    } else if (!param_1
                        && (imageCount == this->imageHotspotCount
                            || this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] == Enums::HTPPT_HERE)) {
                        imageIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        if (imageCount == this->imageHotspotCount) {
                            this->imageHotspotTable[this->imageHotspotCount].yPos = lineY + 25;
                            this->imageHotspotTable[this->imageHotspotCount].imageIndex = imageIndex;
                            this->imageHotspotTable[this->imageHotspotCount].linkId = currentLinkId;
                        }
                        validImageIndex = true;
                    }
                    if (validImageIndex) {
                        Enums::HelpTextPicturePositionToken positionToken
                            = (Enums::HelpTextPicturePositionToken)this
                                  ->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                        ++textMemIndex;
                        int imageWidth = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].width;
                        int imageHeight = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].height;
                        switch (positionToken) {
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
                        case Enums::HTPPT_HERE:
                            imageWidth += 3;
                            if (imageWidth + leftPosition > this->lineLayoutTable[lineY].rightBorder) {
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
                                } while (leftPosition + imageWidth > this->lineLayoutTable[lineY].rightBorder);
                                if (this->useAlternateHelpTab && param_1 == 1) {
                                    local_100 = local_11c;
                                    local_11c = local_114;
                                    ++local_134;
                                    if (0 < this->field51_0x2396c && 2 <= local_134) {
                                        local_134 = -10000;
                                        this->activeHelpHotspotIndex = local_100 + local_10c;
                                        if (this->activeHelpHotspotIndex >= local_11c) {
                                            this->activeHelpHotspotIndex = local_11c - 1;
                                        }
                                        this->field51_0x2396c = 0;
                                    }
                                }
                                currentFontLineHeight = currentFontClass->lineHeight_0x14;
                            }
                            if (imageHeight > currentFontLineHeight) {
                                currentFontLineHeight = imageHeight;
                            }
                            leftPosition += imageWidth;
                            if (param_1 != 1 && imageCount == this->imageHotspotCount) {
                                this->imageHotspotTable[this->imageHotspotCount].xPos = leftPosition - imageWidth;
                                this->imageHotspotTable[this->imageHotspotCount].yPos = lineY;
                                ++this->imageHotspotCount;
                            }
                            break;
                        }
                        textMemIndex += 2;
                        if (positionToken != Enums::HTPPT_HERE && !param_1) {
                            ++this->imageHotspotCount;
                            DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                            abortProcessing = true;
                            continue;
                        }
                    } else {
                        textMemIndex += 3;
                    }
                    break;
                }
                case Enums::HTT_FONT: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(
                            wideTextBuffer, u__FONT__d__005a5454, this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    int fontSize = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    if (fontSize < 15) {
                        fontSize += 5;
                    }
                    textMemIndex += 2;
                    currentFontClass = &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize];
                    if (currentFontClass->lineHeight_0x14 > currentFontLineHeight || !local_f0) {
                        currentFontLineHeight = currentFontClass->lineHeight_0x14;
                    }
                    break;
                }
                case Enums::HTT_COLOUR: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__COLOUR__S__005a5824,
                            DAT_UserHelpDefinedData::instance
                                .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                                .name_0x0);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
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
                        color = ((colorBlue << 16) & 0xff0000) | ((colorGreen << 8) & 0x00ff00) | colorRed & 0x0000ff;
                    } else {
                        textMemIndex += 2;
                    }
                    break;
                }
                case Enums::HTT_LINKCOLOUR: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINKCOLOUR__S__005a5804,
                            DAT_UserHelpDefinedData::instance
                                .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                                .name_0x0);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    if (param_1 == 1) {
                        int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                        textMemIndex += 2;
                        linkColor
                            = ((DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].b_0xc << 16) & 0xff0000)
                            | ((DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].g_0x8 << 8) & 0x00ff00)
                            | DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].r_0x4 & 0x0000ff;
                    } else {
                        textMemIndex += 2;
                    }
                    break;
                }
                case Enums::HTT_LINK: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINK_S__005a57ec,
                            DAT_UserHelpDefinedData::instance
                                .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    currentLinkId = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    if (param_1 == 1) {
                        DAT_TextManagerObject::instance.helpTextLinkActive = TRUE;
                    }
                    textMemIndex += 2;
                    break;
                }
                case Enums::HTT_INCLUDE: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__INCLUDE_S__005a57cc,
                            DAT_UserHelpDefinedData::instance
                                .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    textMemIndex += 2;
                    break;
                }
                case Enums::HTT_SOUND: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__SOUND_S__005a57b0,
                            this->soundFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    if (param_1 == 1 && 0 <= lineY - this->helpContentScrollOffsetY
                        && lineY - this->helpContentScrollOffsetY < this->dialogContentHeight
                        && !this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]) {
                        this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]] = 1;
                    }
                    textMemIndex += 2;
                    break;
                }
                case Enums::HTT_ENDLINK: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__LINK__005a53d4);
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    currentLinkId = -1;
                    if (param_1 == 1) {
                        DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                    }
                    break;
                }
                case Enums::HTT_STRING: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__STRING__d__005a5358,
                            this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    textMemIndex += 2;
                    break;
                }
                case Enums::HTT_CENTRE: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__CENTRE__005a539c);
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    centreActive = TRUE;
                    centerCurrentLine = TRUE;
                    break;
                }
                case Enums::HTT_ENDCENTRE: {
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__CENTRE__005a5388);
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    centreActive = FALSE;
                    break;
                }
                case Enums::HTT_NEWPARAGRAPH: {
                    if (centerCurrentLine) {
                        this->lineLayoutTable[lineY].widthForCentering
                            = this->lineLayoutTable[lineY].rightBorder - leftPosition;
                        centerCurrentLine = centreActive;
                    }
                    if (this->useAlternateHelpTab && local_114 == this->activeHelpHotspotIndex) {
                        lineStartY = lineY;
                        lineEndY = currentFontLineHeight + lineY;
                        int xModify = 0;
                        if (param_1 == 1) {
                            if (centerCurrentLine) {
                                xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                            }
                            int xPos = this->dialogContentX + xModify;
                            int yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(xPos - 1 + leftPosition, yPos - 1 + lineY,
                                xPos - 1 + leftPosition, yPos + 1 + lineEndY, COL_DARK_LIME::instance.shortValue);
                            xPos = this->dialogContentX + xModify;
                            yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(xPos + leftPosition, yPos - 1 + lineY, xPos + leftPosition,
                                yPos + 1 + lineEndY, COL_DARK_LIME::instance.shortValue);
                            local_e4 = TRUE;
                        }
                    }
                    local_f0 = FALSE;
                    lineY += 3 + currentFontLineHeight;
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
                                if (this->activeHelpHotspotIndex >= local_11c) {
                                    this->activeHelpHotspotIndex = local_11c - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                        }
                        if (local_11c == this->activeHelpHotspotIndex && param_1 == 1) {
                            local_10c = 0;
                            if (this->field51_0x2396c < 0) {
                                this->activeHelpHotspotIndex = DAT_00df3348::instance + local_100;
                                if (this->activeHelpHotspotIndex >= local_11c) {
                                    this->activeHelpHotspotIndex = local_11c - 1;
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
                        break;
                    }
                    break;
                }
                case Enums::HTT_TAB: { // TODO?: unknown token
                    if (this->helpDialogSubMode == 1) {
                        charColor = 0xff;
                        local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__tab__005a5784);
                        textToRender.text = wideTextBuffer;
                        break;
                    }
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
                                if (this->activeHelpHotspotIndex >= local_11c) {
                                    this->activeHelpHotspotIndex = local_11c - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                        }
                        currentFontLineHeight = currentFontClass->lineHeight_0x14;
                    }
                    leftPosition += 30;
                    break;
                }
                case (wchar_t*)0: { // TODO?: unknown token, or just NULL, meaning end?
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
                                DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                                return TRUE;
                            }
                        }
                    } else if (this->useAlternateHelpTab) {
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
                            DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                            return TRUE;
                        }
                        DAT_00df334c::instance = 0;
                    }
                    DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                    return TRUE;
                }
                }
            } while (!abortProcessing && textToRender.value < L' ');
            if (abortProcessing) {
                continue;
            }

            int textWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfWideText, currentFontClass)(
                textToRender.text, wcslen(textToRender.text));
            if (leftPosition + textWidth > this->lineLayoutTable[lineY].rightBorder) {
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
                    ++local_134;
                    local_100 = local_11c;
                    local_11c = local_114;
                    if (0 < this->field51_0x2396c && 2 <= local_134) {
                        local_134 = -10000;
                        this->activeHelpHotspotIndex = local_100 + local_10c;
                        if (this->activeHelpHotspotIndex >= local_11c) {
                            this->activeHelpHotspotIndex = local_11c - 1;
                        }
                        this->field51_0x2396c = 0;
                    }
                }
                if (leftPosition + textWidth > this->lineLayoutTable[lineY].rightBorder) {
                    local_f8 = 0;
                    if (centerCurrentLine) {
                        local_f8 = this->lineLayoutTable[lineY].widthForCentering / 2;
                    }
                    int wordLength = wcslen(textToRender.text);
                    for (int i = 0; i < wordLength; ++i) {
                        int wideCharWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth, currentFontClass)(
                            textToRender.text[i]);
                        while (leftPosition + wideCharWidth > this->lineLayoutTable[lineY].rightBorder) {

                            if (centerCurrentLine) {
                                this->lineLayoutTable[lineY].widthForCentering
                                    = this->lineLayoutTable[lineY].rightBorder - leftPosition;
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
                                    if (this->activeHelpHotspotIndex >= local_11c) {
                                        this->activeHelpHotspotIndex = local_11c - 1;
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
                                    int xPos = this->dialogContentX + local_f8;
                                    int yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                        DAT_PencilRenderCore::ptr)(xPos - 1 + leftPosition, yPos - 1 + lineY,
                                        xPos - 1 + leftPosition, yPos + 1 + lineEndY,
                                        COL_DARK_LIME::instance.shortValue);
                                    xPos = this->dialogContentX + local_f8;
                                    yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                        DAT_PencilRenderCore::ptr)(xPos + leftPosition, yPos - 1 + lineY,
                                        xPos + leftPosition, yPos + 1 + lineEndY, COL_DARK_LIME::instance.shortValue);
                                    local_e4 = TRUE;
                                }
                            }
                        }
                        if (param_1 == 1) {
                            int charXPos = this->dialogContentX + local_f8 + leftPosition;
                            int charYPos = this->dialogContentY - this->helpContentScrollOffsetY + lineY;

                            wchar_t currentChar = textToRender.text[i];
                            int const newCharXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar,
                                currentFontClass)(currentChar, charXPos, charYPos, charColor, 0);
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

                        leftPosition += wideCharWidth;
                    }
                    continue;
                }
            }
            int charXPos = this->dialogContentX + leftPosition;
            int charYPos = (this->dialogContentY - this->helpContentScrollOffsetY) + lineY;
            if (centerCurrentLine) {
                charXPos += this->lineLayoutTable[lineY].widthForCentering / 2;
            }
            int wordLength = wcslen(textToRender.text);
            for (int i = 0; i < wordLength; ++i) {
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
                        local_10c = local_114 - local_11c + i;
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
                    wchar_t const currentChar = textToRender.text[i];
                    charXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                        currentChar, charXPos, charYPos, charColor, 0);
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
            leftPosition += textWidth;
        } while (!abortProcessing);
        return FALSE;
    }
}
}
