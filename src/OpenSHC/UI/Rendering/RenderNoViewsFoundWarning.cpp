#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F4070
    void Rendering::RenderNoViewsFoundWarning()
    {
        int left;
        int top;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawPixelPattern4x4OverWholeScreen,
            DAT_PencilRenderCore::ptr)();
        top = (DAT_WindowAndDirectDraw::instance.resolutionY + -0x28) / 2;
        left = (DAT_WindowAndDirectDraw::instance.resolutionX + -400) / 2;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            left, top, left + 400, top + 0x28, (ushort)((int)(COL_WHITE::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            "No views have been found.", (DAT_WindowAndDirectDraw::instance.resolutionX + -400) / 2,
            (int)((int)((DAT_WindowAndDirectDraw::instance.resolutionY + -40) / 2 + 8)), ((TextAlignment)400), 0, 0x11,
            FALSE, 0);
    }

}
}
