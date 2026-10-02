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

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044C850
        void TextureRenderCore::drawLoadingBarUnk(GmID currentGmId, int barLengthUnk)
        {
            DWORD _currentTime;
            _currentTime = timeGetTime();
            if (0x1e < (int)(_currentTime - TIME_LastVisualLoadingBarUpdate::instance)) {
                TIME_LastVisualLoadingBarUpdate::instance = _currentTime;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x + 236,
                    (int)((int)(DAT_MenuHandlerState::instance.y + 571)),
                    (int)(currentGmId * 0x148) / barLengthUnk + 236 + DAT_MenuHandlerState::instance.x,
                    (int)((int)(DAT_MenuHandlerState::instance.y + 579)),
                    (ushort)((int)(COL_DARK_RED::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltScreenMenuSurfaceToScreen,
                    DAT_WindowAndDirectDraw::ptr)(DAT_MenuHandlerState::instance.x + 0xeb,
                    DAT_MenuHandlerState::instance.y + 0x23a, DAT_MenuHandlerState::instance.x + 0x235,
                    DAT_MenuHandlerState::instance.y + 0x244);
            }
        }

    }
}
}
