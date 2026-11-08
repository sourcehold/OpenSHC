#include "../NewEventCondition.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/ScenarioEvents/Enums/ScenarioEventConditionIndex.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004C01B0
        void NewEventCondition::MenuItemRenderFunction_NewEventCondition_Main(int button, ...)
        {
            // The condition's text, copied at the start (copied after the check: quick_diff 0.9440 -> 0.8940)
            int textNumber = button;
            DAT_ButtonUnknownZero::instance = FALSE;
            if (button > 5000) {
                return;
            }
            switch (button) {
            case -1:
                // The event's month: X + W / 2 here (W / 2 + X, as in 2002: reccmp 99.7% -> 99.3%)
                // One call per colour (one call with a colour local: quick_diff 0.9440 -> 0.9237)
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .header.month
                            + 12,
                        DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .header.month
                            + 12,
                        DAT_ButtonX::instance + DAT_ButtonW::instance / 2, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                }
                return;
            case 126:
                if (!DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        .enabled) {
                    // "Inactive"
                    button = 127;
                }
                // as 19
            case 19:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
                return;
            case 104:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.allOrAnyCondition) {
                    // "All of these"
                    button = 105;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
                return;
            case 209: {
                // "Win Timer" (row 39) only while one of these conditions is on: else DAT_ButtonUnknownZero
                BOOLEnum anyEnabled = FALSE;
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_POPULATION]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_GOLD_ACQUIRED]
                        .enabled) {
                    anyEnabled = TRUE; // Written out (a loop over 4 to 7: quick_diff 0.9440 -> 0.8543)
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_FOOD_ACQUIRED]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_GOODS_ACQUIRED]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_WEAPONS_ACQUIRED_17]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_BLESSED]
                        .enabled) {
                    anyEnabled = TRUE; // Written out (a loop over 20 to 22: quick_diff 0.9440 -> 0.8708)
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_PERCENT_DRINKING_ALE]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_CRUELTY]
                        .enabled) {
                    anyEnabled = TRUE;
                }
                if (!DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[OpenSHC::Game::ScenarioEvents::Enums::SECI_MAXIMUM_PLEASANTNESS]
                        .enabled
                    && !anyEnabled) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
            }
                // as 190 to 208
            case 190: // conditions 20 to 39
            case 191:
            case 192:
            case 193:
            case 194:
            case 195:
            case 196:
            case 197:
            case 198:
            case 199:
            case 200:
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 208:
                button -= 64;
            case 106: // conditions 0 to 19
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 112:
            case 113:
            case 114:
            case 115:
            case 116:
            case 117:
            case 118:
            case 119:
            case 120:
            case 121:
            case 122:
            case 123:
            case 124:
            case 125: {
                int const slot = button - 106;
                DAT_ButtonCurrentlyInteracting::instance = DAT_MapPropertiesState::instance.invasionTroopIndex == slot;
                uint color = OpenSHC::Rendering::Colors::COL_C2F0EB;
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // "Food Acquired" (111) and "Weapons Acquired" (112, 123) show "Goods Acquired" (113)
                if (textNumber == 111 || textNumber == 112 || textNumber == 113 || textNumber == 123) {
                    textNumber = 113;
                }
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[slot]
                        .enabled) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumber, DAT_ButtonX::instance + 5,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18, FALSE);
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionMaxValue[slot] == 0) {
                        return;
                    }
                    // ParamKind 1: one of EventConditionOptionTextOffsets (goods); 2: one of field_0x170 (an opponent)
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[slot] == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                            DAT_MissionAestheticsDefinedData::instance
                                .EventConditionOptionTextOffsets[DAT_MapPropertiesState::instance
                                        .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                        .data.scenario.conditions[slot]
                                        .subType],
                            DAT_ButtonX::instance + 14, DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18,
                            TRUE);
                    }
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[slot] == 2) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                            DAT_MissionAestheticsDefinedData::instance.field_0x170[DAT_MapPropertiesState::instance
                                    .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                    .data.scenario.conditions[slot]
                                    .subType],
                            DAT_ButtonX::instance + 14, DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_LEFT, color, 18,
                            TRUE);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.conditions[slot]
                                .value
                            * DAT_MissionAestheticsDefinedData::instance.EventConditionValueScale[slot],
                        DAT_ButtonW::instance + DAT_ButtonX::instance - 8, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_RIGHT, color, 18, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumber, DAT_ButtonX::instance + 5, DAT_ButtonY::instance + 7,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_7F7F7F, 18, FALSE);
                return;
            }
            case 1001:
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            // 2000 before 1000, !interacting first (in turn: quick_diff 0.9440 -> 0.9109; interacting first: 0.8223)
            case 2000:
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            case 1000:
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            case 2002:
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                        DAT_MissionAestheticsDefinedData::instance
                            .EventConditionOptionTextOffsets[DAT_MapPropertiesState::instance
                                    .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                    .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                    .subType],
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 8,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    != 2) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                    DAT_MissionAestheticsDefinedData::instance.field_0x170[DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            .subType],
                    DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 8,
                    OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                return;
            case 2001:
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            default:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
                return;
            }
        }

    }
}
}
