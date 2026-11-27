#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Moves count characters of the current text slot one position to the left, starting at startIndex, which
      deletes the character at startIndex.
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004698F0
    void UserTextHandler::shiftTextLeftAtCursor(int startIndex, int count)
    {
        for (; count != 0; --count, ++startIndex) {
            this->textArray[this->textArrayIndex][startIndex] = this->textArray[this->textArrayIndex][startIndex + 1];
        }
    }

}
}
