#include "../FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469B90
    int FontSizeClass::getWordStartingFromPos(
        char* text, int startAndRunIndex, char* wordReceiver, int maxWordBufferSize, int* wordStartIndexOutPtr)
    {
        if (!text || !wordReceiver || text[startAndRunIndex] == '\0') {
            return 0;
        }

        if (DAT_TextManagerObject::instance.field12_0x30) {
            *wordReceiver = text[startAndRunIndex];
            wordReceiver[1] = '\0';
            *wordStartIndexOutPtr = 0;
            return 1;
        }

        int wordStartIndex = -1;
        char _charHolder;
        do {
            _charHolder = text[startAndRunIndex];
            ++startAndRunIndex;
            ++wordStartIndex;
            if (_charHolder == '\0') {
                return 0;
            }
        } while (_charHolder == ' ');
        *wordStartIndexOutPtr = wordStartIndex;
        *wordReceiver = _charHolder;

        int wordIndexAndLength;
        for (wordIndexAndLength = 1; wordIndexAndLength < maxWordBufferSize; ++wordIndexAndLength) {
            char currentChar = text[startAndRunIndex];
            ++startAndRunIndex;
            if (currentChar == '\0' || currentChar == ' ') {
                break;
            }
            wordReceiver[wordIndexAndLength] = currentChar;
        }
        wordReceiver[wordIndexAndLength] = '\0';
        return wordIndexAndLength;
    }

}
}
