#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472EF0
    int FontSizeClass::renderMultilineTextUnk(
        char* text, int xPos, int yPos, int maxWidth, BGR24 color, int blendStrength, int modeUnk)
    {
        int _textLength = strlen(text);
        int _widthOfWholeText = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, this)(text, _textLength);

        int _runXPos = xPos;
        int _runYPos = yPos;

        int const maxXPosition = maxWidth + xPos;

        int finalTextWidth = 0;
        int _nextWordCutStartIndex = 0;
        int writtenWords = 0;
        int local_68 = 0;

        int singleLineHeight = (this->lineHeight_0x14 * 38) / 32;
        int yLineOffset = singleLineHeight;
        int whiteSpaceWidth = this->whiteSpaceWidth_0x1c;

        int alternateLineHeight = DAT_TextManagerObject::instance.field13_0x34;
        if (alternateLineHeight) {
            singleLineHeight = alternateLineHeight;
        }

        if (DAT_TextManagerObject::instance.field12_0x30) {
            whiteSpaceWidth = 0;
        }

        DAT_TextManagerObject::instance.field1_0x4 = 0;
        if (_textLength <= 0) {
            return 0;
        }

        if (_widthOfWholeText <= maxWidth) {
            DAT_TextManagerObject::instance.field1_0x4 = singleLineHeight;
            if (modeUnk == 0) {
                MACRO_CALL_MEMBER(FontSizeClass_Func::renderText, this)(
                    text, _textLength, _runXPos, _runYPos, color, blendStrength);
                return _widthOfWholeText;
            } else if (modeUnk == 1) {
                return yLineOffset;
            } else if (modeUnk == 2) {
                return _widthOfWholeText;
            }
        }

        do {
            char _wordReceiver[64];
            int _wordStartIndex;
            int wordLength = MACRO_CALL_MEMBER(FontSizeClass_Func::getWordStartingFromPos, this)(
                text, _nextWordCutStartIndex, _wordReceiver, sizeof(_wordReceiver) - 1, &_wordStartIndex);
            if (!wordLength) {
                break;
            }
            _nextWordCutStartIndex += _wordStartIndex + wordLength;
            int _wordWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, this)(_wordReceiver, wordLength);
            if (_wordWidth > maxWidth) {
                int charWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getCharWidthUnk, this)('-');

                int renderedChars = 0;
                do {
                    int remainingWidth = maxXPosition - charWidth - _runXPos;
                    int wordReceiverBufferLength = strlen(_wordReceiver) + 1;
                    int length = 1;
                    for (; length < wordReceiverBufferLength; ++length) {
                        if (MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, this)(_wordReceiver, length)
                            > remainingWidth) {
                            break;
                        }
                    }
                    --length;

                    if (length < 1) {
                        if (writtenWords == 0) {
                            break;
                        }
                    } else {

                        int iVar1 = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, this)(_wordReceiver, length);

                        if (modeUnk == 0) {
                            MACRO_CALL_MEMBER(FontSizeClass_Func::renderText, this)(
                                _wordReceiver, length, _runXPos, _runYPos, color, blendStrength);
                        }

                        renderedChars += length;
                        _runXPos += iVar1;

                        if (renderedChars >= wordLength) {
                            break;
                        }

                        if (modeUnk == 0) {
                            MACRO_CALL_MEMBER(FontSizeClass_Func::renderText, this)(
                                "-", sizeof(char), _runXPos, _runYPos, color, blendStrength);
                        }

                        for (int i = 0; i < (int)sizeof(_wordReceiver); ++i) {
                            _wordReceiver[i] = _wordReceiver[length + i];
                            if (_wordReceiver[i] == '\0') {
                                break;
                            }
                        }
                    }

                    int possibleWidth = _runXPos - xPos;
                    if (possibleWidth > finalTextWidth) {
                        finalTextWidth = possibleWidth;
                    }
                    _runXPos = xPos;

                    _runYPos += singleLineHeight;
                    yLineOffset += singleLineHeight;
                    writtenWords = 0;

                    if (DAT_TextManagerObject::instance.field12_0x30) {
                        local_68 = 1;
                    }
                } while (renderedChars < wordLength && local_68 == 0);
                ++writtenWords;
                _runXPos += whiteSpaceWidth;
                continue;
            }

            if (_wordWidth + _runXPos > maxXPosition && writtenWords != 0) {
                int possibleWidth = _runXPos - xPos;
                if (possibleWidth > finalTextWidth) {
                    finalTextWidth = possibleWidth;
                }
                _runXPos = xPos;

                _runYPos += singleLineHeight;
                yLineOffset += singleLineHeight;
                writtenWords = 0;

                DAT_TextManagerObject::instance.field1_0x4 += singleLineHeight;
                if (DAT_TextManagerObject::instance.field12_0x30) {
                    break;
                }
            }

            if (modeUnk == 0) {
                MACRO_CALL_MEMBER(FontSizeClass_Func::renderText, this)(
                    _wordReceiver, wordLength, _runXPos, _runYPos, color, blendStrength);
            }

            ++writtenWords;
            _runXPos += _wordWidth + whiteSpaceWidth;
        } while (_nextWordCutStartIndex < _textLength && local_68 == 0);

        int possibleWidth = _runXPos - xPos;
        if (possibleWidth > finalTextWidth) {
            finalTextWidth = possibleWidth;
        }

        if (writtenWords != 0) {
            DAT_TextManagerObject::instance.field1_0x4 += singleLineHeight;
        }

        if (modeUnk == 1) {
            if (writtenWords == 0) {
                yLineOffset -= singleLineHeight;
            }
            return yLineOffset;
        }
        return finalTextWidth;
    }

}
}
