#include "../NewEventAction.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventType.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C0860
        void NewEventAction::MenuItemRenderFunction_NewEventAction_Main(int button, ...)
        {
            DAT_ButtonUnknownZero::instance = FALSE;
            // The row's text, and the button for the value (selectedButton first: quick_diff 0.9184 -> 0.9143)
            int textNumber = button;
            int const selectedButton = button;
            int iconOffset = -1;
            switch (button) {
            // 38 to 40 show "Select Message" (text 40), each for one message action
            case 37:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
                return;
            case 38:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == OpenSHC::Game::ScenarioEvents::Enums::SET_LOSE_AND_MESSAGE) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button + 2);
                    return;
                }
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            case 39:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == OpenSHC::Game::ScenarioEvents::Enums::SET_WIN_AND_MESSAGE) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button + 1);
                    return;
                }
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            case 40:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == OpenSHC::Game::ScenarioEvents::Enums::SET_MESSAGE) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
                    return;
                }
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            // the action rows: 128 to 155 are event types 0 to 27, 177 to 187 are 28 to 38
            case 177:
            case 178:
            case 179:
            case 180:
            case 181:
            case 182:
            case 183:
            case 184:
            case 185:
            case 186:
            case 187:
                button -= 21;
            case 128:
            case 129:
            case 130:
            case 131:
            case 132:
            case 133:
            case 134:
            case 135:
            case 136:
            case 137:
            case 138:
            case 139:
            case 140:
            case 141:
            case 142:
            case 143:
            case 144:
            case 145:
            case 146:
            case 147:
            case 148:
            case 149:
            case 150:
            case 151:
            case 152:
            case 153:
            case 154:
            case 155:
                // "Archers" (148) is drawn as "Bandits" (146) with the other icon
                if (textNumber == 148) {
                    textNumber = 146;
                    iconOffset = 0;
                } else if (textNumber == 146) {
                    iconOffset = 2;
                }
                if (button - 128
                    == DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumber, DAT_ButtonX::instance + 14,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                        FALSE);
                    if (iconOffset > -1) {
                        // " - "
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s___005a2304, DAT_ButtonX::instance + 20,
                            DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF,
                            18, TRUE, 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iconOffset + 128,
                            DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 23,
                            DAT_ButtonY::instance + 3);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_MapPropertiesState::instance.sliderPopupDelay != 0) {
                        --DAT_MapPropertiesState::instance.sliderPopupDelay;
                        if (DAT_MapPropertiesState::instance.sliderPopupDelay == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER,
                                DAT_MapPropertiesState::instance.sliderPopupX,
                                DAT_MapPropertiesState::instance.sliderPopupY);
                        }
                    }
                    switch (selectedButton) {
                    case 132:
                    case 139:
                    case 145:
                    case 146:
                    case 148:
                    case 179:
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData,
                            DAT_ButtonW::instance + DAT_ButtonX::instance - 14, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    case 178:
                        // "%"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s_percentage_005a2770,
                            DAT_ButtonW::instance + DAT_ButtonX::instance - 14, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData,
                            DAT_ButtonW::instance + DAT_ButtonX::instance - 28, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    }
                    return;
                }
                // The same draw in both branches (one draw without the test: quick_diff 0.9184 -> 0.7731)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumber, DAT_ButtonX::instance + 14,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                        FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumber, DAT_ButtonX::instance + 14,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                        FALSE);
                }
                if (iconOffset > -1) {
                    // " - "
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        s___005a2304, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iconOffset + 128,
                        DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 23,
                        DAT_ButtonY::instance + 3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                return;
            }
        }

    }
}
}
