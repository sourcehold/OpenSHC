#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004698A0
    void UserTextHandler::handleLeftKey()
    {
        if (0 < this->textCursorIndexArray[this->textArrayIndex]) {
            this->textCursorIndexArray[this->textArrayIndex] = this->textCursorIndexArray[this->textArrayIndex] + -1;
        }
        return;
    }

}
}
