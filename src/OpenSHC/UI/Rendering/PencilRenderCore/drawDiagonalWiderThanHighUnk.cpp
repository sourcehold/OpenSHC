#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00471280
        void PencilRenderCore::drawDiagonalWiderThanHighUnk()
        {
            // Bresenham, the major axis moved in each arm, as the original does (once after the if does not match)
            int const straightStep = this->currentHeight_0x2c * 2;
            int const diagonalStep = straightStep - this->currentWidth_0x28 * 2;
            int error = straightStep - this->currentWidth_0x28;
            for (; this->currentWidth_0x28 >= 0; --this->currentWidth_0x28) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawCurrentPixel, this)();
                if (error > 0) {
                    this->currentX += this->moveDirectionXUnk_0x20;
                    this->currentY += this->moveDirectionYUnk_0x24;
                    error += diagonalStep;
                } else {
                    this->currentX += this->moveDirectionXUnk_0x20;
                    error += straightStep;
                }
            }
        }

    }
}
}
