#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469790
    void UserTextHandler::resetToTextIndex(int textIndex)
    {
        if (!this->allowUserTextInput && textIndex >= 0 && textIndex <= 15) {
            this->textArrayIndex = textIndex;
            this->textCursorIndexArray[textIndex] = 0;
            this->unknown01 = 1;
            this->returnPressed = FALSE;
        }
    }

}
}
