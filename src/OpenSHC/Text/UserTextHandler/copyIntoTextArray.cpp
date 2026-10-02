#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472C30
    void UserTextHandler::copyIntoTextArray(char* param_1)
    {
        char cVar1;
        char* pcVar2;
        char (*_pText)[250];
        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::clearTextAndCursor, this)();
        _pText = this->textArray + this->textArrayIndex;
        pcVar2 = param_1;
        do {
            cVar1 = *pcVar2;
            (*_pText)[0] = cVar1;
            pcVar2 = pcVar2 + 1;
            _pText = (char (*)[250])(*_pText + 1);
        } while (cVar1 != '\0');
        pcVar2 = param_1;
        do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        this->textContentLengthArray[this->textArrayIndex] = (int)pcVar2 - (int)(param_1 + 1);
        pcVar2 = param_1 + 1;
        do {
            cVar1 = *param_1;
            param_1 = param_1 + 1;
        } while (cVar1 != '\0');
        this->textCursorIndexArray[this->textArrayIndex] = (int)param_1 - (int)pcVar2;
        this->unknown01 = 1;
        this->returnPressed = 0;
        return;
    }

}
}
