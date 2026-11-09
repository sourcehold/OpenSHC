#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/COL_DARK_RED.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/TIME_LastVisualLoadingBarUpdate.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044C850
        void TextureRenderCore::drawLoadingBarUnk(GmID currentGmId, int barLengthUnk)
        {
            DWORD const now = timeGetTime();
            if ((int)(now - TIME_LastVisualLoadingBarUpdate::instance) > 30) {
                TIME_LastVisualLoadingBarUpdate::instance = now;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                    DAT_MenuHandlerState::instance.x + 236, DAT_MenuHandlerState::instance.y + 571,
                    (int)(currentGmId * 328) / barLengthUnk + 236 + DAT_MenuHandlerState::instance.x,
                    DAT_MenuHandlerState::instance.y + 579, COL_DARK_RED::instance.shortValue);
                MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::bltScreenMenuSurfaceToScreen,
                    DAT_WindowAndDirectDraw::ptr)(DAT_MenuHandlerState::instance.x + 235,
                    DAT_MenuHandlerState::instance.y + 570, DAT_MenuHandlerState::instance.x + 565,
                    DAT_MenuHandlerState::instance.y + 580);
            }
        }

    }
}
}
