#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/Text/TextArrayIndexTypeInt.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextArrayIndexType;
    using OpenSHC::Text::TextArrayIndexTypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x00469790
    void UserTextHandler::resetToTextIndex(int textIndex)

    {
        if ((this->allowUserTextInput == 0) && (textIndex < ((TextArrayIndexType)0x10))) {
            this->textArrayIndex = textIndex;
            this->textCursorIndexArray[textIndex] = 0;
            this->unknown01 = 1;
            this->returnPressed = 0;
        }
        return;
    }

}
}
