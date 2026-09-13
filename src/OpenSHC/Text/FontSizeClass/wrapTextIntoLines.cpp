// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../FontSizeClass.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469C40
    void FontSizeClass::wrapTextIntoLines(char* text, int allowedWidth)
    {
        int const _textLength = strlen(text);
        int const _textWidth
            = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText, this)(text, _textLength);
        int currentIndexInLine = 0;
        int wordCutIndex = 0;
        int currentWidthOfLine = 0;
        int wordsInLine = 0;
        int const whiteSpaceWidth = this->whiteSpaceWidth_0x1c;
        int lineIndex = 0;

        DAT_TextManagerObject::instance.count1 = 0;
        if (_textLength <= 0) {
            return;
        }

        if (_textWidth <= allowedWidth && _textLength <= 127) {
            strcpy(DAT_TextManagerObject::instance.stringArray1[0], text);
            DAT_TextManagerObject::instance.count1 = 1;
        } else if (_textWidth > allowedWidth) {
            do {
                char _wordReceiver[64];
                int _wordStartIndex;
                int _wordLengthWithoutNull
                    = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWordStartingFromPos, this)(
                        text, wordCutIndex, _wordReceiver, sizeof(_wordReceiver) - 1, &_wordStartIndex);

                if (_wordLengthWithoutNull == 0)
                    break;

                wordCutIndex += _wordStartIndex + _wordLengthWithoutNull;
                int _wordWidth = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText, this)(
                    _wordReceiver, _wordLengthWithoutNull);

                if (_wordWidth > allowedWidth) {
                    DAT_TextManagerObject::instance.count1 = 0;
                    return;
                }

                if (_wordWidth + currentWidthOfLine > allowedWidth && wordsInLine) {
                    DAT_TextManagerObject::instance.stringArray1[lineIndex][currentIndexInLine] = '\0';
                    ++lineIndex;

                    currentWidthOfLine = 0;
                    wordsInLine = 0;
                    if (32 <= lineIndex) {
                        lineIndex = 31;
                        break;
                    }
                    currentIndexInLine = 0;
                }

                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    &DAT_TextManagerObject::instance.stringArray1[lineIndex][currentIndexInLine], s__s_005a5a08,
                    _wordReceiver);

                ++wordsInLine;
                currentWidthOfLine += _wordWidth + whiteSpaceWidth; // printf adds "%s "
                currentIndexInLine += 1 + _wordLengthWithoutNull; // printf adds "%s "
            } while (wordCutIndex < _textLength);
            DAT_TextManagerObject::instance.stringArray1[lineIndex][currentIndexInLine] = '\0';
            DAT_TextManagerObject::instance.count1 = lineIndex + 1;
        }
    }

}
}
