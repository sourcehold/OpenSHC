#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469F20
    void TextManager::setTextClipRange(dword clipMin, dword clipMax)
    {
        this->textClipMin = clipMin;
        this->textClipMax = clipMax;
    }

}
}
