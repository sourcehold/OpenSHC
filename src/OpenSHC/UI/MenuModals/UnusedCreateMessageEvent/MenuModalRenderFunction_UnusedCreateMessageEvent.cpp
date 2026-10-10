#include "../UnusedCreateMessageEvent.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AB680
        void UnusedCreateMessageEvent::MenuModalRenderFunction_UnusedCreateMessageEvent(
            int x, int y, int width, int height)
        {
            /*
              added by script: "Message"
             */
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                199, 0x2f, x, y, width, height);
            int y1 = y + 0xd7;
            int x2 = x + 0x2b3;
            int x1 = x + 0xbd;
            int y2 = y + 0x18a;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0xd6, x2, y + 0xd6, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x18b, x2, y + 0x18b, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x29e, y + 0xeb, x2, y + 0xeb, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x29e, y1, x + 0x29e, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x29f, y + 0x176, x + 0x2b2, y + 0x176, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }

    }
}
}
