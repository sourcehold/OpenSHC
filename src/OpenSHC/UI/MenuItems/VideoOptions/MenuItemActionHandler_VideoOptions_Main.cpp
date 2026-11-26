#include "../VideoOptions.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/CursorType.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x00493E20
        void VideoOptions::MenuItemActionHandler_VideoOptions_Main(int button, ...)
        {
            switch (button) {
            case 11: { // resolution: the next one that the screen supports, in the menu's order
                int resolution = DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution;
                for (OpenSHC::WindowsHelper::Enums::BOOLEnum supported = FALSE; !supported;
                    supported = DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.array[resolution]) {
                    if (resolution == OpenSHC::Rendering::SRE_800x600) {
                        resolution = OpenSHC::Rendering::SRE_1024x600;
                    } else if (resolution == OpenSHC::Rendering::SRE_1024x600) {
                        resolution = OpenSHC::Rendering::SRE_1024x768;
                    } else if (resolution == OpenSHC::Rendering::SRE_1280x1024) {
                        resolution = OpenSHC::Rendering::SRE_1360x768;
                    } else if (resolution == OpenSHC::Rendering::SRE_1360x768) {
                        resolution = OpenSHC::Rendering::SRE_1366x768;
                    } else {
                        resolution++;
                        if (resolution == OpenSHC::Rendering::SRE_1360x768) {
                            resolution = OpenSHC::Rendering::SRE_800x600;
                        }
                    }
                }
                DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution = resolution;
                return;
            }
            case 12: // zoomed out, on or off
                DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01 ^= 1;
                return;
            case 16: // scroll speed
                DAT_MenuTextInputState::instance.menuScrollSpeedSetting++;
                // after the third speed comes the first again
                if (DAT_MenuTextInputState::instance.menuScrollSpeedSetting >= 3) {
                    DAT_MenuTextInputState::instance.menuScrollSpeedSetting = OpenSHC::UI::SS_NORMAL;
                }
                return;
            case 18: // apply the settings, then close
                if (DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                    != DAT_WindowAndDirectDraw::instance.currentGameResolution) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::prepareWindowAndDDraw_2Unk,
                        DAT_WindowAndDirectDraw::ptr)(DAT_WindowAndDirectDraw::instance.runGameAsExclusiveFullscreen,
                        (OpenSHC::Rendering::ScreenResolutionEnum)
                            DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution);
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::resetupViewportThunk,
                        DAT_ViewportRenderState::ptr)();
                    MACRO_CALL(OpenSHC::UI::MenuItems::BuildingAndStatusMenu_Func::
                            MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback)();
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    if (DAT_MenuModalComposition3::instance.activeModalDialogID
                        == OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR) {
                        // the tactical power bar sits 55 pixels from the right edge of the new resolution
                        int const resolution = DAT_WindowAndDirectDraw::instance.currentGameResolution;
                        if (resolution == OpenSHC::Rendering::SRE_800x600) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 745, 50);
                        } else if (resolution == OpenSHC::Rendering::SRE_1024x768) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 969, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1024x600) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 969, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1600x1200) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1545, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1280x1024) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1225, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1280x720) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1225, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1440x900) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1385, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1920x1080) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1865, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1920x1200) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1865, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_2560x1440) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 2505, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_2560x1600) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 2505, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1366x768) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1311, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1360x768) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1305, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1680x1050) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1625, 56);
                        } else if (resolution == OpenSHC::Rendering::SRE_1600x900) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_TACTICAL_POWER_BAR, 1545, 56);
                        }
                    }
                }
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
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            case 17: // close without applying
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            case -10: // cursor type
                DAT_MenuTextInputState::instance.menuCursorType = OpenSHC::UI::Enums::CT_WINDOWS_LIKE_CURSOR;
                return;
            case -20:
                DAT_MenuTextInputState::instance.menuCursorType = OpenSHC::UI::Enums::CT_ANI_CURSOR;
                return;
            }
        }

    }
}
}
