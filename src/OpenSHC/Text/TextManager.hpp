/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Text/TextManager.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eTextSectionsInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/Text/FontSizeClass.hpp"
#include "OpenSHC/Text/GameLanguageInt.hpp"
#include "OpenSHC/Text/TextAlignmentInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/CodePageInt.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Text {

    using OpenSHC::DE::SHCDE::eTextSectionsInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTargetInt;
    using OpenSHC::Text::FontSizeClass;
    using OpenSHC::Text::GameLanguageInt;
    using OpenSHC::Text::TextAlignmentInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::WindowsHelper::Enums::CodePageInt;

#pragma pack(push, 1)

    // SIZE: 0x00057274
    class TextManager {
    public:
        int currentXOffset_0x0; // 0x00000000 length: 4
        dword field1_0x4; // 0x00000004 length: 4
        dword field2_0x8; // 0x00000008 length: 4
        dword field3_0xc; // 0x0000000C length: 4
        CodePageInt codePage; // 0x00000010 length: 4
        dword field5_0x14; // 0x00000014 length: 4
        dword field6_0x18; // 0x00000018 length: 4
        RenderTargetInt textSurfaceTarget; // 0x0000001C length: 4
        dword field8_0x20; // 0x00000020 length: 4
        int field9_0x24; // 0x00000024 length: 4
        int field10_0x28; // 0x00000028 length: 4
        dword field11_0x2c; // 0x0000002C length: 4
        dword field12_0x30; // 0x00000030 length: 4
        dword field13_0x34; // 0x00000034 length: 4
        dword textColor; // 0x00000038 length: 4
        int sizeOfOneFontSet_0x3c; // 0x0000003C length: 4
        BOOLEnum alternativeCodePageUsedUnk; // 0x00000040 length: 4
        GameLanguageInt gameLanguage; // 0x00000044 length: 4
        FontSizeClass fontSizeClassArray[20]; // 0x00000048 length: 720
        char stringArray1[32][128]; // 0x00000318 length: 4096
        dword count1; // 0x00001318 length: 4
        undefined1 padding_0x131c[4]; // 0x0000131C length: 4
        char integerTextBuffer[20]; // 0x00001320 length: 20
        char field26_0x1334[20]; // 0x00001334 length: 20
        dword field27_0x1348; // 0x00001348 length: 4
        int textOffsets[260]; // 0x0000134C length: 1040
        char textStart[351000]; // 0x0000175C length: 351000

    private:
        TextManager(TextManager const&);
        void operator=(TextManager const&);

        TextManager();
        ~TextManager();

    public:
        void renderInGameText(char* textAddress, int xParam, int yParam, TextAlignmentInt alignment, uint color1,
            uint color2, int fontSize, BOOLEnum keepOffsetX);

        void renderTextToScreen2(char* textAddress, int xParam, int yParam, TextAlignmentInt alignment, BGR24 color,
            int fontSize, BOOLEnum keepOffsetX);

        void renderText(eTextSectionsInt textGroupIndex, int textNumInGroup, int xPosition, int yPosition,
            TextAlignmentInt textShift, uint color, uint param_7, int fontSize, BOOLEnum param_9);

        void renderText2(eTextSectionsInt textOffsetIndex, int textNumInGroup, int xParam, int yParam,
            TextAlignmentInt alignment, uint color, int fontSize, BOOLEnum keepOffsetX);

        void renderInGameText2(eTextSectionsInt textOffsetIndex, int textNumInGroup, int xParam, int yParam,
            TextAlignmentInt alignment, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX,
            int blendStrength);

        void renderTextFromTextGroup(eTextSectionsInt offsetIndex, int numInGroup, int xParam, int yParam,
            TextAlignmentInt alignment, uint color, int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        void renderMultilineText2(eTextSectionsInt param_1, int param_2, int param_3, int param_4);

        void renderMultilineTextUnk(eTextSectionsInt textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color, int fontSize, int blendStrength);

        void renderMultilineText2Unk(eTextSectionsInt textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color, int fontSize);

        void renderMultilineText3Unk(eTextSectionsInt textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color1, uint color2, int fontSize, int blendStrength);

        void renderMultilineText4Unk(eTextSectionsInt textOffsetIndex, int textNumInGroup, int xPos, int yPos,
            int maxWidth, uint color, int fontSize, int blendStrength);

        void renderNumber(
            int number, int xPosition, int yPosition, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX);

        void renderLeftAlignedNumberToScreen(
            int number, int xParam, int yParam, uint color, int fontSize, BOOL keepOffsetX);

        void renderNumberToScreen(int number, int xParam, int yParam, TextAlignmentInt alignment, uint color,
            int fontSize, BOOLEnum keepOffsetX);

        int computeTextWidthForTextGroup(eTextSectionsInt textOffsetIndex, int textNumInGroup, int fontSize);

        void setupFontSizeClassObjects();

        void meth_0x469f20(dword param_1, dword param_2);

        void meth_0x469f40();

        void trimText(char* text, int allowedWidth, int fontSize);

        int getTextWidthTillCursorUnk(char* text, int cursorIndex, int fontSize);

        void fillIntegerTextBuffer(int numberInt);

        char* getTextStringInGroupAtOffset(eTextSectionsInt offsetIndex, int numInGroup);

        int renderPartOfNumberUnk(int numberToRenderUnk, int xPosUnk, int yPosUnk, int integerPartToRenderUnk,
            int bgr24, int digitSet, BOOL useCurrentXOffsetUnk);

        int FUN_0046a4d0(int param_1, int param_2);

        int getCharWidth(char char_, int fontSize);

        int computeTextWidth(char* text, int fontSize);

        int meth_0x4716d0(int param_1, int param_2);

        void loadCRTex();

        void renderMultilineText5Unk(
            char* text, int xPos, int yPos, int maxWidth, uint color, int fontSize, int blendStrength);

        void renderMultilineText6Unk(
            char* text, int xPos, int yPos, int maxWidth, uint color1, uint color2, int fontSize, int blendStrength);

        void renderMultilineWideTextUnk(LPWSTR _wideText, int xPos, int yPos, int maxWidth, uint color1, uint color2,
            int fontSize, int blendStrength);

        void renderSomeSpecificTextUnk(
            int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, uint color, int fontSize);

        void renderTextToScreen(char* textAddress, int xParam, int yParam, TextAlignmentInt alignment, BGR24 color,
            int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        void renderWideText(LPWSTR wideText, int xPos, int yPos, TextAlignmentInt alignment, uint color, int fontSize,
            BOOL keepXOffset, int blendStrength);

        void renderNumber2(int integer, int xPosition, int yPosition, TextAlignmentInt textShift, uint color,
            uint param_6, int fontSize, BOOLEnum param_8, int param_9);

        void renderNumberToScreen2(int number, int xParam, int yParam, TextAlignmentInt alignment, uint color,
            int fontSize, BOOLEnum keepOffsetX, int blendStrength);

        void renderInGameTextWithShadow(char* textAddress, int xParam, int yParam, TextAlignmentInt alignment,
            uint foregroundColor, uint backgroundColor, int fontSize, BOOLEnum keepOffsetX, int blendStrength);
    };

    static_assert_cpp98_obj(sizeof(TextManager) == 356980, TextManager);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(TextManager, false, Address::SHC_3BB0A8C1_0x02157578) pDAT_TextManager;

} // namespace Text
} // namespace OpenSHC
