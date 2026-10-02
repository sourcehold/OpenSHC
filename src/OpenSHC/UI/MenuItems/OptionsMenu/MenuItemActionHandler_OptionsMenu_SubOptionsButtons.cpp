#include "../OptionsMenu.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00493BD0
        void OptionsMenu::MenuItemActionHandler_OptionsMenu_SubOptionsButtons(int param_1, ...)
        {
            switch (param_1) {
            case 4:
                DAT_MenuTextInputState::instance.menuCurrentlySelectedResolution
                    = DAT_WindowAndDirectDraw::instance.currentGameResolution;
                DAT_MenuTextInputState::instance.unknownZoomRelatedFlag01
                    = DAT_ViewportRenderState::instance.viewportState.isZoomedOutUnk;
                DAT_MenuTextInputState::instance.menuScrollSpeedSetting
                    = DAT_ScrollingHandler::instance.scrollSpeedSetting_0x38;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_VIDEO_OPTIONS);
                DAT_MenuTextInputState::instance.menuCursorType = DAT_MouseState::instance.cursorType;
                return;
            case 5:
                DAT_MenuTextInputState::instance.DAT_GenieVoiceActiveMenuVar = DAT_GameCore::instance.genieVoiceActive;
                DAT_MenuTextInputState::instance.DAT_SoundActiveMenuVar
                    = DAT_SoundSystemState::instance.soundActiveUnk_0x0;
                DAT_MenuTextInputState::instance.field20_0x44 = DAT_SoundSystemState::instance.streamVolume[0];
                DAT_MenuTextInputState::instance.field21_0x48 = DAT_SoundSystemState::instance.streamVolume[1];
                DAT_MenuTextInputState::instance.field22_0x4c = DAT_SoundSystemState::instance.streamVolume[3];
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_SOUND_OPTIONS);
                return;
            case 6:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_NETWORK_OPTIONS);
                return;
            case 0x11:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
                return;
            case 0x19:
                DAT_MenuTextInputState::instance.field12_0x30 = DAT_GameCore::instance.gameSpeedLevel;
                DAT_MenuTextInputState::instance.field14_0x38 = DAT_GameCore::instance.settingBubbleHelp;
                DAT_MenuTextInputState::instance.field15_0x3c = DAT_GameCore::instance.unusedOption1;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_GAMEPLAY_OPTIONS);
                break;
            case 0x2d:
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    0);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_IDENTITY_OPTIONS);
            }
        }

    }
}
}
