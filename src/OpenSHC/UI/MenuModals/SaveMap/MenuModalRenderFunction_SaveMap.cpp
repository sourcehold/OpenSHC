#include "../SaveMap.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004931A0
        void SaveMap::MenuModalRenderFunction_SaveMap(int x, int y, int width, int height)
        {
            /*
              added by script: "Save"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4a, 3, x, y, 0x130, height);
            int rightColumnX = x + 0x29e;
            int y1 = y + 0x22;
            int y2 = y + 0x177;
            int x2 = rightColumnX + 1;
            int x1 = x + 0x135;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1 - 1, x2, y1 - 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y2 + 1, x2, y2 + 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1 + 0x14, x2, y1 + 0x14, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 0x14, y1, rightColumnX - 0x14, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 0x13, y2 - 0x14, rightColumnX, y2 - 0x14,
                (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }

    }
}
}
