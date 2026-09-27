#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
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
    void ViewportRenderState::setupViewport(
        undefined4 windowX, undefined4 windowY, undefined4 screenPixelWidth, undefined4 screenPixelHeight)

    {
        this->windowX = windowX;
        this->windowY = windowX;
        this->screenPixelHeight = screenPixelHeight;
        this->screenPixelWidth = screenPixelWidth;
        undefined4 someXOffsetDefault = 0xe;
        if (((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                || (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING))
            && ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
            if (this->viewportState.isZoomedOutUnk == 0) {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    this->viewportState.viewportHeight = 30;
                    this->viewportState.viewportWidth = 79;
                    this->viewportState.mbr_0xac = 0xc;
                    this->viewportState.mbr_0xb0 = 40;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0x14;
                    DAT_ScrollingHandler::instance.field13_0x34 = 40;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 30;
                    this->viewportState.someXOffset = 8;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    this->viewportState.viewportHeight = 0x25;
                    this->viewportState.viewportWidth = 100;
                    this->viewportState.mbr_0xac = 0xf;
                    this->viewportState.mbr_0xb0 = 0x2e;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0x11;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x34;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x23;
                    this->viewportState.someXOffset = 10;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == 15) {
                    this->viewportState.viewportHeight = 0x25;
                    this->viewportState.viewportWidth = 0x4f;
                    this->viewportState.mbr_0xac = 15;
                    this->viewportState.mbr_0xb0 = 0x28;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0x11;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x34;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x23;
                    this->viewportState.someXOffset = 10;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    this->viewportState.viewportHeight = 0x2d;
                    this->viewportState.viewportWidth = 0x84;
                    this->viewportState.mbr_0xac = 0x13;
                    this->viewportState.mbr_0xb0 = 0x34;
                    DAT_ScrollingHandler::instance.field12_0x30 = 15;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x28;
                    this->viewportState.someXOffset = 0xc;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == 20) {
                    this->viewportState.viewportWidth = 0x40;
                    this->viewportState.viewportHeight = 0x19;
                    this->viewportState.mbr_0xac = 10;
                    this->viewportState.mbr_0xb0 = 0x1e;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0x28;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x14;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x1e;
                    this->viewportState.someXOffset = 7;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    this->viewportState.viewportWidth = 0x9a;
                    this->viewportState.mbr_0xb0 = 0x50;
                } else {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        this->viewportState.viewportHeight = 45;
                        this->viewportState.viewportWidth = 94;
                        this->viewportState.mbr_0xac = 19;
                        this->viewportState.mbr_0xb0 = 48;
                        DAT_ScrollingHandler::instance.field12_0x30 = 15;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x34;
                        this->viewportState.someXOffset = 0x11;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        this->viewportState.viewportWidth = 0x74;
                        this->viewportState.viewportHeight = 0x32;
                        this->viewportState.mbr_0xac = 0x16;
                        this->viewportState.mbr_0xb0 = 0x3c;
                        this->viewportState.someXOffset = 10;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x40;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    someXOffsetDefault = 10;
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        this->viewportState.viewportWidth = 0x8b;
                        this->viewportState.viewportHeight = 0x41;
                        this->viewportState.mbr_0xac = 0x1d;
                        this->viewportState.mbr_0xb0 = 0x48;
                        this->viewportState.someXOffset = 0xd;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x40;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        this->viewportState.viewportWidth = 0x9a;
                        this->viewportState.mbr_0xac = 0x1d;
                        this->viewportState.viewportHeight = 0x41;
                        this->viewportState.mbr_0xb0 = 0x50;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x4c;
                        this->viewportState.someXOffset = 0xe;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        this->viewportState.viewportWidth = 184;
                        this->viewportState.mbr_0xb0 = 96;
                        this->viewportState.viewportHeight = 85;
                        this->viewportState.mbr_0xac = 39;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 100;
                        this->viewportState.someXOffset = 16;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        this->viewportState.viewportWidth = 0xcc;
                        this->viewportState.mbr_0xb0 = 0x70;
                        this->viewportState.viewportHeight = 85;
                        this->viewportState.mbr_0xac = 39;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 100;
                        this->viewportState.someXOffset = 16;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768)
                        || (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1360x768)) {
                        this->viewportState.viewportHeight = 0x30;
                        this->viewportState.viewportWidth = 100;
                        this->viewportState.mbr_0xac = 0x16;
                        this->viewportState.mbr_0xb0 = 0x2e;
                        this->viewportState.someXOffset = someXOffsetDefault;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x40;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        this->viewportState.viewportHeight = 0x3a;
                        this->viewportState.viewportWidth = 0x87;
                        this->viewportState.mbr_0xac = 0x18;
                        this->viewportState.mbr_0xb0 = 0x48;
                        this->viewportState.someXOffset = 0xd;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x40;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    this->viewportState.viewportWidth = 0x74;
                    this->viewportState.mbr_0xb0 = 0x3c;
                }
                this->viewportState.viewportHeight = 0x37;
                this->viewportState.mbr_0xac = 0x18;
                this->viewportState.someXOffset = someXOffsetDefault;
            } else {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    this->viewportState.viewportHeight = 0x3c;
                    this->viewportState.viewportWidth = 0x9e;
                    this->viewportState.mbr_0xac = 0x1f;
                    this->viewportState.mbr_0xb0 = 0x44;
                    DAT_ScrollingHandler::instance.field12_0x30 = 10;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x50;
                    DAT_ScrollingHandler::instance.field11_0x2c = 2;
                    this->viewportState.someYOffset = 0x41;
                    this->viewportState.someXOffset = 6;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    this->viewportState.viewportHeight = 0x4a;
                    this->viewportState.viewportWidth = 200;
                    this->viewportState.mbr_0xac = 0x24;
                    this->viewportState.mbr_0xb0 = 0x54;
                    DAT_ScrollingHandler::instance.field12_0x30 = 7;
                    DAT_ScrollingHandler::instance.field13_0x34 = 100;
                    DAT_ScrollingHandler::instance.field11_0x2c = 3;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                    this->viewportState.viewportHeight = 0x4a;
                    this->viewportState.viewportWidth = 0x9e;
                    this->viewportState.mbr_0xac = 0x24;
                    this->viewportState.mbr_0xb0 = 0x44;
                    DAT_ScrollingHandler::instance.field12_0x30 = 7;
                    DAT_ScrollingHandler::instance.field13_0x34 = 100;
                    DAT_ScrollingHandler::instance.field11_0x2c = 3;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    this->viewportState.viewportHeight = 0x5a;
                    this->viewportState.viewportWidth = 0x108;
                    this->viewportState.mbr_0xac = 0x29;
                    this->viewportState.mbr_0xb0 = 0x5e;
                    DAT_ScrollingHandler::instance.field12_0x30 = 5;
                    DAT_ScrollingHandler::instance.field13_0x34 = 100;
                    DAT_ScrollingHandler::instance.field11_0x2c = 3;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                    this->viewportState.viewportWidth = 0x80;
                    this->viewportState.viewportHeight = 0x32;
                    this->viewportState.mbr_0xac = 0x19;
                    this->viewportState.mbr_0xb0 = 0x32;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0x14;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x28;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x1e;
                    this->viewportState.someXOffset = 7;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    this->viewportState.viewportWidth = 0x134;
                    this->viewportState.viewportHeight = 0x6e;
                    this->viewportState.mbr_0xac = 0x32;
                    this->viewportState.mbr_0xb0 = 0x6e;
                    this->viewportState.someXOffset = 6;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x40;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    this->viewportState.viewportHeight = 0x5a;
                    this->viewportState.viewportWidth = 0xbc;
                    this->viewportState.mbr_0xac = 0x29;
                    this->viewportState.mbr_0xb0 = 0x50;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x34;
                    this->viewportState.someXOffset = 6;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    this->viewportState.viewportHeight = 100;
                    this->viewportState.viewportWidth = 0xe8;
                    this->viewportState.mbr_0xac = 0x2f;
                    this->viewportState.mbr_0xb0 = 0x5a;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1920x1080) {
                    this->viewportState.viewportHeight = 0x82;
                    this->viewportState.viewportWidth = 0x116;
                    this->viewportState.mbr_0xac = 0x38;
                    this->viewportState.mbr_0xb0 = 100;
                } else {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        this->viewportState.viewportHeight = 0x82;
                        this->viewportState.viewportWidth = 0x134;
                        this->viewportState.mbr_0xac = 0x38;
                        this->viewportState.mbr_0xb0 = 0x6e;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x4c;
                        this->viewportState.someXOffset = 6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        this->viewportState.viewportWidth = 0x170;
                        this->viewportState.mbr_0xb0 = 0x78;
                        this->viewportState.viewportHeight = 0xaa;
                        this->viewportState.mbr_0xac = 0x47;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 100;
                        this->viewportState.someXOffset = 6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        this->viewportState.viewportWidth = 0x198;
                        this->viewportState.mbr_0xb0 = 0x82;
                        this->viewportState.viewportHeight = 0xaa;
                        this->viewportState.mbr_0xac = 0x47;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 100;
                        this->viewportState.someXOffset = 6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768)
                        || (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1360x768)) {
                        this->viewportState.viewportHeight = 0x60;
                        this->viewportState.viewportWidth = 200;
                        this->viewportState.mbr_0xac = 0x2f;
                        this->viewportState.mbr_0xb0 = 0x54;
                        this->viewportState.someXOffset = 3;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x40;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        this->viewportState.viewportHeight = 0x74;
                        this->viewportState.viewportWidth = 0x10e;
                        this->viewportState.mbr_0xb0 = 100;
                    } else {
                        if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            != OpenSHC::Rendering::SRE_1600x900) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                            return;
                        }
                        this->viewportState.viewportWidth = 0xe8;
                        this->viewportState.mbr_0xb0 = 0x55;
                        this->viewportState.viewportHeight = 0x6e;
                    }
                    this->viewportState.mbr_0xac = 0x32;
                }
                this->viewportState.someXOffset = 6;
            }
        } else if (this->viewportState.isZoomedOutUnk == 0) {
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                this->viewportState.viewportHeight = 0x1e;
                this->viewportState.viewportWidth = 0x3f;
                this->viewportState.mbr_0xac = 0xc;
                this->viewportState.mbr_0xb0 = 0x28;
                DAT_ScrollingHandler::instance.field12_0x30 = 0x14;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x28;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x1e;
                this->viewportState.someXOffset = 7;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                this->viewportState.viewportHeight = 0x25;
                this->viewportState.viewportWidth = 0x54;
                this->viewportState.mbr_0xac = 0xf;
                this->viewportState.mbr_0xb0 = 0x2e;
                DAT_ScrollingHandler::instance.field12_0x30 = 0x11;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x34;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x28;
                this->viewportState.someXOffset = 8;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                this->viewportState.viewportHeight = 0x25;
                this->viewportState.viewportWidth = 0x3f;
                this->viewportState.mbr_0xac = 0xf;
                this->viewportState.mbr_0xb0 = 0x28;
                DAT_ScrollingHandler::instance.field12_0x30 = 0x11;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x34;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x28;
                this->viewportState.someXOffset = 8;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                this->viewportState.viewportHeight = 0x2d;
                this->viewportState.viewportWidth = 0x74;
                this->viewportState.mbr_0xac = 0x13;
                this->viewportState.mbr_0xb0 = 0x34;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x34;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x32;
                this->viewportState.someXOffset = 8;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                this->viewportState.viewportWidth = 0x30;
                this->viewportState.viewportHeight = 0x19;
                this->viewportState.mbr_0xac = 10;
                this->viewportState.mbr_0xb0 = 0x1e;
                DAT_ScrollingHandler::instance.field12_0x30 = 0x28;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x14;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x1e;
                this->viewportState.someXOffset = 7;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                this->viewportState.viewportWidth = 0x8a;
                this->viewportState.mbr_0xb0 = 0x50;
                this->viewportState.viewportHeight = 0x37;
                this->viewportState.mbr_0xac = 0x18;
                this->viewportState.someXOffset = someXOffsetDefault;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x40;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                this->viewportState.viewportHeight = 0x2d;
                this->viewportState.viewportWidth = 0x4e;
                this->viewportState.mbr_0xac = 0x13;
                this->viewportState.mbr_0xb0 = 0x30;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x34;
                this->viewportState.someXOffset = 0x11;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                this->viewportState.viewportWidth = 100;
                this->viewportState.viewportHeight = 0x32;
                this->viewportState.mbr_0xac = 0x16;
                this->viewportState.mbr_0xb0 = 0x3c;
                this->viewportState.someXOffset = 10;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x40;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            someXOffsetDefault = 10;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                this->viewportState.viewportWidth = 0x7b;
                this->viewportState.viewportHeight = 0x41;
                this->viewportState.mbr_0xac = 0x1d;
                this->viewportState.mbr_0xb0 = 0x48;
                this->viewportState.someXOffset = 0xd;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x40;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                this->viewportState.viewportWidth = 0x8a;
                this->viewportState.mbr_0xac = 0x27;
                this->viewportState.viewportHeight = 0x41;
                this->viewportState.mbr_0xb0 = 0x50;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x4c;
                this->viewportState.someXOffset = 0xe;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                this->viewportState.viewportWidth = 0xa8;
                this->viewportState.mbr_0xb0 = 0x5a;
                this->viewportState.viewportHeight = 85;
                this->viewportState.mbr_0xac = 39;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 100;
                this->viewportState.someXOffset = 16;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                this->viewportState.viewportHeight = 0x55;
                this->viewportState.viewportWidth = 0xbc;
                this->viewportState.mbr_0xac = 0x1d;
                this->viewportState.mbr_0xb0 = 100;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 100;
                this->viewportState.someXOffset = 0x12;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768)
                || (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768)) {
                this->viewportState.viewportHeight = 0x30;
                this->viewportState.viewportWidth = 0x54;
                this->viewportState.mbr_0xac = 0x16;
                this->viewportState.mbr_0xb0 = 0x2e;
                this->viewportState.someXOffset = 8;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x40;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1680x1050) {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                this->viewportState.viewportWidth = 100;
                this->viewportState.mbr_0xb0 = 0x3c;
                this->viewportState.viewportHeight = 0x37;
                this->viewportState.mbr_0xac = 0x18;
                this->viewportState.someXOffset = someXOffsetDefault;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x40;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            this->viewportState.viewportHeight = 0x3a;
            this->viewportState.viewportWidth = 0x77;
            this->viewportState.mbr_0xac = 0x18;
            this->viewportState.mbr_0xb0 = 0x48;
            this->viewportState.someXOffset = 0xd;
        } else {
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                this->viewportState.viewportHeight = 0x3c;
                this->viewportState.viewportWidth = 0x7e;
                this->viewportState.mbr_0xac = 0x1f;
                this->viewportState.mbr_0xb0 = 0x44;
                DAT_ScrollingHandler::instance.field12_0x30 = 10;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x50;
                DAT_ScrollingHandler::instance.field11_0x2c = 2;
                this->viewportState.someYOffset = 0x41;
                this->viewportState.someXOffset = 6;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                this->viewportState.viewportHeight = 0x4a;
                this->viewportState.viewportWidth = 0xa8;
                this->viewportState.mbr_0xac = 0x24;
                this->viewportState.mbr_0xb0 = 0x54;
                DAT_ScrollingHandler::instance.field12_0x30 = 7;
                DAT_ScrollingHandler::instance.field13_0x34 = 100;
                DAT_ScrollingHandler::instance.field11_0x2c = 3;
                this->viewportState.someYOffset = 0x4e;
                this->viewportState.someXOffset = 6;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                this->viewportState.viewportHeight = 0x4a;
                this->viewportState.viewportWidth = 0x7e;
                this->viewportState.mbr_0xac = 0x24;
                this->viewportState.mbr_0xb0 = 0x44;
                DAT_ScrollingHandler::instance.field12_0x30 = 7;
                DAT_ScrollingHandler::instance.field13_0x34 = 100;
                DAT_ScrollingHandler::instance.field11_0x2c = 3;
                this->viewportState.someYOffset = 0x4e;
                this->viewportState.someXOffset = 6;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                this->viewportState.viewportHeight = 0x5a;
                this->viewportState.viewportWidth = 0xe8;
                this->viewportState.mbr_0xac = 0x29;
                this->viewportState.mbr_0xb0 = 0x5e;
                DAT_ScrollingHandler::instance.field12_0x30 = 5;
                DAT_ScrollingHandler::instance.field13_0x34 = 100;
                DAT_ScrollingHandler::instance.field11_0x2c = 3;
                this->viewportState.someYOffset = 0x5b;
                this->viewportState.someXOffset = 6;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                this->viewportState.viewportWidth = 0x60;
                this->viewportState.viewportHeight = 0x32;
                this->viewportState.mbr_0xac = 0x19;
                this->viewportState.mbr_0xb0 = 0x32;
                DAT_ScrollingHandler::instance.field12_0x30 = 0x14;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x28;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x1e;
                this->viewportState.someXOffset = 7;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x1200) {
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    this->viewportState.viewportHeight = 0x5a;
                    this->viewportState.viewportWidth = 0x9c;
                    this->viewportState.mbr_0xac = 0x29;
                    this->viewportState.mbr_0xb0 = 0x50;
                    DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                    DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                    DAT_ScrollingHandler::instance.field11_0x2c = 1;
                    this->viewportState.someYOffset = 0x34;
                    this->viewportState.someXOffset = 6;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                    return;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    this->viewportState.viewportHeight = 100;
                    this->viewportState.viewportWidth = 200;
                    this->viewportState.mbr_0xac = 0x2f;
                    this->viewportState.mbr_0xb0 = 0x5a;
                } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                    == OpenSHC::Rendering::SRE_1920x1080) {
                    this->viewportState.viewportHeight = 0x82;
                    this->viewportState.viewportWidth = 0xf6;
                    this->viewportState.mbr_0xac = 0x38;
                    this->viewportState.mbr_0xb0 = 100;
                } else {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        this->viewportState.viewportHeight = 0x82;
                        this->viewportState.viewportWidth = 0x114;
                        this->viewportState.mbr_0xac = 0x38;
                        this->viewportState.mbr_0xb0 = 0x6e;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x4c;
                        this->viewportState.someXOffset = 6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        this->viewportState.viewportWidth = 0x150;
                        this->viewportState.mbr_0xb0 = 0x78;
                        this->viewportState.viewportHeight = 0xaa;
                        this->viewportState.mbr_0xac = 0x47;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 100;
                        this->viewportState.someXOffset = 6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        this->viewportState.viewportWidth = 0x178;
                        this->viewportState.mbr_0xb0 = 0x82;
                        this->viewportState.viewportHeight = 0xaa;
                        this->viewportState.mbr_0xac = 0x47;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 100;
                        this->viewportState.someXOffset = 6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    if ((DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1366x768)
                        && (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            != OpenSHC::Rendering::SRE_1360x768)) {
                        if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            != OpenSHC::Rendering::SRE_1680x1050) {
                            if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                != OpenSHC::Rendering::SRE_1600x900) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                                return;
                            }
                            this->viewportState.viewportWidth = 200;
                            this->viewportState.mbr_0xb0 = 0x55;
                            this->viewportState.viewportHeight = 0x6e;
                            this->viewportState.mbr_0xac = 0x32;
                            this->viewportState.someXOffset = 6;
                            DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                            DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                            DAT_ScrollingHandler::instance.field11_0x2c = 1;
                            this->viewportState.someYOffset = 0x40;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                            return;
                        }
                        this->viewportState.viewportHeight = 0x74;
                        this->viewportState.viewportWidth = 0xee;
                        this->viewportState.mbr_0xb0 = 100;
                        this->viewportState.mbr_0xac = 0x32;
                        this->viewportState.someXOffset = 6;
                        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                        DAT_ScrollingHandler::instance.field11_0x2c = 1;
                        this->viewportState.someYOffset = 0x40;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                        return;
                    }
                    this->viewportState.viewportHeight = 0x60;
                    this->viewportState.viewportWidth = 0xa8;
                    this->viewportState.mbr_0xac = 0x2f;
                    this->viewportState.mbr_0xb0 = 0x54;
                }
                this->viewportState.someXOffset = 6;
                DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
                DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
                DAT_ScrollingHandler::instance.field11_0x2c = 1;
                this->viewportState.someYOffset = 0x40;
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
                return;
            }
            this->viewportState.viewportWidth = 0x114;
            this->viewportState.viewportHeight = 0x6e;
            this->viewportState.mbr_0xac = 0x32;
            this->viewportState.mbr_0xb0 = 0x6e;
            this->viewportState.someXOffset = 6;
        }
        DAT_ScrollingHandler::instance.field13_0x34 = 0x3c;
        DAT_ScrollingHandler::instance.field12_0x30 = 0xf;
        DAT_ScrollingHandler::instance.field11_0x2c = 1;
        this->viewportState.someYOffset = 0x40;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, this)();
    }

}
}
