#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4070
    void Rendering::RenderNoViewsFoundWarning()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawPixelPattern4x4OverWholeScreen,
            DAT_PencilRenderCore::ptr)();
        int top = (DAT_WindowAndDirectDraw::instance.resolutionY - 40) / 2;
        int left = (DAT_WindowAndDirectDraw::instance.resolutionX - 400) / 2;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            left, top, left + 400, top + 40, (ushort)(COL_WHITE::instance.shortValue));
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            s_No_views_have_been_found__005ab8c8, (DAT_WindowAndDirectDraw::instance.resolutionX - 400) / 2,
            (int)((DAT_WindowAndDirectDraw::instance.resolutionY - 40) / 2 + 8), ((TextAlignment)400), 0, 17, FALSE, 0);
    }

}
}
