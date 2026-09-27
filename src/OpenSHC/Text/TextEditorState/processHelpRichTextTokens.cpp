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

// TO TEST?: leftPosition does not seem to be used for stack as often as it should be
// could it be that leftPosition is just leftborder called again and again? Although, it is handled rather different
// it would allow to reduce the loops, though

namespace OpenSHC {
namespace Text {

    union TextMemUnion {
        int value;
        wchar_t* text;
        HelpTextToken helpToken;
        Enums::HelpTextPicturePositionToken picturePositionToken;
    };

    struct StackHelper {
        int imageCount;
        BGR24 color;
        int wordLength;
        BGR24 linkColor;
    };

    struct StackHelper2 {
        BOOL local_f0;
        int currentLinkId;
        int lineStartY;
        BOOL local_e4;
    };

    struct StackHelper3 {
        int local_100;
        BOOL centreActive;
    };

    struct StackHelper4 {
        int textMemIndex;
        int leftPosition;
        int local_134;
        int currentFontLineHeight;
        int local_12c;
        TextMemUnion textToRender;
        BGR24 charColor;
        BOOL centerCurrentLine;
        int local_11c;
    };
    struct StackHelper5 {
        int local_114;
        FontSizeClass* currentFontClass;
        int local_10c;
        int lineEndY;
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x0045FDC0
    int TextEditorState::processHelpRichTextTokens(int param_1)
    {
        struct StackHelper stackHelper;
        struct StackHelper2 stackHelper2;
        struct StackHelper3 stackHelper3;
        struct StackHelper4 stackHelper4;
        struct StackHelper5 stackHelper5;

        wchar_t wideTextBuffer[100];

        int local_f8;

        stackHelper2.currentLinkId = -1;
        stackHelper4.textMemIndex = 0;
        stackHelper5.currentFontClass = DAT_TextManagerObject::instance.fontSizeClassArray + 17;
        stackHelper4.currentFontLineHeight = stackHelper5.currentFontClass->lineHeight_0x14;
        stackHelper2.local_f0 = FALSE;
        stackHelper.color = 0xccfaff;
        stackHelper.linkColor = 0x8bcf84;
        stackHelper.imageCount = -1;
        stackHelper3.centreActive = FALSE;
        stackHelper4.centerCurrentLine = FALSE;
        stackHelper2.lineStartY = 0;
        stackHelper5.lineEndY = 0;
        stackHelper4.local_11c = 0;
        stackHelper3.local_100 = 0;
        stackHelper5.local_10c = 0;
        stackHelper2.local_e4 = FALSE;
        stackHelper4.local_134 = -10000;
        if (this->helpDialogVariant == 2 || this->isCustomTextMode) {
            stackHelper.color = 0xc2f0eb;
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
            stackHelper4.leftPosition = this->lineLayoutTable[++lineY].leftBorder;
        } while (stackHelper4.leftPosition == -1);
        while (true) {
            do {
                stackHelper4.charColor = stackHelper.color;
                stackHelper4.local_12c = TRUE;
                if (0 <= stackHelper2.currentLinkId) {
                    stackHelper4.charColor = stackHelper.linkColor;
                }
                stackHelper5.local_114 = stackHelper4.textMemIndex;
                stackHelper4.textToRender.value = MACRO_CALL_MEMBER(
                    TextEditorState_Func::getWideCharOrWideCharPointer, this)(&stackHelper4.textMemIndex);
                if (this->useAlternateHelpTab && stackHelper4.textToRender.value < L' '
                    && stackHelper4.textToRender.helpToken != Enums::HTT_NEWPARAGRAPH
                    && stackHelper5.local_114 == this->activeHelpHotspotIndex) {
                    stackHelper2.lineStartY = lineY;
                    stackHelper5.lineEndY = lineY + stackHelper4.currentFontLineHeight;
                    if (param_1 == 1) {
                        int xModify = 0;
                        if (stackHelper4.centerCurrentLine) {
                            xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                        }
                        stackHelper5.local_10c = stackHelper5.local_114 - stackHelper4.local_11c;
                        if (this->field51_0x2396c < 0) {
                            this->activeHelpHotspotIndex = stackHelper3.local_100 + DAT_00df3348::instance;
                            if (this->activeHelpHotspotIndex >= stackHelper4.local_11c) {
                                this->activeHelpHotspotIndex = stackHelper4.local_11c - 1;
                            }
                            this->field51_0x2396c = 0;
                        }
                        stackHelper4.local_134 = 0;
                        int drawXPos = this->dialogContentX + xModify + stackHelper4.leftPosition - 1;
                        int drawYStart = this->dialogContentY - this->helpContentScrollOffsetY + lineY - 1;
                        int drawYEnd
                            = this->dialogContentY - this->helpContentScrollOffsetY + stackHelper5.lineEndY + 1;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            drawXPos, drawYStart, drawXPos, drawYEnd, COL_DARK_LIME::instance.shortValue);
                        drawXPos = this->dialogContentX + xModify + stackHelper4.leftPosition;
                        drawYStart = this->dialogContentY - this->helpContentScrollOffsetY + lineY - 1;
                        drawYEnd = this->dialogContentY - this->helpContentScrollOffsetY + stackHelper5.lineEndY + 1;
                        MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                            drawXPos, drawYStart, drawXPos, drawYEnd, COL_DARK_LIME::instance.shortValue);
                        stackHelper2.local_e4 = TRUE;
                    }
                }

                switch (stackHelper4.textToRender.helpToken) {
                case Enums::HTT_PIC:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__PIC__d__S__005a583c,
                            this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex],
                            this->graphicFileNames[this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]);
                        Enums::HelpTextPicturePositionToken positionToken
                            = (Enums::HelpTextPicturePositionToken)this
                                  ->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex + 1];
                        ++stackHelper4.textMemIndex;
                        switch (positionToken) {
                        case Enums::HTPPT_LEFT:
                            wcscat(wideTextBuffer, u_LEFT__005a5494);
                            stackHelper4.textMemIndex += 2;
                            stackHelper4.textToRender.text = wideTextBuffer;
                            break;
                        case Enums::HTPPT_RIGHT:
                            wcscat(wideTextBuffer, u_RIGHT__005a5484);
                            stackHelper4.textMemIndex += 2;
                            stackHelper4.textToRender.text = wideTextBuffer;
                            break;
                        case Enums::HTPPT_CENTRE:
                            wcscat(wideTextBuffer, u_CENTRE__005a5474);
                            stackHelper4.textMemIndex += 2;
                            stackHelper4.textToRender.text = wideTextBuffer;
                            break;
                        case Enums::HTPPT_HERE:
                            wcscat(wideTextBuffer, u_HERE__005a5468);
                            stackHelper4.textMemIndex += 2;
                            stackHelper4.textToRender.text = wideTextBuffer;
                            break;
                        default:
                            stackHelper4.textMemIndex += 2;
                            stackHelper4.textToRender.text = wideTextBuffer;
                            break;
                        }
                    } else {
                        ++stackHelper.imageCount;

                        bool validImageIndex = false;
                        int imageIndex;
                        if (param_1 == 1
                            && this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex + 1]
                                == Enums::HTPPT_HERE) {
                            imageIndex = this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex];
                            validImageIndex = true;
                        } else if (!param_1
                            && (stackHelper.imageCount == this->imageHotspotCount
                                || this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex + 1]
                                    == Enums::HTPPT_HERE)) {
                            imageIndex = this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex];
                            if (stackHelper.imageCount == this->imageHotspotCount) {
                                this->imageHotspotTable[this->imageHotspotCount].yPos = lineY + 25;
                                this->imageHotspotTable[this->imageHotspotCount].imageIndex = imageIndex;
                                this->imageHotspotTable[this->imageHotspotCount].linkId = stackHelper2.currentLinkId;
                            }
                            validImageIndex = true;
                        }
                        if (validImageIndex) {
                            Enums::HelpTextPicturePositionToken positionToken
                                = (Enums::HelpTextPicturePositionToken)this
                                      ->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex + 1];
                            ++stackHelper4.textMemIndex;
                            int imageWidth
                                = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].width;
                            int imageHeight
                                = DAT_TextureRenderCoreObject::instance.loadedGfxArray[99 - imageIndex].height;
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
                                if (imageWidth + stackHelper4.leftPosition > this->lineLayoutTable[lineY].rightBorder) {
                                    stackHelper2.local_f0 = FALSE;
                                    if (stackHelper4.centerCurrentLine) {
                                        this->lineLayoutTable[lineY].widthForCentering
                                            = this->lineLayoutTable[lineY].rightBorder - stackHelper4.leftPosition;
                                        stackHelper4.centerCurrentLine = stackHelper3.centreActive;
                                    }
                                    do {
                                        lineY += stackHelper4.currentFontLineHeight + 1;
                                        do {
                                            stackHelper4.leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                                        } while (stackHelper4.leftPosition == -1);
                                    } while (stackHelper4.leftPosition + imageWidth
                                        > this->lineLayoutTable[lineY].rightBorder);
                                    if (this->useAlternateHelpTab && param_1 == 1) {
                                        stackHelper3.local_100 = stackHelper4.local_11c;
                                        stackHelper4.local_11c = stackHelper5.local_114;
                                        ++stackHelper4.local_134;
                                        if (0 < this->field51_0x2396c && 2 <= stackHelper4.local_134) {
                                            stackHelper4.local_134 = -10000;
                                            this->activeHelpHotspotIndex
                                                = stackHelper3.local_100 + stackHelper5.local_10c;
                                            if (this->activeHelpHotspotIndex >= stackHelper5.local_114) {
                                                this->activeHelpHotspotIndex = stackHelper5.local_114 - 1;
                                            }
                                            this->field51_0x2396c = 0;
                                        }
                                    }
                                    stackHelper4.currentFontLineHeight = stackHelper5.currentFontClass->lineHeight_0x14;
                                }
                                if (imageHeight > stackHelper4.currentFontLineHeight) {
                                    stackHelper4.currentFontLineHeight = imageHeight;
                                }
                                stackHelper4.leftPosition += imageWidth;
                                if (param_1 != 1 && stackHelper.imageCount == this->imageHotspotCount) {
                                    this->imageHotspotTable[this->imageHotspotCount].xPos
                                        = stackHelper4.leftPosition - imageWidth;
                                    this->imageHotspotTable[this->imageHotspotCount].yPos = lineY;
                                    ++this->imageHotspotCount;
                                }
                                break;
                            }
                            stackHelper4.textMemIndex += 2;
                            if (positionToken == Enums::HTPPT_HERE || param_1) {
                                continue;
                            }
                            ++this->imageHotspotCount;
                            DAT_TextManagerObject::instance.field6_0x18 = 0;
                            return FALSE;
                        } else {
                            stackHelper4.textMemIndex += 3;
                        }
                    }
                    break;
                case Enums::HTT_FONT:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__FONT__d__005a5454,
                            this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        int fontSize = this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex];
                        if (fontSize < 15) {
                            fontSize += 5;
                        }
                        stackHelper4.textMemIndex += 2;
                        stackHelper5.currentFontClass = &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize];
                        if (stackHelper5.currentFontClass->lineHeight_0x14 > stackHelper4.currentFontLineHeight
                            || !stackHelper2.local_f0) {
                            stackHelper4.currentFontLineHeight = stackHelper5.currentFontClass->lineHeight_0x14;
                        }
                    }
                    break;
                case Enums::HTT_COLOUR:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__COLOUR__S__005a5824,
                            DAT_UserHelpDefinedData::instance
                                .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]
                                .name_0x0);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        if (param_1 == 1) {
                            int const colorIndex = this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex];

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
                            stackHelper4.textMemIndex += 2;
                            stackHelper.color
                                = ((colorBlue << 16) & 0xff0000) | ((colorGreen << 8) & 0x00ff00) | colorRed & 0x0000ff;
                        } else {
                            stackHelper4.textMemIndex += 2;
                        }
                    }
                    break;
                case Enums::HTT_LINKCOLOUR:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINKCOLOUR__S__005a5804,
                            DAT_UserHelpDefinedData::instance
                                .field6_0x7a16c[this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]
                                .name_0x0);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        if (param_1 == 1) {
                            int const colorIndex = this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex];
                            stackHelper4.textMemIndex += 2;
                            stackHelper.linkColor
                                = ((DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].b_0xc << 16)
                                      & 0xff0000)
                                | ((DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].g_0x8 << 8) & 0x00ff00)
                                | DAT_UserHelpDefinedData::instance.field6_0x7a16c[colorIndex].r_0x4 & 0x0000ff;
                        } else {
                            stackHelper4.textMemIndex += 2;
                        }
                    }
                    break;
                case Enums::HTT_LINK:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__LINK_S__005a57ec,
                            DAT_UserHelpDefinedData::instance
                                .HelpSections[this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        stackHelper2.currentLinkId = this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex];
                        if (param_1 == 1) {
                            DAT_TextManagerObject::instance.field6_0x18 = 1;
                        }
                        stackHelper4.textMemIndex += 2;
                    }
                    break;
                case Enums::HTT_INCLUDE:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__INCLUDE_S__005a57cc,
                            DAT_UserHelpDefinedData::instance
                                .HelpSections[this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        stackHelper4.textMemIndex += 2;
                    }
                    break;
                case Enums::HTT_SOUND:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__SOUND_S__005a57b0,
                            this->soundFileNames[this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        if (param_1 == 1 && 0 <= lineY - this->helpContentScrollOffsetY
                            && lineY - this->helpContentScrollOffsetY < this->dialogContentHeight
                            && !this->soundFilePlayedFlags[this
                                    ->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]]) {
                            this->soundFilePlayedFlags[this
                                    ->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]] = 1;
                        }
                        stackHelper4.textMemIndex += 2;
                    }
                    break;
                case Enums::HTT_ENDLINK:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__LINK__005a53d4);
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        stackHelper2.currentLinkId = -1;
                        if (param_1 == 1) {
                            DAT_TextManagerObject::instance.field6_0x18 = 0;
                        }
                    }
                    break;
                case Enums::HTT_STRING:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        MACRO_CALL(Global_Func::PrintToDestination)(wideTextBuffer, u__STRING__d__005a5358,
                            this->DAT_PointerToTemporaryTextMemory[stackHelper4.textMemIndex]);
                        stackHelper4.textMemIndex += 2;
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        stackHelper4.textMemIndex += 2;
                    }
                    break;
                case Enums::HTT_CENTRE:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__CENTRE__005a539c);
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        stackHelper3.centreActive = TRUE;
                        stackHelper4.centerCurrentLine = TRUE;
                    }
                    break;
                case Enums::HTT_ENDCENTRE:
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__CENTRE__005a5388);
                        stackHelper4.textToRender.text = wideTextBuffer;
                    } else {
                        stackHelper3.centreActive = FALSE;
                    }
                    break;
                case Enums::HTT_NEWPARAGRAPH:
                    if (stackHelper4.centerCurrentLine) {
                        this->lineLayoutTable[lineY].widthForCentering
                            = this->lineLayoutTable[lineY].rightBorder - stackHelper4.leftPosition;
                        stackHelper4.centerCurrentLine = stackHelper3.centreActive;
                    }
                    if (this->useAlternateHelpTab && stackHelper5.local_114 == this->activeHelpHotspotIndex) {
                        stackHelper2.lineStartY = lineY;
                        stackHelper5.lineEndY = stackHelper4.currentFontLineHeight + lineY;
                        int xModify = 0;
                        if (param_1 == 1) {
                            if (stackHelper4.centerCurrentLine) {
                                xModify = this->lineLayoutTable[lineY].widthForCentering / 2;
                            }
                            MACRO_CALL_MEMBER(
                                UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                                this->dialogContentX + xModify - 1 + stackHelper4.leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                this->dialogContentX + xModify - 1 + stackHelper4.leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY + 1 + stackHelper5.lineEndY,
                                COL_DARK_LIME::instance.shortValue);
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(this->dialogContentX + xModify + stackHelper4.leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                this->dialogContentX + xModify + stackHelper4.leftPosition,
                                this->dialogContentY - this->helpContentScrollOffsetY + 1 + stackHelper5.lineEndY,
                                COL_DARK_LIME::instance.shortValue);
                            stackHelper2.local_e4 = TRUE;
                        }
                    }
                    stackHelper2.local_f0 = FALSE;
                    lineY += 3 + stackHelper4.currentFontLineHeight;
                    do {
                        stackHelper4.leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                    } while (stackHelper4.leftPosition == -1);
                    stackHelper4.currentFontLineHeight = stackHelper5.currentFontClass->lineHeight_0x14;

                    if (this->useAlternateHelpTab) {
                        stackHelper3.local_100 = stackHelper4.local_11c;
                        stackHelper4.local_11c = stackHelper5.local_114;
                        if (param_1 == 1) {
                            ++stackHelper4.local_134;
                            if (0 < this->field51_0x2396c && 2 <= stackHelper4.local_134) {
                                stackHelper4.local_134 = -10000;
                                this->activeHelpHotspotIndex = stackHelper5.local_10c + stackHelper3.local_100;
                                if (this->activeHelpHotspotIndex >= stackHelper5.local_114) {
                                    this->activeHelpHotspotIndex = stackHelper5.local_114 - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                        }
                        if (stackHelper5.local_114 == this->activeHelpHotspotIndex && param_1 == 1) {
                            stackHelper5.local_10c = 0;
                            if (this->field51_0x2396c < 0) {
                                this->activeHelpHotspotIndex = DAT_00df3348::instance + stackHelper3.local_100;
                                if (this->activeHelpHotspotIndex >= stackHelper5.local_114) {
                                    this->activeHelpHotspotIndex = stackHelper5.local_114 - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                            stackHelper4.local_134 = 0;
                        }
                    }
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__NEWPARAGRAPH__005a5790);
                        stackHelper4.textToRender.text = wideTextBuffer;
                    }
                    break;
                case Enums::HTT_TAB: // TODO?: unknown token
                    if (this->helpDialogSubMode == 1) {
                        stackHelper4.charColor = 0xff;
                        stackHelper4.local_12c = FALSE;
                        wcscpy(wideTextBuffer, u__tab__005a5784);
                        stackHelper4.textToRender.text = wideTextBuffer;

                    } else {
                        if (stackHelper4.leftPosition + 30 > this->lineLayoutTable[lineY].rightBorder) {
                            stackHelper2.local_f0 = FALSE;
                            if (stackHelper4.centerCurrentLine) {
                                this->lineLayoutTable[lineY].widthForCentering
                                    = this->lineLayoutTable[lineY].rightBorder - stackHelper4.leftPosition;
                                stackHelper4.centerCurrentLine = stackHelper3.centreActive;
                            }
                            do {
                                lineY += stackHelper4.currentFontLineHeight + 1;
                                do {
                                    stackHelper4.leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                                } while (stackHelper4.leftPosition == -1);
                            } while (stackHelper4.leftPosition + 30 > this->lineLayoutTable[lineY].rightBorder);

                            if (this->useAlternateHelpTab && param_1 == 1) {
                                stackHelper3.local_100 = stackHelper4.local_11c;
                                stackHelper4.local_11c = stackHelper5.local_114;
                                ++stackHelper4.local_134;
                                if (0 < this->field51_0x2396c && 2 <= stackHelper4.local_134) {
                                    stackHelper4.local_134 = -10000;
                                    this->activeHelpHotspotIndex = stackHelper3.local_100 + stackHelper5.local_10c;
                                    if (this->activeHelpHotspotIndex >= stackHelper5.local_114) {
                                        this->activeHelpHotspotIndex = stackHelper5.local_114 - 1;
                                    }
                                    this->field51_0x2396c = 0;
                                }
                            }
                            stackHelper4.currentFontLineHeight = stackHelper5.currentFontClass->lineHeight_0x14;
                        }
                        stackHelper4.leftPosition += 30;
                    }
                    break;
                case (wchar_t*)0: // TODO?: unknown token, or just NULL, meaning end?
                    if (param_1 == 0) {
                        this->topVisibleLineIndex = lineY + stackHelper4.currentFontLineHeight - 1;
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
                            if (stackHelper2.lineStartY < this->helpContentScrollOffsetY) {
                                this->helpContentScrollOffsetY = stackHelper2.lineStartY;
                            }
                            if (stackHelper5.lineEndY > this->helpContentScrollOffsetY + this->dialogContentHeight) {
                                this->helpContentScrollOffsetY
                                    = (stackHelper5.lineEndY - this->dialogContentHeight) + 5;
                            }
                        }
                    } else {
                        if (this->useAlternateHelpTab) {
                            DAT_00df3348::instance = stackHelper5.local_10c;
                            if (0 < this->field51_0x2396c && stackHelper4.local_134 == 1) {
                                this->activeHelpHotspotIndex = stackHelper5.local_10c + stackHelper4.local_11c;
                                if (this->activeHelpHotspotIndex > this->customHelpTextLength) {
                                    this->activeHelpHotspotIndex = this->customHelpTextLength;
                                }
                                this->field51_0x2396c = 0;
                            }
                            if (!stackHelper2.local_e4 && this->activeHelpHotspotIndex && DAT_00df334c::instance) {
                                --this->activeHelpHotspotIndex;
                                this->field52_0x23970 = 0;
                            } else {
                                DAT_00df334c::instance = 0;
                            }
                        }
                    }
                    DAT_TextManagerObject::instance.field6_0x18 = 0;
                    return TRUE;
                }
            } while (stackHelper4.textToRender.value < L' ');

            int textWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfWideText, stackHelper5.currentFontClass)(
                stackHelper4.textToRender.text, wcslen(stackHelper4.textToRender.text));
            if (textWidth + stackHelper4.leftPosition > this->lineLayoutTable[lineY].rightBorder) {
                stackHelper2.local_f0 = FALSE;
                if (stackHelper4.centerCurrentLine) {
                    this->lineLayoutTable[lineY].widthForCentering
                        = this->lineLayoutTable[lineY].rightBorder - stackHelper4.leftPosition;
                    stackHelper4.centerCurrentLine = stackHelper3.centreActive;
                }
                lineY += 1 + stackHelper4.currentFontLineHeight;
                do {
                    stackHelper4.leftPosition = this->lineLayoutTable[++lineY].leftBorder;
                } while (stackHelper4.leftPosition == -1);
                stackHelper4.currentFontLineHeight = stackHelper5.currentFontClass->lineHeight_0x14;
                if (this->useAlternateHelpTab) {
                    ++stackHelper4.local_134;
                    stackHelper3.local_100 = stackHelper4.local_11c;
                    stackHelper4.local_11c = stackHelper5.local_114;
                    if (0 < this->field51_0x2396c && 2 <= stackHelper4.local_134) {
                        stackHelper4.local_134 = -10000;
                        this->activeHelpHotspotIndex = stackHelper3.local_100 + stackHelper5.local_10c;
                        if (this->activeHelpHotspotIndex >= stackHelper5.local_114) {
                            this->activeHelpHotspotIndex = stackHelper5.local_114 - 1;
                        }
                        this->field51_0x2396c = 0;
                    }
                }
            }
            if (textWidth + stackHelper4.leftPosition > this->lineLayoutTable[lineY].rightBorder) {
                local_f8 = 0;
                if (stackHelper4.centerCurrentLine) {
                    local_f8 = this->lineLayoutTable[lineY].widthForCentering / 2;
                }
                stackHelper.wordLength = wcslen(stackHelper4.textToRender.text);
                for (int i = 0; i < stackHelper.wordLength; ++i) {
                    int wideCharWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth,
                        stackHelper5.currentFontClass)(stackHelper4.textToRender.text[i]);
                    while (this->lineLayoutTable[lineY].rightBorder < stackHelper4.leftPosition + wideCharWidth) {

                        if (stackHelper4.centerCurrentLine) {
                            this->lineLayoutTable[lineY].widthForCentering
                                = this->lineLayoutTable[lineY].rightBorder - stackHelper4.leftPosition;
                            stackHelper4.centerCurrentLine = stackHelper3.centreActive;
                        }
                        lineY += stackHelper4.currentFontLineHeight + 1;
                        if (this->useAlternateHelpTab && param_1 == 1) {
                            ++stackHelper4.local_134;
                            stackHelper3.local_100 = stackHelper4.local_11c;
                            stackHelper4.local_11c = stackHelper5.local_114 + i;
                            if (0 < this->field51_0x2396c && 2 <= stackHelper4.local_134) {
                                stackHelper4.local_134 = -10000;
                                this->activeHelpHotspotIndex = stackHelper3.local_100 + stackHelper5.local_10c;
                                if (this->activeHelpHotspotIndex >= stackHelper5.local_114 + i) {
                                    this->activeHelpHotspotIndex = stackHelper5.local_114 + i - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                        }
                        do {
                            stackHelper4.leftPosition = this->lineLayoutTable[lineY++].leftBorder;
                        } while (stackHelper4.leftPosition == -1);
                        if (stackHelper4.centerCurrentLine) {
                            local_f8 = this->lineLayoutTable[lineY].widthForCentering / 2;
                        }
                    }
                    if (this->useAlternateHelpTab && stackHelper5.local_114 + i == this->activeHelpHotspotIndex) {
                        stackHelper5.lineEndY = lineY + stackHelper4.currentFontLineHeight;
                        stackHelper2.lineStartY = lineY;
                        if (param_1 == 1) {
                            if (stackHelper4.local_12c) {
                                stackHelper5.local_10c = (i - stackHelper4.local_11c) + stackHelper5.local_114;
                                if (this->field51_0x2396c < 0) {
                                    this->activeHelpHotspotIndex = DAT_00df3348::instance + stackHelper3.local_100;
                                    if (this->activeHelpHotspotIndex >= stackHelper4.local_11c) {
                                        this->activeHelpHotspotIndex = stackHelper4.local_11c - 1;
                                    }
                                    this->field51_0x2396c = 0;
                                }
                                stackHelper4.local_134 = 0;
                                MACRO_CALL_MEMBER(
                                    UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                                    this->dialogContentX + local_f8 - 1 + stackHelper4.leftPosition,
                                    this->dialogContentY - this->helpContentScrollOffsetY + -1 + lineY,
                                    this->dialogContentX + local_f8 - 1 + stackHelper4.leftPosition,
                                    this->dialogContentY - this->helpContentScrollOffsetY + 1 + stackHelper5.lineEndY,
                                    COL_DARK_LIME::instance.shortValue);
                                MACRO_CALL_MEMBER(
                                    UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                                    this->dialogContentX + local_f8 + stackHelper4.leftPosition,
                                    this->dialogContentY - this->helpContentScrollOffsetY - 1 + lineY,
                                    this->dialogContentX + local_f8 + stackHelper4.leftPosition,
                                    this->dialogContentY - this->helpContentScrollOffsetY + 1 + stackHelper5.lineEndY,
                                    COL_DARK_LIME::instance.shortValue);
                                stackHelper2.local_e4 = TRUE;
                            }
                        }
                    }
                    if (param_1 == 1) {
                        int const newCharXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar,
                            stackHelper5.currentFontClass)(stackHelper4.textToRender.text[i],
                            this->dialogContentX + local_f8 + stackHelper4.leftPosition,
                            this->dialogContentY - this->helpContentScrollOffsetY + lineY, stackHelper4.charColor, 0);
                        stackHelper2.local_f0 = TRUE;
                        if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                this->dialogContentX + local_f8 + stackHelper4.leftPosition - this->helpContentScrollX,
                                this->dialogContentY - this->helpContentScrollOffsetY + lineY
                                    - this->helpContentScrollY,
                                newCharXPos - this->dialogContentX + local_f8 + stackHelper4.leftPosition,
                                stackHelper4.currentFontLineHeight + 2)) {
                            if (stackHelper4.local_12c) {
                                this->field49_0x23964 = stackHelper5.local_114 + i;
                                this->currentLinkId = stackHelper2.currentLinkId;
                            } else {
                                this->field49_0x23964 = stackHelper5.local_114;
                            }
                        }
                    }

                    stackHelper4.leftPosition += wideCharWidth;
                }
            } else {
                int charXPos = this->dialogContentX + stackHelper4.leftPosition;
                int charYPos = (this->dialogContentY - this->helpContentScrollOffsetY) + lineY;
                if (stackHelper4.centerCurrentLine) {
                    charXPos += this->lineLayoutTable[lineY].widthForCentering / 2;
                }
                stackHelper.wordLength = wcslen(stackHelper4.textToRender.text);
                for (int i = 0; i < stackHelper.wordLength; ++i) {
                    local_f8 = stackHelper5.local_114 - stackHelper4.local_11c;

                    if (this->useAlternateHelpTab && i + stackHelper5.local_114 == this->activeHelpHotspotIndex) {
                        if (param_1 == 1 && stackHelper4.local_12c) {
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(charXPos - 1, charYPos - 1, charXPos - 1,
                                charYPos + 1 + stackHelper4.currentFontLineHeight, COL_DARK_LIME::instance.shortValue);
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine,
                                DAT_PencilRenderCore::ptr)(charXPos, charYPos - 1, charXPos,
                                charYPos + 1 + stackHelper4.currentFontLineHeight, COL_DARK_LIME::instance.shortValue);
                            stackHelper2.local_e4 = TRUE;
                        }
                        stackHelper5.lineEndY = lineY + stackHelper4.currentFontLineHeight;
                        stackHelper2.lineStartY = lineY;
                        if (param_1 == 1) {
                            stackHelper4.local_134 = 0;
                            stackHelper5.local_10c = local_f8 + i;
                            if (this->field51_0x2396c < 0 && stackHelper4.local_12c) {
                                this->activeHelpHotspotIndex = stackHelper3.local_100 + DAT_00df3348::instance;
                                if (this->activeHelpHotspotIndex >= stackHelper4.local_11c) {
                                    this->activeHelpHotspotIndex = stackHelper4.local_11c - 1;
                                }
                                this->field51_0x2396c = 0;
                            }
                        }
                    }

                    if (param_1 == 1) {
                        stackHelper2.local_f0 = TRUE;
                        int oldCharPos = charXPos;
                        charXPos = MACRO_CALL_MEMBER(FontSizeClass_Func::renderWideChar, stackHelper5.currentFontClass)(
                            stackHelper4.textToRender.text[i], charXPos, charYPos, stackHelper4.charColor, 0);
                        if (MACRO_CALL_MEMBER(Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                                oldCharPos - this->helpContentScrollX, charYPos - this->helpContentScrollY,
                                charXPos - oldCharPos, stackHelper4.currentFontLineHeight + 2)) {
                            if (stackHelper4.local_12c) {
                                this->field49_0x23964 = i + stackHelper5.local_114;
                                this->currentLinkId = stackHelper2.currentLinkId;
                            } else {
                                this->field49_0x23964 = stackHelper5.local_114;
                            }
                        }
                    } else {
                        charXPos += MACRO_CALL_MEMBER(FontSizeClass_Func::getWideCharWidth,
                            stackHelper5.currentFontClass)(stackHelper4.textToRender.text[i]);
                    }
                }
                stackHelper4.leftPosition = stackHelper4.leftPosition + textWidth;
            }
        }
    }
}
}
