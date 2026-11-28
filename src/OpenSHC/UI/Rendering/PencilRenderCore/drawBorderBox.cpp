#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004711B0
        void PencilRenderCore::drawBorderBox(int left, int top, int right, int bottom, ushort color)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            BOOLEnum const _drawReady = MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(left, top, right, bottom, color);
            if (_drawReady) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                dword const _savedStartY = this->drawStartY;
                this->drawStartY = this->drawEndY;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                this->drawStartY = _savedStartY;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawVerticalLine, this)();
                dword const _savedStartX = this->drawStartX;
                this->drawStartX = this->drawEndX;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawVerticalLine, this)();
                this->drawStartX = _savedStartX;
            }
        }

    }
}
}
