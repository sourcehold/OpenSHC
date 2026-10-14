// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469800
    void UserTextHandler::setTextEntryAndUpdateCursor(int textIndex, char* text)
    {
        strcpy(this->textArray[textIndex], text);
        this->textContentLengthArray[textIndex] = strlen(text);
        this->textCursorIndexArray[textIndex] = strlen(text);
    }

}
}
