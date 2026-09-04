#include "OpenSHC/Text/UserTextHandler.hpp"

namespace OpenSHC {

namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004698d0
    void UserTextHandler::moveCursorToEnd()
    {
        this->textCursorIndexArray[this->textArrayIndex] = this->textContentLengthArray[this->textArrayIndex];
    }

}
}
