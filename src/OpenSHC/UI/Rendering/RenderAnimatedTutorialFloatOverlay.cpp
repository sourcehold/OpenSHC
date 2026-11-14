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

    // Draws the animated GID_FLOATS_NEW frames to the screen menu and, with the camera offset, to the map.
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC790
    void Rendering::RenderAnimatedTutorialFloatOverlay(int x, int y)
    {
        if (DAT_00df5540::instance != 0) {
            return;
        }
        if (!(INT_00df5640::instance & 1)) {
            INT_00df5640::instance |= 1;
            INT_00df563c::instance = timeGetTime();
        }
        DWORD const now = timeGetTime();
        int frame = (now - INT_00df563c::instance) / 60;
        if (frame >= 10) {
            frame = 0;
            INT_00df563c::instance = now;
        }
        // two steps: one subtraction loses the match
        x -= 8;
        y -= 32;
        int resolutionYOffset = 0;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
            resolutionYOffset = 168;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
            resolutionYOffset = 424;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
            resolutionYOffset = 600;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
            resolutionYOffset = 120;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
            resolutionYOffset = 300;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
            resolutionYOffset = 480;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
            resolutionYOffset = 600;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
            resolutionYOffset = 840;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
            resolutionYOffset = 1000;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
            resolutionYOffset = 168;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
            resolutionYOffset = 168;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
            // fixme: every other offset is the screen height - 600 (450 here); the original has 4050
            resolutionYOffset = 4050;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
            resolutionYOffset = 300;
        }
        RenderTargetInt const previousDrawBuffer = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        x -= 28;
        y -= 69;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 261,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + x, y + resolutionYOffset,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 271, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 261,
            DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + x,
            DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + resolutionYOffset + y,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, frame + 271, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = previousDrawBuffer;
    }

}
}
