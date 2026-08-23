#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CCD0
        void TextureRenderCore::temporarySaveMapSurfaceHeightRangeUnk()

        {
            this->mapSurfaceRangeTemporaryUnk_0x16c864.start = this->mapGameSurfaceHeightRange.start;
            this->mapSurfaceRangeTemporaryUnk_0x16c864.end = this->mapGameSurfaceHeightRange.end;
        }

    }
}
}
