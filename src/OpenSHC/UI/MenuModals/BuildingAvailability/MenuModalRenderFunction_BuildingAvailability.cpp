#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABBA0
        void BuildingAvailability::MenuModalRenderFunction_BuildingAvailability(int x, int y, int width, int height)
        {
            // "Building Availability"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 171, x, y, width, height);
            int rightColumnX = x + 598;
            int y1 = y + 82;
            int y2 = y + 461;
            int x2 = rightColumnX + 1;
            int x1 = x + 117;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1 - 1, x2, y1 - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y2 + 1, x2, y2 + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 20, y1 + 20, x2, y1 + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 20, y1, rightColumnX - 20, y2, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 19, y2 - 20, rightColumnX, y2 - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
        }

    }
}
}
