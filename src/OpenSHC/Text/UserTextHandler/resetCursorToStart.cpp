#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004698C0
    void UserTextHandler::resetCursorToStart() { this->textCursorIndexArray[this->textArrayIndex] = 0; }

}
}
