#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // fixme: the body runs once even when count is 0, reading textArray[textArrayIndex][startIndex - 1]
    // FUNCTION: STRONGHOLDCRUSADER 0x00469930
    void UserTextHandler::shiftTextRightAtCursor(int startIndex, int count)
    {
        this->textArray[this->textArrayIndex][count + startIndex + 1] = '\0';
        for (;;) {
            this->textArray[this->textArrayIndex][count + startIndex]
                = this->textArray[this->textArrayIndex][count + startIndex - 1];
            --count;
            if (count <= 0) {
                break;
            }
        }
    }

}
}
