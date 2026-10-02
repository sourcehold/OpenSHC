#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469800
    void UserTextHandler::setTextEntryAndUpdateCursor(int textIndex, char* text)
    {
        char* destination = this->textArray[textIndex];
        char* source = text;
        char character;
        do {
            character = *source;
            *destination = character;
            ++destination;
            ++source;
        } while (character != '\0');

        source = text;
        char* afterFirst = text + 1;
        do {
            character = *source;
            ++source;
        } while (character != '\0');
        this->textContentLengthArray[textIndex] = source - afterFirst;

        source = text;
        afterFirst = text + 1;
        do {
            character = *source;
            ++source;
        } while (character != '\0');
        this->textCursorIndexArray[textIndex] = source - afterFirst;
    }

}
}
