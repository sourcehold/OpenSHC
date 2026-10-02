#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextArrayIndexType.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextArrayIndexType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004694A0
    void UserTextHandler::FUN_004694a0()
    {
        char (*pacVar1)[250];
        char (*pacVar2)[250];
        this->returnPressed = 0;
        this->textArrayIndex = OpenSHC::Text::TAIT_NINE__FILTER_B;
        this->textArrayFontSizes[0] = 0x11;
        this->textBoxMaxCharactersArray[0] = 0x100;
        this->textBoxMaxTextWidthDimensionArray[0] = 0x13b;
        this->textBoxMaxTextWidthDimensionArray[1] = 200;
        this->textArrayFontSizes[1] = 0x12;
        this->textBoxMaxCharactersArray[1] = 0x20;
        strcpy(this->textArray[1], "Campaign name string");
        pacVar1 = this->textArray + 1;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[1] = (int)(pacVar2 + -0x16dbc) + 0xe;
        this->textArrayFontSizes[2] = 0x12;
        this->textBoxMaxCharactersArray[2] = 0x20;
        this->textBoxMaxTextWidthDimensionArray[2] = 0xb4;
        this->textArray[2][0] = (*pacVar2)[0];
        pacVar1 = this->textArray + 2;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[2] = (int)(pacVar2 + -0x16dbd) + 0xe;
        this->textArrayFontSizes[3] = 0x12;
        this->textBoxMaxCharactersArray[3] = 0x20;
        this->textBoxMaxTextWidthDimensionArray[3] = 0xb4;
        strcpy(this->textArray[3], "Game load string");
        pacVar1 = this->textArray + 3;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[3] = (int)(pacVar2 + -0x16dbe) + 0xe;
        this->textArrayFontSizes[4] = 0x13;
        this->textBoxMaxCharactersArray[4] = 0xf9;
        this->textBoxMaxTextWidthDimensionArray[4] = 400;
        strcpy(this->textArray[4], "   ");
        pacVar1 = this->textArray + 4;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[4] = (int)(pacVar2 + -0x16dbf) + 0xe;
        this->textArrayFontSizes[5] = 0x11;
        this->textArrayFontSizes[6] = 0x11;
        this->textArrayFontSizes[7] = 0x11;
        this->textArrayFontSizes[9] = 0x11;
        this->textBoxMaxCharactersArray[5] = 0xf;
        this->textBoxMaxTextWidthDimensionArray[5] = 200;
        this->textBoxMaxTextWidthDimensionArray[6] = 200;
        this->textBoxMaxCharactersArray[7] = 0xf;
        this->textBoxMaxTextWidthDimensionArray[7] = 200;
        this->textBoxMaxCharactersArray[6] = 5;
        this->textBoxMaxCharactersArray[9] = 2;
        this->textBoxMaxTextWidthDimensionArray[9] = 0x14;
        this->textArrayFontSizes[10] = 0x12;
        this->textBoxMaxCharactersArray[10] = 4;
        this->textBoxMaxTextWidthDimensionArray[10] = 0x3c;
        strcpy(this->textArray[10], "1181");
        pacVar1 = this->textArray + 10;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[10] = (int)(pacVar2 + -0x16dc5) + 0xe;
        this->textArrayFontSizes[0xb] = 0x12;
        this->textBoxMaxCharactersArray[0xb] = 4;
        this->textBoxMaxTextWidthDimensionArray[0xb] = 0x3c;
        strcpy(this->textArray[0xb], "1181");
        pacVar1 = this->textArray + 0xb;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[0xb] = (int)(pacVar2 + -0x16dc6) + 0xe;
        this->textArrayFontSizes[0xc] = 0x12;
        this->textBoxMaxCharactersArray[0xc] = 4;
        this->textBoxMaxTextWidthDimensionArray[0xc] = 0x3c;
        this->textArray[0xc][0] = (*pacVar2)[0];
        pacVar1 = this->textArray + 0xc;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[0xc] = (int)(pacVar2 + -0x16dc7) + 0xe;
        this->textArrayFontSizes[0xd] = 0x12;
        this->textBoxMaxCharactersArray[0xd] = 4;
        this->textBoxMaxTextWidthDimensionArray[0xd] = 0x3c;
        this->textArray[0xd][0] = (*pacVar2)[0];
        pacVar1 = this->textArray + 0xd;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[0xd] = (int)(pacVar2 + -0x16dc8) + 0xe;
        this->textArrayFontSizes[0xe] = 0x12;
        this->textBoxMaxCharactersArray[0xe] = 99;
        this->textBoxMaxTextWidthDimensionArray[0xe] = 0x181;
        this->textArray[0xe][0] = (*pacVar2)[0];
        pacVar1 = this->textArray + 0xe;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[0xe] = (int)(pacVar2 + -0x16dc9) + 0xe;
        this->textArrayFontSizes[0xf] = 0x12;
        this->textBoxMaxCharactersArray[0xf] = 0x20;
        this->textBoxMaxTextWidthDimensionArray[0xf] = 0xb4;
        this->textArray[0xf][0] = (*pacVar2)[0];
        pacVar1 = this->textArray + 0xf;
        do {
            pacVar2 = pacVar1;
            pacVar1 = (char (*)[250])(*pacVar2 + 1);
        } while ((*pacVar2)[0] != '\0');
        this->textContentLengthArray[0xf] = (int)(pacVar2 + -0x16dca) + 0xe;
        this->allowUserTextInput = 0;
    }

}
}
