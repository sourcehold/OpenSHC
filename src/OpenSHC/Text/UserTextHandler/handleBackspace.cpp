#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004715A0
    void UserTextHandler::handleBackspace()
    {
        char* pcVar1;
        char (*pacVar2)[250];
        if (0 < this->textCursorIndexArray[this->textArrayIndex]) {
            this->textCursorIndexArray[this->textArrayIndex] = this->textCursorIndexArray[this->textArrayIndex] + -1;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::shiftTextLeftAtCursor, this)(
                this->textCursorIndexArray[this->textArrayIndex],
                (int)((int)(this->textContentLengthArray[this->textArrayIndex]
                    - this->textCursorIndexArray[this->textArrayIndex])));
            pacVar2 = this->textArray + this->textArrayIndex;
            do {
                pcVar1 = *pacVar2;
                pacVar2 = (char (*)[250])(*pacVar2 + 1);
            } while (*pcVar1 != '\0');
            this->textContentLengthArray[this->textArrayIndex]
                = (int)pacVar2 - (this->textArrayIndex * 0xfa + 0x1652891);
        }
        return;
    }

}
}
