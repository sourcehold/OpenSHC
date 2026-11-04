#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-macros.hpp"

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

        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B8BF0
        void EditScenario::MenuItemRenderFunction_EditScenario_EventAndInvasionList(int param_1, ...)
        {
            byte bVar1;
            BGR24 color;
            bool bVar5;
            if (DAT_MapPropertiesState::instance.eventListSelection >= DAT_MapPropertiesState::instance.eventsCount) {
                DAT_MapPropertiesState::instance.eventListSelection = DAT_MapPropertiesState::instance.eventsCount - 1;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                (uint)(param_1 == DAT_MapPropertiesState::instance.eventListSelection), param_1, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if ((int)DAT_MapPropertiesState::instance.eventListScrollOffset + param_1
                >= DAT_MapPropertiesState::instance.eventsCount) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if ((param_1 == DAT_MapPropertiesState::instance.eventListSelection)
                || (color = 12775659, DAT_ButtonCurrentlyInteracting::instance)) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
            }
            int iVar10 = 0;
            BOOLEnum BVar9 = FALSE;
            int iVar8 = 18;
            BGR24 BVar7 = OpenSHC::Rendering::Colors::COL_CCFAFF;
            TextAlignment TVar6 = OpenSHC::Text::TTA_LEFT;
            int iVar3 = DAT_ButtonY::instance + 4;
            int iVar4 = DAT_ButtonX::instance + 8;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS,
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .header.month),
                iVar4, iVar3, TVar6, BVar7, iVar8, BVar9, iVar10);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_MapPropertiesState::instance
                    .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                    .header.year,
                (int)(DAT_ButtonX::instance + 40), (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            iVar3 = DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .header.tl_type;
            if (iVar3 != 1) {
                if (iVar3 != 3) {
                    return;
                }
                iVar3 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                            .data.scenario.ScenarioEventType;
                iVar4 = iVar3 + 128;
                if (155 < iVar4) {
                    iVar4 = iVar3 + 149;
                    return;
                }
                BVar9 = FALSE;
                iVar10 = 18;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_ButtonY::instance + 4;
                iVar8 = DAT_ButtonX::instance + 80;
                BVar7 = color;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar4),
                    iVar8, iVar3, TVar6, BVar7, iVar10, BVar9, 0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .data.scenario.repeat
                    == 0) {
                    return;
                }
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .data.scenario.repeatMonths
                    == 1) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    // "("
                    S_BRACE_CLOSE_005A2778, (int)(DAT_ButtonX::instance + 340), (int)(DAT_ButtonY::instance + 4),
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE, 0);
                bVar1 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                            .data.scenario.repeatMonths;
                if (bVar1 != 10) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen,
                        DAT_TextManagerObject::ptr)((uint)bVar1, (int)(DAT_ButtonX::instance + 340),
                        (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_LEFT, (uint)(color), 18, TRUE);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    // "x"
                    S_X_005AA7F8, (int)(DAT_ButtonX::instance + 340), (int)(DAT_ButtonY::instance + 4),
                    OpenSHC::Text::TTA_LEFT, color, 18, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    (uint)DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .data.scenario.repeat,
                    (int)(DAT_ButtonX::instance + 340), (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_LEFT,
                    (uint)(color), 18, TRUE, 0);
                bVar5 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                            .data.scenario.repeat
                    == 1;
            } else {
                iVar10 = 0;
                BVar9 = FALSE;
                iVar8 = 18;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_ButtonY::instance + 4;
                iVar4 = DAT_ButtonX::instance + 80;
                BVar7 = color;
                // added by script: S_INVASION_005A7638
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 46),
                    iVar4, iVar3, TVar6, BVar7, iVar8, BVar9, iVar10);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .data.scenario.actionData,
                    (int)(DAT_ButtonX::instance + 250), (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_LEFT,
                    (uint)(color), 18, FALSE, 0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .data.invasion.repeatMonths
                    == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    // "(x"
                    S__X_005AA7F4, (int)(DAT_ButtonX::instance + 340), (int)(DAT_ButtonY::instance + 4),
                    OpenSHC::Text::TTA_LEFT, color, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                        .data.invasion.repeatMonths,
                    (int)(DAT_ButtonX::instance + 340), (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_LEFT,
                    (uint)(color), 18, TRUE, 0);
                bVar5 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.eventListScrollOffset + param_1]
                            .data.invasion.repeatMonths
                    == 1;
            }
            if (bVar5) {
                iVar3 = 210;
            } else {
                iVar3 = 211;
            }
            // added by script: "Months"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar3, (int)(DAT_ButtonX::instance + 346),
                (int)(DAT_ButtonY::instance + 4), OpenSHC::Text::TTA_LEFT, (uint)(color), 18, TRUE);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                // ")"
                S_BRACE_OPEN_005A2774, (int)(DAT_ButtonX::instance + 346), (int)(DAT_ButtonY::instance + 4),
                OpenSHC::Text::TTA_LEFT, color, 18, TRUE, 0);
        }

    }
}
}
