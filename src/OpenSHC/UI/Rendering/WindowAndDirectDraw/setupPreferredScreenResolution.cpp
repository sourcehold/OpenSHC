#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046F880
        void WindowAndDirectDraw::setupPreferredScreenResolution()
        {
            if (this->currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                this->gameResolutionX = 800;
                this->gameResolutionY = 600;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                this->gameResolutionX = 1024;
                this->gameResolutionY = 768;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                this->gameResolutionX = 1024;
                this->gameResolutionY = 600;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                this->gameResolutionX = 1280;
                this->gameResolutionY = 1024;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                this->gameResolutionX = 1600;
                this->gameResolutionY = 1200;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                this->gameResolutionX = 1280;
                this->gameResolutionY = 720;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                this->gameResolutionX = 1440;
                this->gameResolutionY = 900;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                this->gameResolutionX = 1920;
                this->gameResolutionY = 1080;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                this->gameResolutionX = 1920;
                this->gameResolutionY = 1200;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                this->gameResolutionX = 2560;
                this->gameResolutionY = 1440;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                this->gameResolutionX = 2560;
                this->gameResolutionY = 1600;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                this->gameResolutionX = 1366;
                this->gameResolutionY = 768;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                this->gameResolutionX = 1360;
                this->gameResolutionY = 768;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                this->gameResolutionX = 1680;
                this->gameResolutionY = 1050;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                this->gameResolutionX = 1600;
                this->gameResolutionY = 900;
            } else if (this->currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                this->gameResolutionX = 640;
                this->gameResolutionY = 480;
            } else {
                this->gameResolutionX = 800;
                this->gameResolutionY = 600;
            }
            // The game is centered around the 800x600 resolution. That is the target res for the menu. -TheRedDaemon
            this->mainMenuBorderWidth = (this->gameResolutionX - 800) / 2;
            this->mainMenuBorderHeight = (this->gameResolutionY - 600) / 2;
            this->resolutionX = this->gameResolutionX;
            this->resolutionY = this->gameResolutionY;
            this->byteSizeOfOneHorizontalLine = this->gameResolutionX * 2;
            // 1366x768 seems to have a different handling. It uses the x-res 1368 * 2. No wonder 1366x768 once broke my
            // display engine change. Interesting though, ignoring this handling fixed my issue. -TheRedDaemon
            if (this->currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                this->byteSizeOfOneHorizontalLine = 1368 * 2;
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
