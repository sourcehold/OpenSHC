#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469870
    void UserTextHandler::handleReturnKey()
    {
        this->returnPressed = 1;
        return;
    }

}
}
