#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Zeroes textCursorIndexArray for the current textArrayIndex, resetting the text editing cursor to   the beginning
      of the active text slot.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004698C0
    void UserTextHandler::resetCursorToStart()
    {
        this->textCursorIndexArray[this->textArrayIndex] = 0;
        return;
    }

}
}
