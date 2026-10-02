#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::ScreenResolutionEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0046F880
        void WindowAndDirectDraw::setupPreferredScreenResolution()
        {
            if (this->currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
            LAB_0046f9de:
                this->gameResolutionX = 800;
            } else {
                if (this->currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    this->gameResolutionX = 1024;
                    this->gameResolutionY = 768;
                    goto LAB_0046f9ec;
                }
                if (this->currentGameResolution != OpenSHC::Rendering::SRE_1024x600) {
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        this->gameResolutionX = 0x500;
                        this->gameResolutionY = 0x400;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        this->gameResolutionX = 0x640;
                        this->gameResolutionY = 0x4b0;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        this->gameResolutionX = 0x500;
                        this->gameResolutionY = 0x2d0;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        this->gameResolutionX = 0x5a0;
                        this->gameResolutionY = 900;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        this->gameResolutionX = 0x780;
                        this->gameResolutionY = 0x438;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        this->gameResolutionX = 0x780;
                        this->gameResolutionY = 0x4b0;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        this->gameResolutionX = 0xa00;
                        this->gameResolutionY = 0x5a0;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        this->gameResolutionX = 0xa00;
                        this->gameResolutionY = 0x640;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        this->gameResolutionX = 0x556;
                        this->gameResolutionY = 0x300;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        this->gameResolutionX = 0x550;
                        this->gameResolutionY = 0x300;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        this->gameResolutionX = 0x690;
                        this->gameResolutionY = 0x41a;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                        this->gameResolutionX = 0x640;
                        this->gameResolutionY = 900;
                        goto LAB_0046f9ec;
                    }
                    if (this->currentGameResolution == 20) {
                        this->gameResolutionX = 640;
                        this->gameResolutionY = 480;
                        goto LAB_0046f9ec;
                    }
                    goto LAB_0046f9de;
                }
                this->gameResolutionX = 0x400;
            }
            this->gameResolutionY = 600;
        LAB_0046f9ec:
            /*
              The game is centered around the 800x600 resolution. That is the target res   for the menu. -TheRedDaemon
             */
            this->mainMenuBorderWidth = (this->gameResolutionX + -800) / 2;
            this->mainMenuBorderHeight = (this->gameResolutionY + -600) / 2;
            this->byteSizeOfOneHorizontalLine = this->gameResolutionX * 2;
            this->resolutionX = this->gameResolutionX;
            this->resolutionY = this->gameResolutionY;
            /*
              1366x768 seems to have a different handling. It uses the x-res 1368 * 2. No   wonder 1366x768 once broke
              my display engine change. Interesting though,   ignoring this handling fixed my issue. -TheRedDaemon
             */
            if (this->currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                this->byteSizeOfOneHorizontalLine = 2736;
            }
            this->gameResolutionY_3_0x44 = this->gameResolutionY;
            this->byteSizeofScreenResolution = this->byteSizeOfOneHorizontalLine * this->gameResolutionY;
            this->numPixel_GameX_x_3_x_GameY_0x4c = this->gameResolutionY * this->gameResolutionX * 3;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                DAT_TextureRenderCoreObject::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRangeUnk,
                DAT_TextureRenderCoreObject::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                DAT_TextureRenderCoreObject::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::resetTextClipRange, DAT_TextManagerObject::ptr)();
        }

    }
}
}
