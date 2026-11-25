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
    int TextEditorState::processHelpRichTextTokens(int interactionModeUnk)
    {
        wchar_t wideTextBuffer[100];

        int centeringXOffset;

        int currentLinkId = -1;
        int textMemIndex = 0;
        FontSizeClass* currentFontClass = DAT_TextManagerObject::instance.fontSizeClassArray + 17;
        int currentFontLineHeight = currentFontClass->lineHeight_0x14;
        BOOL lineHasGlyphsUnk = FALSE;
        BGR24 color = 0xccfaff;
        BGR24 linkColor = 0x8bcf84;
        int imageCount = -1;
        BOOL centreActive = FALSE;
        BOOL centerCurrentLine = FALSE;
        int lineStartY = 0;
        int lineEndY = 0;
        int currentHotspotIndex = 0;
        int previousHotspotIndex = 0;
        int hotspotIndexOffset = 0;
        BOOL hotspotHandled = FALSE;
        int hotspotStepCountUnk = -10000;
        if (this->helpDialogVariant == 2 || this->isCustomTextMode) {
            color = 0xc2f0eb;
        }
        if (!this->isTextHelpDialogMode) {
            return 1;
        }
        this->field_0x23964 = -1;
        this->currentLinkId = -1;
        if (this->field_0x2396c) {
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
            int tokenStartIndex;
            BGR24 charColor;
            // false if text debug view token handled (this->helpDialogSubMode == 1), maybe related to input?
            BOOL isPlainTextTokenUnk;

            charColor = color;
            isPlainTextTokenUnk = TRUE;
            if (0 <= currentLinkId) {
                charColor = linkColor;
            }
            tokenStartIndex = textMemIndex;
            textToRender.value
                = MACRO_CALL_MEMBER(TextEditorState_Func::getWideCharOrWideCharPointer, this)(&textMemIndex);
            if (this->useAlternateHelpTab && textToRender.value < L' '
                && textToRender.helpToken != Enums::HTT_NEWPARAGRAPH
                && tokenStartIndex == this->activeHelpHotspotIndex) {
                lineStartY = lineY;
                lineEndY = lineY + currentFontLineHeight;
                if (interactionModeUnk == 1) {
                    int xModify = 0;
                    if (centerCurrentLine) {
                        xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                    }
                    hotspotIndexOffset = tokenStartIndex - currentHotspotIndex;
                    if (this->field_0x2396c < 0) {
                        this->activeHelpHotspotIndex = previousHotspotIndex + DAT_00df3348::instance;
                        if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                            this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                        }
                        this->field_0x2396c = 0;
                    }
                    hotspotStepCountUnk = 0;
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
                    hotspotHandled = TRUE;
                }
            }

            switch (textToRender.helpToken) {
            case Enums::HTT_PIC: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__PIC__d__S__005a583c,
                        this->DAT_PointerToTemporaryTextMemory[textMemIndex],
                        this->graphicFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    Enums::HelpTextPicturePositionToken positionToken
                        = (Enums::HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                    ++textMemIndex;
                    switch (positionToken) {
                    case Enums::HTPPT_LEFT:
                        wcscat(wideTextBuffer, u_LEFT__005a5494);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    case Enums::HTPPT_RIGHT:
                        wcscat(wideTextBuffer, u_RIGHT__005a5484);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    case Enums::HTPPT_CENTRE:
                        wcscat(wideTextBuffer, u_CENTRE__005a5474);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    case Enums::HTPPT_HERE:
                        wcscat(wideTextBuffer, u_HERE__005a5468);
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    default:
                        textMemIndex += 2;
                        textToRender.text = wideTextBuffer;
                        break;
                    }
                    break;
                }
                ++imageCount;

                bool validImageIndex = false;
                int imageIndex;
                if (interactionModeUnk == 1
                    && this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1] == Enums::HTPPT_HERE) {
                    imageIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    validImageIndex = true;
                } else if (!interactionModeUnk
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
                        = (Enums::HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[textMemIndex + 1];
                    ++textMemIndex;
                    int imageWidth = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].width;
                    int imageHeight = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].height;
                    switch (positionToken) {
                    case Enums::HTPPT_LEFT: {
                        this->imageHotspotTable[this->imageHotspotCount].xPos = this->lineLayoutTable[lineY].leftBorder;
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
                            lineHasGlyphsUnk = FALSE;
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
                            if (this->useAlternateHelpTab && interactionModeUnk == 1) {
                                previousHotspotIndex = currentHotspotIndex;
                                currentHotspotIndex = tokenStartIndex;
                                ++hotspotStepCountUnk;
                                if (0 < this->field_0x2396c && 2 <= hotspotStepCountUnk) {
                                    hotspotStepCountUnk = -10000;
                                    this->activeHelpHotspotIndex = previousHotspotIndex + hotspotIndexOffset;
                                    if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                        this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                                    }
                                    this->field_0x2396c = 0;
                                }
                            }
                            currentFontLineHeight = currentFontClass->lineHeight_0x14;
                        }
                        if (imageHeight > currentFontLineHeight) {
                            currentFontLineHeight = imageHeight;
                        }
                        leftPosition += hereWidth;
                        if (interactionModeUnk != 1 && imageCount == this->imageHotspotCount) {
                            this->imageHotspotTable[this->imageHotspotCount].xPos = leftPosition - hereWidth;
                            this->imageHotspotTable[this->imageHotspotCount].yPos = lineY;
                            ++this->imageHotspotCount;
                        }
                        break;
                    }
                    }
                    textMemIndex += 2;
                    if (positionToken != Enums::HTPPT_HERE && !interactionModeUnk) {
                        ++this->imageHotspotCount;
                        DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                        abortProcessing = true;
                        // continue;
                    }
                } else {
                    textMemIndex += 3;
                }
                break;
            }
            case Enums::HTT_FONT: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
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
                if (currentFontClass->lineHeight_0x14 > currentFontLineHeight || !lineHasGlyphsUnk) {
                    currentFontLineHeight = currentFontClass->lineHeight_0x14;
                }
                break;
            }
            case Enums::HTT_COLOUR: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__COLOUR__S__005a5824,
                        DAT_UserHelpDefinedData::instance
                            .field_0x7a16c[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                            .name_0x0);
                    textMemIndex += 2;
                    textToRender.text = wideTextBuffer;
                    break;
                }
                if (interactionModeUnk == 1) {
                    int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];

                    uint colorRed;
                    uint colorGreen;
                    uint colorBlue;
                    if (this->helpDialogVariant == 2 && colorIndex == 1) {
                        colorRed = 0xd7;
                        colorGreen = 0xd2;
                        colorBlue = 0xa4;
                    } else {
                        colorRed = DAT_UserHelpDefinedData::instance.field_0x7a16c[colorIndex].r_0x4;
                        colorGreen = DAT_UserHelpDefinedData::instance.field_0x7a16c[colorIndex].g_0x8;
                        colorBlue = DAT_UserHelpDefinedData::instance.field_0x7a16c[colorIndex].b_0xc;
                    }
                    textMemIndex += 2;
                    color = RGB(colorRed, colorGreen, colorBlue);
                } else {
                    textMemIndex += 2;
                }
                break;
            }
            case Enums::HTT_LINKCOLOUR: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINKCOLOUR__S__005a5804,
                        DAT_UserHelpDefinedData::instance
                            .field_0x7a16c[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]
                            .name_0x0);
                    textMemIndex += 2;
                    textToRender.text = wideTextBuffer;
                    break;
                }
                if (interactionModeUnk == 1) {
                    int const colorIndex = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                    textMemIndex += 2;
                    linkColor = RGB(DAT_UserHelpDefinedData::instance.field_0x7a16c[colorIndex].r_0x4,
                        DAT_UserHelpDefinedData::instance.field_0x7a16c[colorIndex].g_0x8,
                        DAT_UserHelpDefinedData::instance.field_0x7a16c[colorIndex].b_0xc);
                } else {
                    textMemIndex += 2;
                }
                break;
            }
            case Enums::HTT_LINK: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINK_S__005a57ec,
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    textToRender.text = wideTextBuffer;
                    break;
                }
                currentLinkId = this->DAT_PointerToTemporaryTextMemory[textMemIndex];
                if (interactionModeUnk == 1) {
                    DAT_TextManagerObject::instance.helpTextLinkActive = TRUE;
                }
                textMemIndex += 2;
                break;
            }
            case Enums::HTT_INCLUDE: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
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
                    isPlainTextTokenUnk = FALSE;
                    MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__SOUND_S__005a57b0,
                        this->soundFileNames[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]);
                    textMemIndex += 2;
                    textToRender.text = wideTextBuffer;
                    break;
                }
                if (interactionModeUnk == 1) {
                    int const visibleY = lineY - this->helpContentScrollOffsetY;
                    if (0 <= visibleY && visibleY < this->dialogContentHeight
                        && !this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]]) {
                        this->soundFilePlayedFlags[this->DAT_PointerToTemporaryTextMemory[textMemIndex]] = 1;
                    }
                }
                textMemIndex += 2;
                break;
            }
            case Enums::HTT_ENDLINK: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    wcscpy(wideTextBuffer, u__LINK__005a53d4);
                    textToRender.text = wideTextBuffer;
                    break;
                }
                currentLinkId = -1;
                if (interactionModeUnk == 1) {
                    DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                }
                break;
            }
            case Enums::HTT_STRING: {
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    MACRO_CALL(Global_Func::PrintToDestination)(
                        wideTextBuffer, u__STRING__d__005a5358, this->DAT_PointerToTemporaryTextMemory[textMemIndex]);
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
                    isPlainTextTokenUnk = FALSE;
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
                    isPlainTextTokenUnk = FALSE;
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
                if (this->useAlternateHelpTab && tokenStartIndex == this->activeHelpHotspotIndex) {
                    lineStartY = lineY;
                    lineEndY = currentFontLineHeight + lineY;
                    if (interactionModeUnk == 1) {
                        int xModify = 0;
                        if (centerCurrentLine) {
                            xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                        }
                        int xPos = this->dialogContentX + xModify;
                        int yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            xPos - 1 + leftPosition, yPos - 1 + lineStartY, xPos - 1 + leftPosition,
                            yPos + 1 + lineEndY, COL_DARK_LIME::instance.shortValue);
                        xPos = this->dialogContentX + xModify;
                        yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            xPos + leftPosition, yPos - 1 + lineStartY, xPos + leftPosition, yPos + 1 + lineEndY,
                            COL_DARK_LIME::instance.shortValue);
                        hotspotHandled = TRUE;
                    }
                }
                lineHasGlyphsUnk = FALSE;
                lineY += 3 + currentFontLineHeight;
                do {
                    leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                } while (leftPosition == -1);
                currentFontLineHeight = currentFontClass->lineHeight_0x14;

                if (this->useAlternateHelpTab) {
                    previousHotspotIndex = currentHotspotIndex;
                    currentHotspotIndex = tokenStartIndex;
                    if (interactionModeUnk == 1) {
                        ++hotspotStepCountUnk;
                        if (0 < this->field_0x2396c && 2 <= hotspotStepCountUnk) {
                            hotspotStepCountUnk = -10000;
                            this->activeHelpHotspotIndex = hotspotIndexOffset + previousHotspotIndex;
                            if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                            }
                            this->field_0x2396c = 0;
                        }
                    }
                    if (currentHotspotIndex == this->activeHelpHotspotIndex && interactionModeUnk == 1) {
                        hotspotIndexOffset = 0;
                        if (this->field_0x2396c < 0) {
                            this->activeHelpHotspotIndex = DAT_00df3348::instance + previousHotspotIndex;
                            if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                            }
                            this->field_0x2396c = 0;
                        }
                        hotspotStepCountUnk = 0;
                    }
                }
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    wcscpy(wideTextBuffer, u__NEWPARAGRAPH__005a5790);
                    textToRender.text = wideTextBuffer;
                    break;
                }
                break;
            }
            case Enums::HTT_TAB: { // TODO?: unknown token
                if (this->helpDialogSubMode == 1) {
                    charColor = 0xff;
                    isPlainTextTokenUnk = FALSE;
                    wcscpy(wideTextBuffer, u__tab__005a5784);
                    textToRender.text = wideTextBuffer;
                    break;
                }
                if (leftPosition + 30 > this->lineLayoutTable[lineY].rightBorder) {
                    lineHasGlyphsUnk = FALSE;
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

                    if (this->useAlternateHelpTab && interactionModeUnk == 1) {
                        previousHotspotIndex = currentHotspotIndex;
                        currentHotspotIndex = tokenStartIndex;
                        ++hotspotStepCountUnk;
                        if (0 < this->field_0x2396c && 2 <= hotspotStepCountUnk) {
                            hotspotStepCountUnk = -10000;
                            this->activeHelpHotspotIndex = previousHotspotIndex + hotspotIndexOffset;
                            if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                            }
                            this->field_0x2396c = 0;
                        }
                    }
                    currentFontLineHeight = currentFontClass->lineHeight_0x14;
                }
                leftPosition += 30;
                break;
            }
            case (wchar_t*)0: { // TODO?: unknown token, or just NULL, meaning end?
                if (interactionModeUnk == 0) {
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
                    DAT_00df3348::instance = hotspotIndexOffset;
                    if (0 < this->field_0x2396c && hotspotStepCountUnk == 1) {
                        this->activeHelpHotspotIndex = hotspotIndexOffset + currentHotspotIndex;
                        if (this->activeHelpHotspotIndex > this->customHelpTextLength) {
                            this->activeHelpHotspotIndex = this->customHelpTextLength;
                        }
                        this->field_0x2396c = 0;
                    }
                    if (!hotspotHandled && this->activeHelpHotspotIndex && DAT_00df334c::instance) {
                        --this->activeHelpHotspotIndex;
                        this->field_0x23970 = 0;
                        DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                        return TRUE;
                    }
                    DAT_00df334c::instance = 0;
                }
                DAT_TextManagerObject::instance.helpTextLinkActive = FALSE;
                return TRUE;
            }
            }
            if (textToRender.value < L' ') {
                continue;
            }

            int textWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfWideText, currentFontClass)(
                textToRender.text, wcslen(textToRender.text));
            if (leftPosition + textWidth > this->lineLayoutTable[lineY].rightBorder) {
                lineHasGlyphsUnk = FALSE;
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
                    ++hotspotStepCountUnk;
                    previousHotspotIndex = currentHotspotIndex;
                    currentHotspotIndex = tokenStartIndex;
                    if (0 < this->field_0x2396c && 2 <= hotspotStepCountUnk) {
                        hotspotStepCountUnk = -10000;
                        this->activeHelpHotspotIndex = previousHotspotIndex + hotspotIndexOffset;
                        if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                            this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                        }
                        this->field_0x2396c = 0;
                    }
                }
                if (leftPosition + textWidth > this->lineLayoutTable[lineY].rightBorder) {
                    centeringXOffset = 0;
                    if (centerCurrentLine) {
                        centeringXOffset = this->lineLayoutTable[lineY].widthForCentering / 2;
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
                            if (this->useAlternateHelpTab && interactionModeUnk == 1) {
                                previousHotspotIndex = currentHotspotIndex;
                                currentHotspotIndex = tokenStartIndex + i;
                                ++hotspotStepCountUnk;
                                if (0 < this->field_0x2396c && 2 <= hotspotStepCountUnk) {
                                    hotspotStepCountUnk = -10000;
                                    this->activeHelpHotspotIndex = previousHotspotIndex + hotspotIndexOffset;
                                    if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                        this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                                    }
                                    this->field_0x2396c = 0;
                                }
                            }
                            do {
                                leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                            } while (leftPosition == -1);
                            if (centerCurrentLine) {
                                centeringXOffset = this->lineLayoutTable[lineY].widthForCentering / 2;
                            }
                        }
                        if (this->useAlternateHelpTab && tokenStartIndex + i == this->activeHelpHotspotIndex) {
                            lineStartY = lineY;
                            lineEndY = lineY + currentFontLineHeight;
                            if (interactionModeUnk == 1) {
                                if (isPlainTextTokenUnk) {
                                    hotspotIndexOffset = (i - currentHotspotIndex) + tokenStartIndex;
                                    if (this->field_0x2396c < 0) {
                                        this->activeHelpHotspotIndex = DAT_00df3348::instance + previousHotspotIndex;
                                        if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                            this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                                        }
                                        this->field_0x2396c = 0;
                                    }
                                    hotspotStepCountUnk = 0;
                                    int xPos = this->dialogContentX + centeringXOffset;
                                    int yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                        DAT_PencilRenderCore::ptr)(xPos - 1 + leftPosition, yPos - 1 + lineY,
                                        xPos - 1 + leftPosition, yPos + 1 + lineEndY,
                                        COL_DARK_LIME::instance.shortValue);
                                    xPos = this->dialogContentX + centeringXOffset;
                                    yPos = this->dialogContentY - this->helpContentScrollOffsetY;
                                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                        DAT_PencilRenderCore::ptr)(xPos + leftPosition, yPos - 1 + lineY,
                                        xPos + leftPosition, yPos + 1 + lineEndY, COL_DARK_LIME::instance.shortValue);
                                    hotspotHandled = TRUE;
                                }
                            }
                        }
                        if (interactionModeUnk == 1) {
                            int charXPos = this->dialogContentX + centeringXOffset + leftPosition;
                            int charYPos = this->dialogContentY - this->helpContentScrollOffsetY + lineY;

                            wchar_t currentChar = textToRender.text[i];
                            int const newCharXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar,
                                currentFontClass)(currentChar, charXPos, charYPos, charColor, 0);
                            lineHasGlyphsUnk = TRUE;
                            if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                    charXPos - this->helpContentScrollX, charYPos - this->helpContentScrollY,
                                    newCharXPos - charXPos, currentFontLineHeight + 2)) {
                                if (isPlainTextTokenUnk) {
                                    this->field_0x23964 = tokenStartIndex + i;
                                    this->currentLinkId = currentLinkId;
                                } else {
                                    this->field_0x23964 = tokenStartIndex;
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
                if (this->useAlternateHelpTab && i + tokenStartIndex == this->activeHelpHotspotIndex) {
                    if (interactionModeUnk == 1 && isPlainTextTokenUnk) {
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            charXPos - 1, charYPos - 1, charXPos - 1, charYPos + 1 + currentFontLineHeight,
                            COL_DARK_LIME::instance.shortValue);
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            charXPos, charYPos - 1, charXPos, charYPos + 1 + currentFontLineHeight,
                            COL_DARK_LIME::instance.shortValue);
                        hotspotHandled = TRUE;
                    }
                    lineStartY = lineY;
                    lineEndY = lineY + currentFontLineHeight;
                    if (interactionModeUnk == 1) {
                        hotspotStepCountUnk = 0;
                        hotspotIndexOffset = tokenStartIndex - currentHotspotIndex + i;
                        if (this->field_0x2396c < 0 && isPlainTextTokenUnk) {
                            this->activeHelpHotspotIndex = previousHotspotIndex + DAT_00df3348::instance;
                            if (this->activeHelpHotspotIndex >= currentHotspotIndex) {
                                this->activeHelpHotspotIndex = currentHotspotIndex - 1;
                            }
                            this->field_0x2396c = 0;
                        }
                    }
                }

                if (interactionModeUnk == 1) {
                    lineHasGlyphsUnk = TRUE;
                    int oldCharPos = charXPos;
                    wchar_t const currentChar = textToRender.text[i];
                    charXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, currentFontClass)(
                        currentChar, charXPos, charYPos, charColor, 0);
                    if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                            oldCharPos - this->helpContentScrollX, charYPos - this->helpContentScrollY,
                            charXPos - oldCharPos, currentFontLineHeight + 2)) {
                        if (isPlainTextTokenUnk) {
                            this->field_0x23964 = i + tokenStartIndex;
                            this->currentLinkId = currentLinkId;
                        } else {
                            this->field_0x23964 = tokenStartIndex;
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
