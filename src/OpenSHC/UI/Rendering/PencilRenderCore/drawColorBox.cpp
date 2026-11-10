#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00470E90
        void PencilRenderCore::drawColorBox(int left, int top, int right, int bottom, ushort color)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            if (!MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                    left, top, right, bottom, color)) {
                return;
            }
            for (; this->currentHeight_0x2c >= 0; --this->currentHeight_0x2c, ++this->drawStartY) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
            }
        }

    }
}
}
