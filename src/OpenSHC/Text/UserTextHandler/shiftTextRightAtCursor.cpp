#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextArrayIndexType.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextArrayIndexType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00469930
    void UserTextHandler::shiftTextRightAtCursor(int startIndex, int count)
    {
        this->textArray[this->textArrayIndex][count + startIndex + 1] = '\0';
        int next;
        do {
            /*
              Moves everything an index forward to make space for the new char.   --TheRedDaemon
             */
            next = count + -1;
            /*
              write character
             */
            this->textArray[this->textArrayIndex][count + startIndex]
                = this->textArray[this->textArrayIndex - OpenSHC::Text::TAIT_ONE__FILTER_B]
                                 [count + startIndex + 0xf9];
            count = next;
        } while (0 < next);
    }

}
}
