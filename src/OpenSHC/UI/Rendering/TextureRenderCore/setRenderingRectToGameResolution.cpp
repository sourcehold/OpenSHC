#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00454960
        void TextureRenderCore::setRenderingRectToGameResolution()
        {
            this->renderingRect_16c854.left = 0;
            this->renderingRect_16c854.top = 0;
            this->renderingRect_16c854.right = DAT_WindowAndDirectDraw::instance.resolutionX;
            this->renderingRect_16c854.bottom = DAT_WindowAndDirectDraw::instance.resolutionY;
        }

    }
}
}
