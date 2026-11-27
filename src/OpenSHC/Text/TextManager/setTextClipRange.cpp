#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00469F20
    void TextManager::setTextClipRange(dword param_1, dword param_2)
    {
        this->textClipMin = param_1;
        this->textClipMax = param_2;
        return;
    }

}
}
