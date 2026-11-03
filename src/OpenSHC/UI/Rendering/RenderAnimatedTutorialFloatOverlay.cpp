#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00df563c.hpp"
#include "OpenSHC/Globals/INT_00df5640.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::Rendering::Enums::RenderTarget;

    // Renders the animated tutorial arrow (GID_FLOATS_NEW) at (x, y), moved down by a per-resolution offset. It
    // cycles through 10 frames at about 60 ms each and is drawn twice: to the screen menu surface and, with the
    // camera offset, to the map surface. Skipped while DAT_00df5540 is set.
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC790
    void Rendering::RenderAnimatedTutorialFloatOverlay(int x, int y)
    {
        if (DAT_00df5540::instance != 0) {
            return;
        }
        if ((INT_00df5640::instance & 1U) == 0) {
            INT_00df5640::instance = INT_00df5640::instance | 1;
            INT_00df563c::instance = timeGetTime();
        }
        DWORD const now = timeGetTime();
        int frame = (now - INT_00df563c::instance) / 60;
        if (frame >= 10) {
            frame = 0;
            INT_00df563c::instance = now;
        }
        // The gotos measure 3.5 points better than a plain if/else-if chain: the original keeps the shared
        // 168 and 600 blocks at their first occurrence. It also keeps x - 8 and y - 32 apart from the
        // later - 28 and - 69 (an inlined helper?), which this source folds.
        int resolutionYOffset = 0;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
        yOffset168:
            resolutionYOffset = 0xa8;
            goto draw;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
            resolutionYOffset = 0x1a8;
            goto draw;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
        yOffset600:
            resolutionYOffset = 600;
        } else {
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                resolutionYOffset = 0x78;
                goto draw;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1440x900) {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    resolutionYOffset = 0x1e0;
                    goto draw;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200)
                    goto yOffset600;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    resolutionYOffset = 0x348;
                    goto draw;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    resolutionYOffset = 1000;
                    goto draw;
                }
                if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768)
                    || (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768))
                    goto yOffset168;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    resolutionYOffset = 0xfd2;
                    goto draw;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900)
                    goto draw;
            }
            resolutionYOffset = 300;
        }
    draw:
        RenderTargetInt const previousDrawBuffer = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 261,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + x - 0x24, y - 0x65 + resolutionYOffset,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 271, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 261,
            DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + x - 0x24,
            DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + resolutionYOffset + y - 0x65,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 271, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = previousDrawBuffer;
    }

}
}
