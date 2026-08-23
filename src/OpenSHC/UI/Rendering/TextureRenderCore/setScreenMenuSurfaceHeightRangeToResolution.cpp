#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044cd30
        void TextureRenderCore::setScreenMenuSurfaceHeightRangeToResolution()
        {
            this->screenMenuSurfaceHeightRange.start = 0;
            this->screenMenuSurfaceHeightRange.end = DAT_WindowAndDirectDraw::ptr->resolutionY;
        }

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
