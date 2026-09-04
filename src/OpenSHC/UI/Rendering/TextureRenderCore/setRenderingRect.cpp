#include "../TextureRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00454990
        void TextureRenderCore::setRenderingRect(int xPos, int yPos, int width, int heigth)
        {
            this->renderingRect_16c854.left = xPos;
            this->renderingRect_16c854.top = yPos;
            this->renderingRect_16c854.right = width;
            this->renderingRect_16c854.bottom = heigth;
        }

    }
}
}
