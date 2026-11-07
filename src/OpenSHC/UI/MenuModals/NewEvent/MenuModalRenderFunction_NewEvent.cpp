#include "../NewEvent.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AB790
        void NewEvent::MenuModalRenderFunction_NewEvent(int x, int y, int width, int height)
        {
            // "Event"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 48, x, y, width, height);
            // Lists the event's first seven enabled conditions, each with its parameter and value
            int rowsDrawn = 0;
            // Declared here, between the other two (declared in the for: quick_diff 0.9476 -> 0.9372)
            int conditionIndex = 0;
            int rowY = y + 165;
            for (;
                conditionIndex < countof(DAT_MapPropertiesState::instance.scenarioEvents[0].data.scenario.conditions);
                ++conditionIndex) {
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[conditionIndex]
                        .enabled
                    == 0) {
                    continue;
                }
                // Condition names are texts 106-125, then 190 on; the four "... Acquired" ones all read "Goods
                // Acquired"
                int conditionText = conditionIndex + 106;
                if (conditionText > 125) {
                    conditionText += 64;
                }
                if (conditionText == 111 || conditionText == 112 || conditionText == 113 || conditionText == 123) {
                    conditionText = 113;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, conditionText),
                    x + 150, rowY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                // Kind 1: the condition's resource
                if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[conditionIndex] == 1) {
                    int const optionX = x + 158;
                    // "("
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        s_brace_close_005a2778, optionX, rowY, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                    // The option's text offset is read after the "(" (in the call: quick_diff 0.9476 -> 0.8429)
                    int const optionText = DAT_MissionAestheticsDefinedData::instance
                                               .EventConditionOptionTextOffsets[DAT_MapPropertiesState::instance
                                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                       .data.scenario.conditions[conditionIndex]
                                                       .subType];
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, optionText),
                        optionX, rowY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                    // ")"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        s_brace_open_005a2774, optionX, rowY, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                }
                // Kind 2: the condition's lord
                if (DAT_MissionAestheticsDefinedData::instance.EventConditionParamKind[conditionIndex] == 2) {
                    int const optionX = x + 158;
                    // "("
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        s_brace_close_005a2778, optionX, rowY, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                    int const optionText
                        = DAT_MissionAestheticsDefinedData::instance.field_0x170[DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.conditions[conditionIndex]
                                .subType];
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, optionText),
                        optionX, rowY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                    // ")"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        s_brace_open_005a2774, optionX, rowY, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data.scenario.conditions[conditionIndex]
                            .value
                        * DAT_MissionAestheticsDefinedData::instance.EventConditionValueScale[conditionIndex],
                    x + 450, rowY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                ++rowsDrawn;
                rowY += 24;
                if (rowsDrawn >= 7) {
                    break;
                }
            }
            // Event action names are texts 128-155, then 177 on
            int eventText
                = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                      .data.scenario.ScenarioEventType
                + 128;
            if (eventText > 155) {
                eventText += 21;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, eventText),
                x + 158, y + 380, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
        }

    }
}
}
