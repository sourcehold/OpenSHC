#include "../PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00471220
        void PencilRenderCore::drawDiagonalHeigherThanWideUnk()
        {
            // Bresenham, the major axis moved in each arm, as the original does (once after the if does not match)
            int const straightStep = this->currentWidth_0x28 * 2;
            int const diagonalStep = straightStep - this->currentHeight_0x2c * 2;
            int error = straightStep - this->currentHeight_0x2c;
            for (; this->currentHeight_0x2c >= 0; --this->currentHeight_0x2c) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawCurrentPixel, this)();
                if (error > 0) {
                    this->currentX += this->moveDirectionXUnk_0x20;
                    this->currentY += this->moveDirectionYUnk_0x24;
                    error += diagonalStep;
                } else {
                    this->currentY += this->moveDirectionYUnk_0x24;
                    error += straightStep;
                }
            }
        }

    }
}
}
