#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00468F20
        void PencilRenderCore::drawCurrentPixel()
        {
            *(ushort*)((int)this->surfacePtr + this->currentY * this->horizontalByteSize + this->currentX * 2)
                = this->drawColor;
        }

    }
}
}
