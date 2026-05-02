/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/FontSizeClass.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/FontRenderTypeInt.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Text {

    using OpenSHC::IO::Graphics::GmIDInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::FontRenderTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00000024
    class FontSizeClass {
    public:
        GmIDInt fontGmID_0x0; // 0x00000000 length: 4
        dword numberOfFontStartInGm_0x4; // 0x00000004 length: 4
        int fontStartImageId_0x8; // 0x00000008 length: 4
        FontRenderTypeInt renderType_0xc; // 0x0000000C length: 4
        int baselineOffset_0x10; // 0x00000010 length: 4
        dword lineHeight_0x14; // 0x00000014 length: 4
        int letterSpacing_0x18; // 0x00000018 length: 4
        int whiteSpaceWidth_0x1c; // 0x0000001C length: 4
        HGDIOBJ hgdiobj; // 0x00000020 length: 4

    private:
        FontSizeClass(FontSizeClass const&);
        void operator=(FontSizeClass const&);

        FontSizeClass();
        ~FontSizeClass();

    public:
        void setupFontSizeClassObject(GmIDInt fontGmID, int numberOfFontStartInGm, FontRenderTypeInt renderType,
            int baselineOffset, int lineHeight, int letterSpacing, int whiteSpaceWidth);

        int getWidthOfText(char* text, int length);

        int getWordStartingFromPos(
            char* text, int startAndRunIndex, char* wordReceiver, int maxWordBufferSize, int* wordStartIndexOutPtr);

        void meth_0x469c40(char* text, int allowedWidth);

        int getCharWidthUnk(byte charUnk);

        int getWidthOfWideText(LPWSTR wideText, int numberOfChars);

        dword meth_0x471670(WCHAR wChar);

        int renderText(char* text, int textLength, int xPos, int yPos, BGR24 color, int blendStrength);

        int renderMultilineTextUnk(
            char* text, int xPos, int yPos, int maxWidth, BGR24 color, int blendStrength, int modeUnk);

        int renderMultilineWideTextUnk(
            LPWSTR _wideText, int xPos, int yPos, int maxWidth, uint color, int blendStrength, int modeUnk);

        void renderSomeSpecificTextUnk(int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, BGR24 color);

        int renderCharUnk(char charId, int xPos, int yPosUnk, int bgr24, int blendStrengthUnk);

        void renderWideText(LPWSTR wideText, int textLength, int xPos, int yPos, BGR24 color, int blendStrength);

        void meth_0x473830(undefined4 param_1, int param_2, int param_3, int param_4, int param_5);
    };

    static_assert_cpp98_obj(sizeof(FontSizeClass) == 36, FontSizeClass);

#pragma pack(pop)

} // namespace Text
} // namespace OpenSHC
