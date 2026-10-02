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
        // FUNCTION: STRONGHOLDCRUSADER 0x00472B20
        void PencilRenderCore::drawLine(int x1, int y1, int x2, int y2, ushort color)
        {
            BOOLEnum _drawReady;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            _drawReady = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                x1, y1, x2, y2, color);
            if (_drawReady != FALSE) {
                if (this->currentWidth_0x28 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawVerticalLine, this)();
                }
                if (this->currentHeight_0x2c == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                }
                if (this->currentWidth_0x28 < this->currentHeight_0x2c) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawDiagonalHeigherThanWideUnk, this)();
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawDiagonalWiderThanHighUnk, this)();
            }
        }

    }
}
}
