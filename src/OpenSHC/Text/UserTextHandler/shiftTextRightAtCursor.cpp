#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextArrayIndexType.hpp"

namespace OpenSHC {
namespace Text {

    /*
        Shifts characters in the current text slot right by one position,
        making space for a new character insertion at the cursor. First places a null terminator at
        param_2 + param_1 + 1 to cap the string, then walks backward copying each character one position
        to the right. Used to implement character insertion in the text editor.
    */

    // FIXME: The logic here is completely unsafe, even compared to shiftTextLeftAtCursor. Even if count is 0, it will
    // shift at least 1. No idea if this is sound.

    // FUNCTION: STRONGHOLDCRUSADER 0x00469930
    void UserTextHandler::shiftTextRightAtCursor(int startIndex, int count)
    {
        this->textArray[this->textArrayIndex][count + startIndex + 1] = '\0';
        do {
            --count;
            this->textArray[this->textArrayIndex][count + startIndex]
                = this->textArray[this->textArrayIndex][count + startIndex - 1];
        } while (count > 0);
    }

}
}
