#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00471280
        void PencilRenderCore::drawDiagonalWiderThanHighUnk()
        {
            int iVar1 = this->currentHeight_0x2c * 2;
            int _negativeHeightX2 = this->currentWidth_0x28 * -2;
            int iVar3 = iVar1 - this->currentWidth_0x28;
            for (; -1 < this->currentWidth_0x28; this->currentWidth_0x28 = this->currentWidth_0x28 + -1) {
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawCurrentPixel, this)();
                int iVar2 = iVar1;
                if (0 < iVar3) {
                    this->currentY = this->currentY + this->moveDirectionYUnk_0x24;
                    iVar2 = iVar1 + _negativeHeightX2;
                }
                this->currentX = this->currentX + this->moveDirectionXUnk_0x20;
                iVar3 = iVar3 + iVar2;
            }
        }

    }
}
}
