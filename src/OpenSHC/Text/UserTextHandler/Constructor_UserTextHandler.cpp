// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../UserTextHandler.func.hpp"

#include "OpenSHC/string-macros.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004694A0
    UserTextHandler* UserTextHandler::Constructor_UserTextHandler()
    {
        this->returnPressed = FALSE;
        this->textArrayIndex = OpenSHC::Text::TAIT_NINE__FILTER_B;

        this->textArrayFontSizes[0] = 17;
        this->textBoxMaxCharactersArray[0] = 256;
        this->textBoxMaxTextWidthDimensionArray[0] = 315;

        this->textArrayFontSizes[1] = 18;
        this->textBoxMaxCharactersArray[1] = 32;
        this->textBoxMaxTextWidthDimensionArray[1] = 200;
        strcpy(this->textArray[1], S_CAMPAIGN_NAME_STRING_005A59F0);
        this->textContentLengthArray[1] = strlen(this->textArray[1]);

        this->textArrayFontSizes[2] = 18;
        this->textBoxMaxCharactersArray[2] = 32;
        this->textBoxMaxTextWidthDimensionArray[2] = 180;
        this->textArray[2][0] = '\0';
        this->textContentLengthArray[2] = strlen(this->textArray[2]);

        this->textArrayFontSizes[3] = 18;
        this->textBoxMaxCharactersArray[3] = 32;
        this->textBoxMaxTextWidthDimensionArray[3] = 180;
        strcpy(this->textArray[3], S_GAME_LOAD_STRING_005A59DC);
        this->textContentLengthArray[3] = strlen(this->textArray[3]);

        this->textArrayFontSizes[4] = 19;
        this->textBoxMaxCharactersArray[4] = 249;
        this->textBoxMaxTextWidthDimensionArray[4] = 400;
        strcpy(this->textArray[4], "   ");
        this->textContentLengthArray[4] = strlen(this->textArray[4]);

        this->textArrayFontSizes[5] = 17;
        this->textBoxMaxCharactersArray[5] = 15;
        this->textBoxMaxTextWidthDimensionArray[5] = 200;

        this->textArrayFontSizes[6] = 17;
        this->textBoxMaxCharactersArray[6] = 5;
        this->textBoxMaxTextWidthDimensionArray[6] = 200;

        this->textArrayFontSizes[7] = 17;
        this->textBoxMaxCharactersArray[7] = 15;
        this->textBoxMaxTextWidthDimensionArray[7] = 200;

        this->textArrayFontSizes[9] = 17;
        this->textBoxMaxCharactersArray[9] = 2;
        this->textBoxMaxTextWidthDimensionArray[9] = 20;

        this->textArrayFontSizes[10] = 18;
        this->textBoxMaxCharactersArray[10] = 4;
        this->textBoxMaxTextWidthDimensionArray[10] = 60;
        strcpy(this->textArray[10], S_1181_005A59D4);
        this->textContentLengthArray[10] = strlen(this->textArray[10]);

        this->textArrayFontSizes[11] = 18;
        this->textBoxMaxCharactersArray[11] = 4;
        this->textBoxMaxTextWidthDimensionArray[11] = 60;
        strcpy(this->textArray[11], S_1181_005A59D4);
        this->textContentLengthArray[11] = strlen(this->textArray[11]);

        this->textArrayFontSizes[12] = 18;
        this->textBoxMaxCharactersArray[12] = 4;
        this->textBoxMaxTextWidthDimensionArray[12] = 60;
        this->textArray[12][0] = '\0';
        this->textContentLengthArray[12] = strlen(this->textArray[12]);

        this->textArrayFontSizes[13] = 18;
        this->textBoxMaxCharactersArray[13] = 4;
        this->textBoxMaxTextWidthDimensionArray[13] = 60;
        this->textArray[13][0] = '\0';
        this->textContentLengthArray[13] = strlen(this->textArray[13]);

        this->textArrayFontSizes[14] = 18;
        this->textBoxMaxCharactersArray[14] = 99;
        this->textBoxMaxTextWidthDimensionArray[14] = 385;
        this->textArray[14][0] = '\0';
        this->textContentLengthArray[14] = strlen(this->textArray[14]);

        this->textArrayFontSizes[15] = 18;
        this->textBoxMaxCharactersArray[15] = 32;
        this->textBoxMaxTextWidthDimensionArray[15] = 180;
        this->textArray[15][0] = '\0';
        this->textContentLengthArray[15] = strlen(this->textArray[15]);

        this->allowUserTextInput = FALSE;
        return this;
    }

}
}
