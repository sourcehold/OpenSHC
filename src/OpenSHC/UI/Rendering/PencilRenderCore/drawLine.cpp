#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00472B20
        void PencilRenderCore::drawLine(int x1, int y1, int x2, int y2, ushort color)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            if (!MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                    x1, y1, x2, y2, color)) {
                return;
            }
            if (this->currentWidth_0x28 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawVerticalLine, this)();
                return;
            }
            if (this->currentHeight_0x2c == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                return;
            }
            if (this->currentHeight_0x2c > this->currentWidth_0x28) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawDiagonalHeigherThanWideUnk, this)();
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawDiagonalWiderThanHighUnk, this)();
        }

    }
}
}
