#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Moves count characters of the current text slot one position to the right, starting at startIndex, to make
      room for an inserted character, and terminates the string one past its new end.
     */
    // fixme: the do-while copies once even when count is 0, reading textArray[textArrayIndex][startIndex - 1]
    // FUNCTION: STRONGHOLDCRUSADER 0x00469930
    void UserTextHandler::shiftTextRightAtCursor(int startIndex, int count)
    {
        this->textArray[this->textArrayIndex][count + startIndex + 1] = '\0';
        do {
            this->textArray[this->textArrayIndex][count + startIndex]
                = this->textArray[this->textArrayIndex][count + startIndex - 1];
            --count;
        } while (count > 0);
    }

}
}
