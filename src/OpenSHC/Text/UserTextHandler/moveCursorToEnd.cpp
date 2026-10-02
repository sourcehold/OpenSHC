#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004698D0
    void UserTextHandler::moveCursorToEnd()
    {
        this->textCursorIndexArray[this->textArrayIndex] = this->textContentLengthArray[this->textArrayIndex];
        return;
    }

}
}
