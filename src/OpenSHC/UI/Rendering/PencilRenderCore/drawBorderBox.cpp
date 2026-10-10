#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004711B0
        void PencilRenderCore::drawBorderBox(int left, int top, int right, int bottom, ushort color)
        {
            BOOLEnum _drawReady;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            _drawReady = MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                left, top, right, bottom, color);
            if (_drawReady) {
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                dword dVar1 = this->drawStartY;
                this->drawStartY = this->drawEndY;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                this->drawStartY = dVar1;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawVerticalLine, this)();
                dVar1 = this->drawStartX;
                this->drawStartX = this->drawEndX;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawVerticalLine, this)();
                this->drawStartX = dVar1;
            }
        }

    }
}
}
