#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CCF0
        void TextureRenderCore::restoreMapSurfaceHeightRangeFromTemporaryUnk()
        {
            this->mapGameSurfaceHeightRange.start = this->mapSurfaceRangeTemporaryUnk_0x16c864.start;
            this->mapGameSurfaceHeightRange.end = this->mapSurfaceRangeTemporaryUnk_0x16c864.end;
        }

    }
}
}
