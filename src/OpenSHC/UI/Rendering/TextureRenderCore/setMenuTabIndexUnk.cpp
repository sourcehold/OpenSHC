#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00454EE0
        void TextureRenderCore::setMenuTabIndexUnk(int indexToSetToMinusOne)
        {
            this->activeMenuTabIndex = indexToSetToMinusOne + 1;
        }

    }
}
}
