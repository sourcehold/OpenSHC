#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472D00
    void UserTextHandler::handleDeleteKey()
    {
        char* pcVar1;
        int iVar2;
        char (*pacVar3)[250];
        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::isTextInputAtCapacity, this)();
        if (iVar2 != 2) {
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::shiftTextLeftAtCursor, this)(
                this->textCursorIndexArray[this->textArrayIndex],
                (int)((int)(this->textContentLengthArray[this->textArrayIndex]
                    - this->textCursorIndexArray[this->textArrayIndex])));
            pacVar3 = this->textArray + this->textArrayIndex;
            do {
                pcVar1 = *pacVar3;
                pacVar3 = (char (*)[250])(*pacVar3 + 1);
            } while (*pcVar1 != '\0');
            this->textContentLengthArray[this->textArrayIndex]
                = (int)pacVar3 - (this->textArrayIndex * 0xfa + 0x1652891);
        }
        return;
    }

}
}
