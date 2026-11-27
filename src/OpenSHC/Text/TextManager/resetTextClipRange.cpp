#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00469F40
    void TextManager::resetTextClipRange()
    {
        this->textClipMin = 0;
        this->textClipMax = 10000;
        return;
    }

}
}
