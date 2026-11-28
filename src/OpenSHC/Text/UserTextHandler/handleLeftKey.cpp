#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004698A0
    void UserTextHandler::handleLeftKey()
    {
        if (this->textCursorIndexArray[this->textArrayIndex] > 0) {
            --this->textCursorIndexArray[this->textArrayIndex];
        }
    }

}
}
