#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469F40
    void TextManager::resetTextClipRange()
    {
        this->textClipMin = 0;
        this->textClipMax = 10000;
    }

}
}
