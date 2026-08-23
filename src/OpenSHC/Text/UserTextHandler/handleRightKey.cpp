#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469880
    void UserTextHandler::handleRightKey()
    {
        if (this->textCursorIndexArray[this->textArrayIndex] < this->textContentLengthArray[this->textArrayIndex]) {
            this->textCursorIndexArray[this->textArrayIndex] += 1;
        }
    }

}
}
