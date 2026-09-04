#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004698A0
    void UserTextHandler::handleLeftKey()
    {
        if (0 < this->textCursorIndexArray[this->textArrayIndex]) {
            this->textCursorIndexArray[this->textArrayIndex] -= 1;
        }
    }

}
}
