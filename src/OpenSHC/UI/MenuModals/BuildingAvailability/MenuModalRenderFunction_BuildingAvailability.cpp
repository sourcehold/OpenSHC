#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABBA0
        void BuildingAvailability::MenuModalRenderFunction_BuildingAvailability(int x, int y, int width, int height)
        {
            /*
              added by script: "Building Availability"
             */
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                199, 0xab, x, y, width, height);
            int y1 = y + 0x52;
            int x2 = x + 599;
            int x1 = x + 0x75;
            int y2 = y + 0x1cd;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x51, x2, y + 0x51, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x1ce, x2, y + 0x1ce, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x242, y + 0x66, x2, y + 0x66, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x242, y1, x + 0x242, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x243, y + 0x1b9, x + 0x256, y + 0x1b9, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }

    }
}
}
