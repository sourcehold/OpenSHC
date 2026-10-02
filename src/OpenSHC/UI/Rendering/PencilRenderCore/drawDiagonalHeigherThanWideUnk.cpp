#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00471220
        void PencilRenderCore::drawDiagonalHeigherThanWideUnk()
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int _negativeHeightX2;
            iVar1 = this->currentWidth_0x28 * 2;
            _negativeHeightX2 = this->currentHeight_0x2c * -2;
            iVar3 = iVar1 - this->currentHeight_0x2c;
            for (; -1 < this->currentHeight_0x2c; this->currentHeight_0x2c = this->currentHeight_0x2c + -1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawCurrentPixel, this)();
                iVar2 = iVar1;
                if (0 < iVar3) {
                    this->currentX = this->currentX + this->moveDirectionXUnk_0x20;
                    iVar2 = iVar1 + _negativeHeightX2;
                }
                this->currentY = this->currentY + this->moveDirectionYUnk_0x24;
                iVar3 = iVar3 + iVar2;
            }
        }

    }
}
}
