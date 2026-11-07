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

        // FUNCTION: STRONGHOLDCRUSADER 0x00493E20
        void VideoOptions::MenuItemActionHandler_VideoOptions_Main(int param_1, ...)
        {
            int dialogX;
            int dialogY;
            switch (param_1) {
            case 11:
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
                            += OpenSHC::Rendering::SRE_800x600;
                        if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                            == OpenSHC::Rendering::SRE_1360x768) {
                            DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                                = OpenSHC::Rendering::SRE_800x600;
                        }
                    }
                } while (DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68
                             .array[DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution]
                    == 0);
                return;
            case 12:
                DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01 ^= 1;
                return;
            case 16:
                DAT_MenuTextInputState::instance.menuScrollSpeedSetting += OpenSHC::UI::SS_FAST;
                if (3 <= (int)DAT_MenuTextInputState::instance.menuScrollSpeedSetting) {
                    DAT_MenuTextInputState::instance.menuScrollSpeedSetting = 0;
                }
                break;
            case 17:
                goto switchD_00493e37_caseD_11;
            case 18:
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
                            dialogY = 50;
                            dialogX = 745;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1024x768) {
                            dialogY = 56;
                            dialogX = 969;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1024x600) {
                            dialogY = 56;
                            dialogX = 969;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1600x1200) {
                        LAB_00493fda:
                            dialogY = 56;
                            dialogX = 1545;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1280x1024) {
                            dialogY = 56;
                            dialogX = 1225;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1280x720) {
                            dialogY = 56;
                            dialogX = 1225;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1440x900) {
                            dialogY = 56;
                            dialogX = 1385;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1920x1080) {
                            dialogY = 56;
                            dialogX = 1865;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1920x1200) {
                            dialogY = 56;
                            dialogX = 1865;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_2560x1440) {
                            dialogY = 56;
                            dialogX = 2505;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_2560x1600) {
                            dialogY = 56;
                            dialogX = 2505;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1366x768) {
                            dialogY = 56;
                            dialogX = 1311;
                        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                            == OpenSHC::Rendering::SRE_1360x768) {
                            dialogY = 56;
                            dialogX = 1305;
                        } else {
                            if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                != OpenSHC::Rendering::SRE_1680x1050) {
                                if (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                    != OpenSHC::Rendering::SRE_1600x900)
                                    goto LAB_00493ff0;
                                goto LAB_00493fda;
                            }
                            dialogY = 56;
                            dialogX = 1625;
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
            case -20:
                DAT_MenuTextInputState::instance.menuCursorType = 1;
                break;
            case -10:
                DAT_MenuTextInputState::instance.menuCursorType = 2;
            }
        }

    }
}
}
