#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004698F0
    void UserTextHandler::shiftTextLeftAtCursor(int startIndex, int count)
    {
        for (; count != 0; --count, ++startIndex) {
            this->textArray[this->textArrayIndex][startIndex] = this->textArray[this->textArrayIndex][startIndex + 1];
        }
    }

}
}
