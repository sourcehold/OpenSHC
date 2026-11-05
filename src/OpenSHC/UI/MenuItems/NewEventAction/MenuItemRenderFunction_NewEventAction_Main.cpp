#include "../NewEventAction.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-macros.hpp"

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
        void NewEventAction::MenuItemRenderFunction_NewEventAction_Main(int param_1, ...)
        {
            int textNumInGroup;
            int iVar2 = -1;
            DAT_ButtonUnknownZero::instance = 0;
            int iVar1 = param_1;
            switch (param_1) {
            case 37:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                return;
            case 38:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == 27) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1 + 2);
                }
                break;
            case 39:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == 26) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1 + 1);
                }
                break;
            case 40:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == 2) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                }
                break;
            default:
                DAT_ButtonUnknownZero::instance = 0;
                return;
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
                iVar1 = param_1 - 21;
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
                if (param_1 == 148) {
                    iVar2 = 0;
                    textNumInGroup = 146;
                } else {
                    textNumInGroup = param_1;
                    if (param_1 == 146) {
                        iVar2 = 2;
                    }
                }
                if (iVar1 - 128
                    == DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup, (int)(DAT_ButtonX::instance + 14),
                        (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    if (0 <= iVar2) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            // " - "
                            DAT_TextManagerObject::ptr)(S___005A2304, (int)(DAT_ButtonX::instance + 20),
                            (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 128,
                            (int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 23 + DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 3));
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if ((DAT_MapPropertiesState::instance.sliderPopupDelay != 0)
                        && (DAT_MapPropertiesState::instance.sliderPopupDelay
                            = DAT_MapPropertiesState::instance.sliderPopupDelay - 1,
                            DAT_MapPropertiesState::instance.sliderPopupDelay == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                            DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER,
                            (int)(DAT_MapPropertiesState::instance.sliderPopupX),
                            (int)(DAT_MapPropertiesState::instance.sliderPopupY));
                    }
                    switch (param_1) {
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
                            (int)(DAT_ButtonW::instance - 14 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        return;
                    default:
                        return;
                    case 178:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            // "%"
                            DAT_TextManagerObject::ptr)(S_PERCENTAGE_005A2770,
                            (int)(DAT_ButtonW::instance - 14 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData,
                            (int)(DAT_ButtonW::instance - 28 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    }
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup, (int)(DAT_ButtonX::instance + 14),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB,
                    18, FALSE);
                if (iVar2 < 0) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    // " - "
                    S___005A2304, (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 7),
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 128,
                    (int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 23 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 3));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            DAT_ButtonUnknownZero::instance = 1;
        }

    }
}
}
