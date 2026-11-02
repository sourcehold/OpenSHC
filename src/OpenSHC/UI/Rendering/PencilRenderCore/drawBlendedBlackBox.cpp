#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00471000
        void PencilRenderCore::drawBlendedBlackBox(int left, int top, int right, int bottom, int blendStrengh)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            BOOLEnum const _drawReady = MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(left, top, right, bottom, 0);
            if (_drawReady) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderBlendedBlackBox,
                    DAT_TextureRenderCoreObject::ptr)(this->drawStartX, (int)(this->drawStartY), (int)(this->drawEndX),
                    (int)(this->drawEndY), blendStrengh);
            }
        }

    }
}
}
