#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0046F730
        void WindowAndDirectDraw::cleanDirectDraw()
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::releaseSurfacesAndDirectDraw, this)(
                TRUE);
            this->drawingReady_0x0 = FALSE;
        }

    }
}
}
