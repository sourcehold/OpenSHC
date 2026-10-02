#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004697C0
    char* UserTextHandler::getCurrentText()
    {
        if (this->unknown01 == 0) {
            return (char*)0x0;
        }
        return (char*)(this->textArray[this->textArrayIndex]);
    }

}
}
