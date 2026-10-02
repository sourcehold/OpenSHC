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

    /*
      Renders an animated floating arrow/indicator overlay (GID_FLOATS_NEW) at a screen position   derived from
      param_1/param_2 and the current resolution. Animates through 10 frames at ~60ms per   frame using timeGetTime.
      Renders twice: once to RT_SCREEN_MENU and once to RT_MAP_GAME with   camera offset applied. Skipped if
      DAT_00df5540 is non-zero.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC790
    void Rendering::RenderAnimatedTutorialFloatOverlay(int param_1, int param_2)
    {
        RenderTargetInt RVar1;
        DWORD DVar2;
        uint uVar3;
        int iVar4;
        if (DAT_00df5540::instance != 0) {}
        if ((INT_00df5640::instance & 1U) == 0) {
            INT_00df5640::instance = INT_00df5640::instance | 1;
            INT_00df563c::instance = timeGetTime();
        }
        DVar2 = timeGetTime();
        RVar1 = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
        uVar3 = (DVar2 - INT_00df563c::instance) / 0x3c;
        if (9 < uVar3) {
            uVar3 = 0;
            INT_00df563c::instance = DVar2;
        }
        iVar4 = 0;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
        LAB_004bc7fc:
            iVar4 = 0xa8;
            goto LAB_004bc873;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
            iVar4 = 0x1a8;
            goto LAB_004bc873;
        }
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
        LAB_004bc814:
            iVar4 = 600;
        } else {
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                iVar4 = 0x78;
                goto LAB_004bc873;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1440x900) {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    iVar4 = 0x1e0;
                    goto LAB_004bc873;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200)
                    goto LAB_004bc814;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    iVar4 = 0x348;
                    goto LAB_004bc873;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    iVar4 = 1000;
                    goto LAB_004bc873;
                }
                if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768)
                    || (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768))
                    goto LAB_004bc7fc;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    iVar4 = 0xfd2;
                    goto LAB_004bc873;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900)
                    goto LAB_004bc873;
            }
            iVar4 = 300;
        }
    LAB_004bc873:
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(uVar3 + 0x105)),
            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + param_1 + -0x24, param_2 + -0x65 + iVar4,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(uVar3 + 0x10f)), 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(uVar3 + 0x105)),
            DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX
                + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + param_1 + -0x24,
            DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + iVar4 + param_2 + -0x65,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(uVar3 + 0x10f)), 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = RVar1;
    }

}
}
