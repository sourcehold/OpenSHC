#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/HLP_WCHAR_Buffer.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D200
    LPWSTR TextEditorState::parseHLPPart(FILE* filePointer)
    {

        int finishedParsing = FALSE;
        int quoteActive = FALSE;
        int reachedWEOF = FALSE;
        wchar_t* bufferPtr = HLP_WCHAR_Buffer::instance;
        while (!reachedWEOF) {
            if (finishedParsing) {
                return HLP_WCHAR_Buffer::instance;
            }

            int readWChar = MACRO_CALL(OS_Func::_fgetwc)(filePointer);
            switch (readWChar) {
            case L'"':
                quoteActive ^= TRUE;
                continue;

            case L'\t':
            case L' ':
            case L',':
            case L'=':
                if (!quoteActive) {
                    int consumed = FALSE;
                    while (!reachedWEOF && !consumed) {
                        readWChar = MACRO_CALL(OS_Func::_fgetwc)(filePointer);

                        if (readWChar == WEOF) {
                            reachedWEOF = TRUE;
                            continue;
                        }

                        switch (readWChar) {
                        default:
                            MACRO_CALL(OS_Func::_fseek)(filePointer, -2, FILE_CURRENT);
                        case L'>':
                            consumed = true;
                        case L'\t':
                        case L' ':
                        case L',':
                        case L'=':
                            break;
                        }
                    }
                }
            case L'>':
                if (!quoteActive) {
                    finishedParsing = true;
                    *bufferPtr = L'\0';
                    continue;
                }
                break;

            case L'\n':
            case L'\r':
                continue;

            case WEOF:
                reachedWEOF = true;
                continue;
            }
            *bufferPtr++ = readWChar;
        }
        return NULL;
    }

}
}
