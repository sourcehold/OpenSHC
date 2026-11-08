#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E66F0
    void ViewportRenderState::setupViewport(int windowX, int windowY, int screenPixelWidth, int screenPixelHeight)
    {
        this->windowX = windowX;
        // fixme: the original stores windowX into windowY as well
        this->windowY = windowX;
        this->screenPixelHeight = screenPixelHeight;
        this->screenPixelWidth = screenPixelWidth;
        if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
                || DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
            && (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
            if (this->viewportState.isZoomedOutUnk == 0) {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    this->viewportState.viewportHeight = 30;
                    this->viewportState.viewportWidth = 79;
                    this->viewportState.mbr_0xac = 12;
                    this->viewportState.mbr_0xb0 = 40;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 20;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 40;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 30;
                    this->viewportState.someXOffset = 8;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1024x768) {
                    this->viewportState.viewportHeight = 37;
                    this->viewportState.viewportWidth = 100;
                    this->viewportState.mbr_0xac = 15;
                    this->viewportState.mbr_0xb0 = 46;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 17;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 52;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 35;
                    this->viewportState.someXOffset = 10;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1024x600) {
                    this->viewportState.viewportHeight = 37;
                    this->viewportState.viewportWidth = 79;
                    this->viewportState.mbr_0xac = 15;
                    this->viewportState.mbr_0xb0 = 40;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 17;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 52;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 35;
                    this->viewportState.someXOffset = 10;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1280x1024) {
                    this->viewportState.viewportHeight = 45;
                    this->viewportState.viewportWidth = 132;
                    this->viewportState.mbr_0xac = 19;
                    this->viewportState.mbr_0xb0 = 52;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 40;
                    this->viewportState.someXOffset = 12;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                    this->viewportState.viewportWidth = 64;
                    this->viewportState.viewportHeight = 25;
                    this->viewportState.mbr_0xac = 10;
                    this->viewportState.mbr_0xb0 = 30;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 40;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 20;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 30;
                    this->viewportState.someXOffset = 7;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1600x1200) {
                    this->viewportState.viewportWidth = 154;
                    this->viewportState.mbr_0xb0 = 80;
                    this->viewportState.viewportHeight = 55;
                    this->viewportState.mbr_0xac = 24;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 14;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1280x720) {
                    this->viewportState.viewportHeight = 45;
                    this->viewportState.viewportWidth = 94;
                    this->viewportState.mbr_0xac = 19;
                    this->viewportState.mbr_0xb0 = 48;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 52;
                    this->viewportState.someXOffset = 17;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1440x900) {
                    this->viewportState.viewportWidth = 116;
                    this->viewportState.viewportHeight = 50;
                    this->viewportState.mbr_0xac = 22;
                    this->viewportState.mbr_0xb0 = 60;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 10;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1920x1080) {
                    this->viewportState.viewportWidth = 139;
                    this->viewportState.viewportHeight = 65;
                    this->viewportState.mbr_0xac = 29;
                    this->viewportState.mbr_0xb0 = 72;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 13;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1920x1200) {
                    this->viewportState.viewportWidth = 154;
                    this->viewportState.mbr_0xac = 29;
                    this->viewportState.viewportHeight = 65;
                    this->viewportState.mbr_0xb0 = 80;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 76;
                    this->viewportState.someXOffset = 14;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_2560x1440) {
                    this->viewportState.viewportWidth = 184;
                    this->viewportState.mbr_0xb0 = 96;
                    this->viewportState.viewportHeight = 85;
                    this->viewportState.mbr_0xac = 39;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 100;
                    this->viewportState.someXOffset = 16;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_2560x1600) {
                    this->viewportState.viewportWidth = 204;
                    this->viewportState.mbr_0xb0 = 112;
                    this->viewportState.viewportHeight = 85;
                    this->viewportState.mbr_0xac = 39;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 100;
                    this->viewportState.someXOffset = 16;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1366x768) {
                    this->viewportState.viewportHeight = 48;
                    this->viewportState.viewportWidth = 100;
                    this->viewportState.mbr_0xac = 22;
                    this->viewportState.mbr_0xb0 = 46;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 10;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1360x768) {
                    this->viewportState.viewportHeight = 48;
                    this->viewportState.viewportWidth = 100;
                    this->viewportState.mbr_0xac = 22;
                    this->viewportState.mbr_0xb0 = 46;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 10;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1680x1050) {
                    this->viewportState.viewportHeight = 58;
                    this->viewportState.viewportWidth = 135;
                    this->viewportState.mbr_0xac = 24;
                    this->viewportState.mbr_0xb0 = 72;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 13;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1600x900) {
                    this->viewportState.viewportWidth = 116;
                    this->viewportState.mbr_0xb0 = 60;
                    this->viewportState.viewportHeight = 55;
                    this->viewportState.mbr_0xac = 24;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 10;
                    this->viewportState.someYOffset = 64;
                }
            } else {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    this->viewportState.viewportHeight = 60;
                    this->viewportState.viewportWidth = 158;
                    this->viewportState.mbr_0xac = 31;
                    this->viewportState.mbr_0xb0 = 68;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 10;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 80;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 2;
                    this->viewportState.someYOffset = 65;
                    this->viewportState.someXOffset = 6;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1024x768) {
                    this->viewportState.viewportHeight = 74;
                    this->viewportState.viewportWidth = 200;
                    this->viewportState.mbr_0xac = 36;
                    this->viewportState.mbr_0xb0 = 84;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 7;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 100;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 3;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1024x600) {
                    this->viewportState.viewportHeight = 74;
                    this->viewportState.viewportWidth = 158;
                    this->viewportState.mbr_0xac = 36;
                    this->viewportState.mbr_0xb0 = 68;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 7;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 100;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 3;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1280x1024) {
                    this->viewportState.viewportHeight = 90;
                    this->viewportState.viewportWidth = 264;
                    this->viewportState.mbr_0xac = 41;
                    this->viewportState.mbr_0xb0 = 94;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 5;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 100;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 3;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                    this->viewportState.viewportWidth = 128;
                    this->viewportState.viewportHeight = 50;
                    this->viewportState.mbr_0xac = 25;
                    this->viewportState.mbr_0xb0 = 50;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 20;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 40;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 30;
                    this->viewportState.someXOffset = 7;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1600x1200) {
                    this->viewportState.viewportWidth = 308;
                    this->viewportState.viewportHeight = 110;
                    this->viewportState.mbr_0xac = 50;
                    this->viewportState.mbr_0xb0 = 110;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 6;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1280x720) {
                    this->viewportState.viewportHeight = 90;
                    this->viewportState.viewportWidth = 188;
                    this->viewportState.mbr_0xac = 41;
                    this->viewportState.mbr_0xb0 = 80;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 52;
                    this->viewportState.someXOffset = 6;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1440x900) {
                    this->viewportState.viewportHeight = 100;
                    this->viewportState.viewportWidth = 232;
                    this->viewportState.mbr_0xac = 47;
                    this->viewportState.mbr_0xb0 = 90;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 6;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1920x1080) {
                    this->viewportState.viewportHeight = 130;
                    this->viewportState.viewportWidth = 278;
                    this->viewportState.mbr_0xac = 56;
                    this->viewportState.mbr_0xb0 = 100;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 6;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1920x1200) {
                    this->viewportState.viewportHeight = 130;
                    this->viewportState.viewportWidth = 308;
                    this->viewportState.mbr_0xac = 56;
                    this->viewportState.mbr_0xb0 = 110;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 76;
                    this->viewportState.someXOffset = 6;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_2560x1440) {
                    this->viewportState.viewportWidth = 368;
                    this->viewportState.mbr_0xb0 = 120;
                    this->viewportState.viewportHeight = 170;
                    this->viewportState.mbr_0xac = 71;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 100;
                    this->viewportState.someXOffset = 6;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_2560x1600) {
                    this->viewportState.viewportWidth = 408;
                    this->viewportState.mbr_0xb0 = 130;
                    this->viewportState.viewportHeight = 170;
                    this->viewportState.mbr_0xac = 71;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someYOffset = 100;
                    this->viewportState.someXOffset = 6;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1366x768) {
                    this->viewportState.viewportHeight = 96;
                    this->viewportState.viewportWidth = 200;
                    this->viewportState.mbr_0xac = 47;
                    this->viewportState.mbr_0xb0 = 84;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 3;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1360x768) {
                    this->viewportState.viewportHeight = 96;
                    this->viewportState.viewportWidth = 200;
                    this->viewportState.mbr_0xac = 47;
                    this->viewportState.mbr_0xb0 = 84;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 3;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1680x1050) {
                    this->viewportState.viewportHeight = 116;
                    this->viewportState.viewportWidth = 270;
                    this->viewportState.mbr_0xb0 = 100;
                    this->viewportState.mbr_0xac = 50;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 6;
                    this->viewportState.someYOffset = 64;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1600x900) {
                    this->viewportState.viewportWidth = 232;
                    this->viewportState.mbr_0xb0 = 85;
                    this->viewportState.viewportHeight = 110;
                    this->viewportState.mbr_0xac = 50;
                    DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                    DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                    DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                    this->viewportState.someXOffset = 6;
                    this->viewportState.someYOffset = 64;
                }
            }
        } else if (this->viewportState.isZoomedOutUnk == 0) {
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                this->viewportState.viewportHeight = 30;
                this->viewportState.viewportWidth = 63;
                this->viewportState.mbr_0xac = 12;
                this->viewportState.mbr_0xb0 = 40;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 20;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 40;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 30;
                this->viewportState.someXOffset = 7;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                this->viewportState.viewportHeight = 37;
                this->viewportState.viewportWidth = 84;
                this->viewportState.mbr_0xac = 15;
                this->viewportState.mbr_0xb0 = 46;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 17;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 52;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 40;
                this->viewportState.someXOffset = 8;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                this->viewportState.viewportHeight = 37;
                this->viewportState.viewportWidth = 63;
                this->viewportState.mbr_0xac = 15;
                this->viewportState.mbr_0xb0 = 40;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 17;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 52;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 40;
                this->viewportState.someXOffset = 8;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                this->viewportState.viewportHeight = 45;
                this->viewportState.viewportWidth = 116;
                this->viewportState.mbr_0xac = 19;
                this->viewportState.mbr_0xb0 = 52;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 52;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 50;
                this->viewportState.someXOffset = 8;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                this->viewportState.viewportWidth = 48;
                this->viewportState.viewportHeight = 25;
                this->viewportState.mbr_0xac = 10;
                this->viewportState.mbr_0xb0 = 30;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 40;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 20;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 30;
                this->viewportState.someXOffset = 7;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                this->viewportState.viewportWidth = 138;
                this->viewportState.mbr_0xb0 = 80;
                this->viewportState.viewportHeight = 55;
                this->viewportState.mbr_0xac = 24;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 14;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                this->viewportState.viewportHeight = 45;
                this->viewportState.viewportWidth = 78;
                this->viewportState.mbr_0xac = 19;
                this->viewportState.mbr_0xb0 = 48;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 52;
                this->viewportState.someXOffset = 17;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                this->viewportState.viewportWidth = 100;
                this->viewportState.viewportHeight = 50;
                this->viewportState.mbr_0xac = 22;
                this->viewportState.mbr_0xb0 = 60;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 10;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                this->viewportState.viewportWidth = 123;
                this->viewportState.viewportHeight = 65;
                this->viewportState.mbr_0xac = 29;
                this->viewportState.mbr_0xb0 = 72;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 13;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                this->viewportState.viewportWidth = 138;
                this->viewportState.mbr_0xac = 39;
                this->viewportState.viewportHeight = 65;
                this->viewportState.mbr_0xb0 = 80;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 76;
                this->viewportState.someXOffset = 14;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                this->viewportState.viewportWidth = 168;
                this->viewportState.mbr_0xb0 = 90;
                this->viewportState.viewportHeight = 85;
                this->viewportState.mbr_0xac = 39;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 100;
                this->viewportState.someXOffset = 16;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                this->viewportState.viewportHeight = 85;
                this->viewportState.viewportWidth = 188;
                this->viewportState.mbr_0xac = 29;
                this->viewportState.mbr_0xb0 = 100;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 100;
                this->viewportState.someXOffset = 18;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                this->viewportState.viewportHeight = 48;
                this->viewportState.viewportWidth = 84;
                this->viewportState.mbr_0xac = 22;
                this->viewportState.mbr_0xb0 = 46;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 8;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                this->viewportState.viewportHeight = 48;
                this->viewportState.viewportWidth = 84;
                this->viewportState.mbr_0xac = 22;
                this->viewportState.mbr_0xb0 = 46;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 8;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                this->viewportState.viewportHeight = 58;
                this->viewportState.viewportWidth = 119;
                this->viewportState.mbr_0xac = 24;
                this->viewportState.mbr_0xb0 = 72;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 13;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                this->viewportState.viewportWidth = 100;
                this->viewportState.mbr_0xb0 = 60;
                this->viewportState.viewportHeight = 55;
                this->viewportState.mbr_0xac = 24;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 10;
                this->viewportState.someYOffset = 64;
            }
        } else {
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                this->viewportState.viewportHeight = 60;
                this->viewportState.viewportWidth = 126;
                this->viewportState.mbr_0xac = 31;
                this->viewportState.mbr_0xb0 = 68;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 10;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 80;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 2;
                this->viewportState.someYOffset = 65;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                this->viewportState.viewportHeight = 74;
                this->viewportState.viewportWidth = 168;
                this->viewportState.mbr_0xac = 36;
                this->viewportState.mbr_0xb0 = 84;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 7;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 100;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 3;
                this->viewportState.someYOffset = 78;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                this->viewportState.viewportHeight = 74;
                this->viewportState.viewportWidth = 126;
                this->viewportState.mbr_0xac = 36;
                this->viewportState.mbr_0xb0 = 68;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 7;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 100;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 3;
                this->viewportState.someYOffset = 78;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                this->viewportState.viewportHeight = 90;
                this->viewportState.viewportWidth = 232;
                this->viewportState.mbr_0xac = 41;
                this->viewportState.mbr_0xb0 = 94;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 5;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 100;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 3;
                this->viewportState.someYOffset = 91;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                this->viewportState.viewportWidth = 96;
                this->viewportState.viewportHeight = 50;
                this->viewportState.mbr_0xac = 25;
                this->viewportState.mbr_0xb0 = 50;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 20;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 40;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 30;
                this->viewportState.someXOffset = 7;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                this->viewportState.viewportWidth = 276;
                this->viewportState.viewportHeight = 110;
                this->viewportState.mbr_0xac = 50;
                this->viewportState.mbr_0xb0 = 110;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                this->viewportState.viewportHeight = 90;
                this->viewportState.viewportWidth = 156;
                this->viewportState.mbr_0xac = 41;
                this->viewportState.mbr_0xb0 = 80;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 52;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                this->viewportState.viewportHeight = 100;
                this->viewportState.viewportWidth = 200;
                this->viewportState.mbr_0xac = 47;
                this->viewportState.mbr_0xb0 = 90;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                this->viewportState.viewportHeight = 130;
                this->viewportState.viewportWidth = 246;
                this->viewportState.mbr_0xac = 56;
                this->viewportState.mbr_0xb0 = 100;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                this->viewportState.viewportHeight = 130;
                this->viewportState.viewportWidth = 276;
                this->viewportState.mbr_0xac = 56;
                this->viewportState.mbr_0xb0 = 110;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 76;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                this->viewportState.viewportWidth = 336;
                this->viewportState.mbr_0xb0 = 120;
                this->viewportState.viewportHeight = 170;
                this->viewportState.mbr_0xac = 71;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 100;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                this->viewportState.viewportWidth = 376;
                this->viewportState.mbr_0xb0 = 130;
                this->viewportState.viewportHeight = 170;
                this->viewportState.mbr_0xac = 71;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someYOffset = 100;
                this->viewportState.someXOffset = 6;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                this->viewportState.viewportHeight = 96;
                this->viewportState.viewportWidth = 168;
                this->viewportState.mbr_0xac = 47;
                this->viewportState.mbr_0xb0 = 84;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                this->viewportState.viewportHeight = 96;
                this->viewportState.viewportWidth = 168;
                this->viewportState.mbr_0xac = 47;
                this->viewportState.mbr_0xb0 = 84;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                this->viewportState.viewportHeight = 116;
                this->viewportState.viewportWidth = 238;
                this->viewportState.mbr_0xb0 = 100;
                this->viewportState.mbr_0xac = 50;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                this->viewportState.viewportWidth = 200;
                this->viewportState.mbr_0xb0 = 85;
                this->viewportState.viewportHeight = 110;
                this->viewportState.mbr_0xac = 50;
                DAT_ScrollingHandler::instance.scrollAccelerationInterval = 15;
                DAT_ScrollingHandler::instance.scrollDistanceLimit = 60;
                DAT_ScrollingHandler::instance.scrollDistanceMin = 1;
                this->viewportState.someXOffset = 6;
                this->viewportState.someYOffset = 64;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
    }

}
}
