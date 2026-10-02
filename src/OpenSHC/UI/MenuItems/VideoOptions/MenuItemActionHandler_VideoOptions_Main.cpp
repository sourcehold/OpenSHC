#include "../VideoOptions.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::UI::ScrollSpeed;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00493E20
        void VideoOptions::MenuItemActionHandler_VideoOptions_Main(int param_1, ...)
        {
            int dialogX;
            int dialogY;
            switch (param_1) {
            case 0xb:
                do {
                    if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                        == OpenSHC::Rendering::SRE_800x600) {
                        DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            = OpenSHC::Rendering::SRE_1024x600;
                    } else if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                        == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            = OpenSHC::Rendering::SRE_1024x768;
                    } else if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                        == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            = OpenSHC::Rendering::SRE_1360x768;
                    } else if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                        == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            = OpenSHC::Rendering::SRE_1366x768;
                    } else {
                        DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            = DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            + OpenSHC::Rendering::SRE_800x600;
                        if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            == OpenSHC::Rendering::SRE_1360x768) {
                            DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                                = OpenSHC::Rendering::SRE_800x600;
                        }
                    }
                } while ((&DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68
                                 .noneUnk)[DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution]
                    == 0);
                return;
            case 0xc:
                DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01
                    = DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01 ^ 1;
                return;
            case 0x10:
                DAT_MenuTextInputState::instance.menuScrollSpeedSetting
                    = DAT_MenuTextInputState::instance.menuScrollSpeedSetting + OpenSHC::UI::SS_FAST;
                if (3 <= (int)DAT_MenuTextInputState::instance.menuScrollSpeedSetting) {
                    DAT_MenuTextInputState::instance.menuScrollSpeedSetting = 0;
                }
                break;
            case 0x11:
                goto switchD_00493e37_caseD_11;
            case 0x12:
                if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                    != DAT_WindowAndDirectDraw::instance.currentGameResolution) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::prepareWindowAndDDraw_2Unk,
                        DAT_WindowAndDirectDraw::ptr)(DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen,
                        (ScreenResolutionEnum)((
                            int)(DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution)));
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::resetupViewportThunk,
                        DAT_ViewportRenderState::ptr)();
                    MACRO_CALL(OpenSHC::UI::MenuItems::BuildingAndStatusMenu_Func::
                            MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback)();
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    if (DAT_MenuModalComposition3::instance.activeModalDialogID
                        == OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR) {
                        if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_800x600) {
                            dialogY = 0x32;
                            dialogX = 0x2e9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1024x768) {
                            dialogY = 0x38;
                            dialogX = 0x3c9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1024x600) {
                            dialogY = 0x38;
                            dialogX = 0x3c9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1600x1200) {
                        LAB_00493fda:
                            dialogY = 0x38;
                            dialogX = 0x609;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1280x1024) {
                            dialogY = 0x38;
                            dialogX = 0x4c9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1280x720) {
                            dialogY = 0x38;
                            dialogX = 0x4c9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1440x900) {
                            dialogY = 0x38;
                            dialogX = 0x569;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1920x1080) {
                            dialogY = 0x38;
                            dialogX = 0x749;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1920x1200) {
                            dialogY = 0x38;
                            dialogX = 0x749;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_2560x1440) {
                            dialogY = 0x38;
                            dialogX = 0x9c9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_2560x1600) {
                            dialogY = 0x38;
                            dialogX = 0x9c9;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1366x768) {
                            dialogY = 0x38;
                            dialogX = 0x51f;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1360x768) {
                            dialogY = 0x38;
                            dialogX = 0x519;
                        } else {
                            if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                != OpenSHC::Rendering::SRE_1680x1050) {
                                if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                    != OpenSHC::Rendering::SRE_1600x900)
                                    goto LAB_00493ff0;
                                goto LAB_00493fda;
                            }
                            dialogY = 0x38;
                            dialogX = 0x659;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                            DAT_MenuModalComposition3::ptr)(
                            OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, dialogX, dialogY);
                    }
                }
            LAB_00493ff0:
                if (DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01
                    != DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::resetupViewport,
                        DAT_ViewportRenderState::ptr)(DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01);
                    DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                }
                if (DAT_MenuTextInputState::instance.menuCursorType != DAT_MouseState::instance.cursorType) {
                    DAT_MouseState::instance.cursorType = DAT_MenuTextInputState::instance.menuCursorType;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Input::MouseState_Func::makeSelectedCursorTypeCurrent, DAT_MouseState::ptr)();
                }
                DAT_ScrollingHandler::instance.scrollSpeedSetting_0x38
                    = DAT_MenuTextInputState::instance.menuScrollSpeedSetting;
            switchD_00493e37_caseD_11:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            case -0x14:
                DAT_MenuTextInputState::instance.menuCursorType = 1;
                break;
            case -10:
                DAT_MenuTextInputState::instance.menuCursorType = 2;
            }
        }

    }
}
}
