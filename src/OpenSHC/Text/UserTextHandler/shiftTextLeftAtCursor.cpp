#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Shifts characters in the current text slot left by one position starting at index startIndex,
      repeating count times, deleting the character at startIndex and closing the gap.
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004698F0
    void UserTextHandler::shiftTextLeftAtCursor(int startIndex, int count)
    {
        for (int remaining = count; remaining != 0; --remaining) {
            this->textArray[this->textArrayIndex][startIndex]
                = this->textArray[this->textArrayIndex][startIndex + 1];
            ++startIndex;
        }
    }

}
}
