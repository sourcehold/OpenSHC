#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8BF0
        void EditScenario::MenuItemRenderFunction_EditScenario_EventAndInvasionList(int row, ...)
        {
            if (DAT_MapPropertiesState::instance.eventListSelection >= DAT_MapPropertiesState::instance.eventsCount) {
                DAT_MapPropertiesState::instance.eventListSelection = DAT_MapPropertiesState::instance.eventsCount - 1;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(row == DAT_MapPropertiesState::instance.eventListSelection, row, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // the event index is re-read after every call (an eventID local: quick_diff 0.9831 -> 0.6609)
            if (DAT_MapPropertiesState::instance.eventListScrollOffset + row
                >= DAT_MapPropertiesState::instance.eventsCount) {
                return;
            }
            // set in each branch (a default overridden: reccmp 100.0% -> 99.3%)
            uint color;
            if (row == DAT_MapPropertiesState::instance.eventListSelection
                || DAT_ButtonCurrentlyInteracting::instance) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
            } else {
                color = OpenSHC::Rendering::Colors::COL_C2F0EB;
            }
            // the month in a local first (in the call: quick_diff 0.9831 -> 0.9155)
            int const month = DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                                  .header.month;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS, month),
                DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_MapPropertiesState::instance
                    .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                    .header.year,
                DAT_ButtonX::instance + 40, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            // "Month(s)" in each case, merged by MSVC (a flag and one if after the switch: quick_diff 0.9831 -> 0.7973)
            switch (DAT_MapPropertiesState::instance
                    .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                    .header.tl_type) {
            case 1: {
                // an invasion: "Invasion", its unit count and, if it repeats, "(x<months> Month(s))"
                // "Invasion"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 46),
                    DAT_ButtonX::instance + 80, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.invasion.totalUnitCount,
                    DAT_ButtonX::instance + 250, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                    0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.invasion.repeatMonths
                    == 0) {
                    return;
                }
                // "(x"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s__x_005aa7f4, DAT_ButtonX::instance + 340, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT,
                    color, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.invasion.repeatMonths,
                    DAT_ButtonX::instance + 340, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT, color, 18, TRUE,
                    0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.invasion.repeatMonths
                    == 1) {
                    // "Month"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 210, DAT_ButtonX::instance + 346, DAT_ButtonY::instance + 4,
                        OpenSHC::Text::TTA_LEFT, color, 18, TRUE);
                } else {
                    // "Months"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 211, DAT_ButtonX::instance + 346, DAT_ButtonY::instance + 4,
                        OpenSHC::Text::TTA_LEFT, color, 18, TRUE);
                }
                break;
            }
            case 3: {
                // an event: its name and, if it repeats, "(<repeatMonths>x<repeat> Month(s))"
                // the event names start at 128 in the scenario texts, with 21 other texts after the 28th
                int textIndex = DAT_MapPropertiesState::instance
                                    .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                                    .data.scenario.ScenarioEventType
                    + 128;
                if (textIndex > 155) {
                    textIndex += 21;
                }
                // y then x for the name (in the call: quick_diff 0.9831 -> 0.9696)
                int const nameY = DAT_ButtonY::instance + 4;
                int const nameX = DAT_ButtonX::instance + 80;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, textIndex),
                    nameX, nameY, OpenSHC::Text::TTA_LEFT, color, 18, FALSE, 0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.scenario.repeat
                    == 0) {
                    return;
                }
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.scenario.repeatMonths
                    == 1) {
                    return;
                }
                // "("
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + 340, DAT_ButtonY::instance + 4,
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE, 0);
                // 10 shows no number
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.scenario.repeatMonths
                    != 10) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)(
                        DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                            .data.scenario.repeatMonths,
                        DAT_ButtonX::instance + 340, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT, color, 18,
                        TRUE);
                }
                // "x"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_x_005aa7f8, DAT_ButtonX::instance + 340, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT,
                    color, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.scenario.repeat,
                    DAT_ButtonX::instance + 340, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT, color, 18, TRUE,
                    0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + row]
                        .data.scenario.repeat
                    == 1) {
                    // "Month"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 210, DAT_ButtonX::instance + 346, DAT_ButtonY::instance + 4,
                        OpenSHC::Text::TTA_LEFT, color, 18, TRUE);
                } else {
                    // "Months"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, 211, DAT_ButtonX::instance + 346, DAT_ButtonY::instance + 4,
                        OpenSHC::Text::TTA_LEFT, color, 18, TRUE);
                }
                break;
            }
            default:
                return;
            }
            // ")"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s_brace_open_005a2774, DAT_ButtonX::instance + 346, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT,
                color, 18, TRUE, 0);
        }

    }
}
}
