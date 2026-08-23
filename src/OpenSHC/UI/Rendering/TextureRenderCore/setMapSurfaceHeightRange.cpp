#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044cca0
        void TextureRenderCore::setMapSurfaceHeightRange(int start, int end)
        {
            this->mapGameSurfaceHeightRange.start = start;
            this->mapGameSurfaceHeightRange.end = end;
        }
    }
}
}
