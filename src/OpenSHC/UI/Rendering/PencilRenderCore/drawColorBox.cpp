#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00470E90
        void PencilRenderCore::drawColorBox(int left, int top, int right, int bottom, ushort color)
        {
            BOOLEnum _drawPossible;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            _drawPossible = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                left, top, right, bottom, color);
            if (_drawPossible != FALSE) {
                for (; -1 < this->currentHeight_0x2c; this->currentHeight_0x2c = this->currentHeight_0x2c + -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                    this->drawStartY = this->drawStartY + 1;
                }
            }
        }

    }
}
}
